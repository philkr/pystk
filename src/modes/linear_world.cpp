//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "modes/linear_world.hpp"

#include "config/stk_config.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/cannon_animation.hpp"
#include "karts/controller/controller.hpp"
#include "karts/kart_properties.hpp"
#include "graphics/material.hpp"
#include "physics/physics.hpp"
#include "tracks/check_manager.hpp"
#include "tracks/check_structure.hpp"
#include "tracks/drive_graph.hpp"
#include "tracks/drive_node.hpp"
#include "tracks/track_sector.hpp"
#include "tracks/track.hpp"
#include "utils/constants.hpp"
#include "utils/string_utils.hpp"

#include <climits>
#include <iostream>

//-----------------------------------------------------------------------------
/** Constructs the linear world. Note that here no functions can be called
 *  that use World::getWorld(), since it is not yet defined.
 */
LinearWorld::LinearWorld() : WorldWithRank()
{
    m_fastest_lap_ticks    = INT_MAX;
    m_fastest_lap_kart_name = "";
}   // LinearWorld

// ----------------------------------------------------------------------------
/** Actually initialises the world, i.e. creates all data structures to
 *  for all karts etc. In init functions can be called that use
 *  World::getWorld().
 */
void LinearWorld::init()
{
    WorldWithRank::init();

    assert(!Track::getCurrentTrack()->isArena());
    assert(!Track::getCurrentTrack()->isSoccer());

    m_fastest_lap_kart_name         = "";

    // The values are initialised in reset()
    m_kart_info.resize(m_karts.size());
}   // init

//-----------------------------------------------------------------------------
/** The destructor frees al data structures.
 */
LinearWorld::~LinearWorld()
{
}   // ~LinearWorld

//-----------------------------------------------------------------------------
/** Called before a race is started (or restarted). It resets the data
 *  structures that keep track of position and distance long track of
 *  all karts.
 */
void LinearWorld::reset(bool restart)
{
    WorldWithRank::reset(restart);
    m_finish_timeout = std::numeric_limits<float>::max();
    m_fastest_lap_ticks    = INT_MAX;

    const unsigned int kart_amount = (unsigned int) m_karts.size();
    for(unsigned int i=0; i<kart_amount; i++)
    {
        m_kart_info[i].reset();
    }   // next kart

    // At the moment the last kart would be the one that is furthest away
    // from the start line, i.e. it would determine the amount by which
    // the track length must be extended (to avoid negative numbers in
    // estimateFinishTimeForKart()). On the other hand future game modes
    // might not follow this rule, so check the distance for all karts here:
    m_distance_increase = Track::getCurrentTrack()->getTrackLength();
    for(unsigned int i=0; i<kart_amount; i++)
    {
        m_distance_increase = std::min(m_distance_increase,
                                       getDistanceDownTrackForKart(i, false));
    }
    // Track length - minimum distance is how much the track length must
    // be increased to avoid negative values in estimateFinishTimeForKart
    // Increase this value somewhat in case that a kart drivess/slides
    // backwards a little bit at start.
    m_distance_increase = Track::getCurrentTrack()->getTrackLength() 
                        - m_distance_increase + 5.0f;

    if(m_distance_increase<0) m_distance_increase = 1.0f;  // shouldn't happen

    // First all kart infos must be updated before the kart position can be
    // recomputed, since otherwise 'new' (initialised) valued will be compared
    // with old values.
    updateRacePosition();

#ifdef DEBUG
    //FIXME: this could be defined somewhere in a central header so it can
    //       be used everywhere
#define assertExpr( ARG1, OP, ARG2 ) if (!(ARG1 OP ARG2)) \
        { \
            std::cerr << "Failed assert " << #ARG1 << #OP << #ARG2 << " @ " \
                      << __FILE__ << ":" << __LINE__ \
                      << "; values are (" << ARG1 << #OP << ARG2 << ")\n"; \
            assert(false); \
        }

    for (unsigned int i=0; i<kart_amount; i++)
    {
        for (unsigned int j=i+1; j<kart_amount; j++)
        {
            assertExpr( m_karts[i]->getPosition(), !=,
                        m_karts[j]->getPosition() );
        }
    }
#endif

}   // reset

//-----------------------------------------------------------------------------
/** General update function called once per frame. This updates the kart
 *  sectors, which are then used to determine the kart positions.
 *  \param ticks Number of physics time steps - should be 1.
 */
void LinearWorld::update(int ticks)
{
    if (getPhase() == RACE_PHASE &&
        m_finish_timeout != std::numeric_limits<float>::max())
    {
        m_finish_timeout -= stk_config->ticks2Time(ticks);
        if (m_finish_timeout < 0.0f)
        {
            endRaceEarly();
            m_finish_timeout = std::numeric_limits<float>::max();
        }
    }

    // Do stuff specific to this subtype of race.
    // ------------------------------------------
    updateTrackSectors();
    // Run generic parent stuff that applies to all modes.
    // It especially updates the kart positions.
    // It MUST be done after the update of the distances
    WorldWithRank::update(ticks);

    // Update all positions. This must be done after _all_ karts have
    // updated their position and laps etc, otherwise inconsistencies
    // (like two karts at same position) can occur.
    // ---------------------------------------------------------------
    WorldWithRank::updateTrack(ticks);
    updateRacePosition();

    const unsigned int kart_amount = getNumKarts();
    for (unsigned int i=0; i<kart_amount; i++)
    {
        // ---------- update rank ------
        if (m_karts[i]->hasFinishedRace() ||
            m_karts[i]->isEliminated()       ) continue;

        // Update the estimated finish time.
        // This is used by the AI
        m_kart_info[i].m_estimated_finish =
                estimateFinishTimeForKart(m_karts[i].get());
    }

#ifdef DEBUG
    // Debug output in case that the double position error occurs again.
    std::vector<int> pos_used;
    pos_used.resize(kart_amount+1, -99);
    for(unsigned int i=0; i<kart_amount; i++)
    {
        if(pos_used[m_karts[i]->getPosition()]!=-99)
        {
            for(unsigned int j=0; j<kart_amount; j++)
            {
                Log::verbose("[LinearWorld]", "kart id=%u, position=%d, finished=%d, laps=%d, "
                       "distanceDownTrack=%f overallDistance=%f %s",
                    j, m_karts[j]->getPosition(),
                    m_karts[j]->hasFinishedRace(),
                    m_kart_info[j].m_finished_laps,
                    getDistanceDownTrackForKart(m_karts[j]->getWorldKartId(), true),
                    m_kart_info[j].m_overall_distance,
                    (m_karts[j]->getPosition() == m_karts[i]->getPosition()
                     ? "<--- !!!" : "")                                      );
            }
        }
        pos_used[m_karts[i]->getPosition()]=i;
    }
#endif
}   // update

//-----------------------------------------------------------------------------
void LinearWorld::updateTrackSectors()
{
    const unsigned int kart_amount = getNumKarts();
    for(unsigned int n=0; n<kart_amount; n++)
    {
        KartInfo& kart_info = m_kart_info[n];
        AbstractKart* kart = m_karts[n].get();

        // Nothing to do for karts that are currently being
        // rescued or eliminated
        if(kart->getKartAnimation() &&
           !dynamic_cast<CannonAnimation*>(kart->getKartAnimation()))
            continue;
        // If the kart is off road, and 'flying' over a reset plane
        // don't adjust the distance of the kart, to avoid a jump
        // in the position of the kart (e.g. while falling the kart
        // might get too close to another part of the track, shortly
        // jump to position one, then on reset fall back to last)
        if ((!getTrackSector(n)->isOnRoad() &&
            (!kart->getMaterial() ||
              kart->getMaterial()->isDriveReset())))
            continue;
        getTrackSector(n)->update(kart->getFrontXYZ());
        kart_info.m_overall_distance = kart_info.m_finished_laps
                                     * Track::getCurrentTrack()->getTrackLength()
                        + getDistanceDownTrackForKart(kart->getWorldKartId(), true);
    }   // for n
}   // updateTrackSectors

//-----------------------------------------------------------------------------
/** This updates all only graphical elements.It is only called once per
*  rendered frame, not once per time step.
*  float dt Time since last rame.
*/
void LinearWorld::updateGraphics(float dt)
{
    WorldWithRank::updateGraphics(dt);
}   // updateGraphics

//-----------------------------------------------------------------------------
/** Is called by check structures if a kart starts a new lap.
 *  \param kart_index Index of the kart.
 */
void LinearWorld::newLap(unsigned int kart_index)
{
    KartInfo &kart_info = m_kart_info[kart_index];
    AbstractKart *kart  = m_karts[kart_index].get();

    // Only update the kart controller if a kart that has already finished
    // the race crosses the start line again. This avoids 'fastest lap'
    // messages if the end controller does a fastest lap, but especially
    // allows the end controller to switch end cameras
    if(kart->hasFinishedRace())
    {
        kart->getController()->newLap(kart_info.m_finished_laps);
        return;
    }

    const int lap_count = race_manager->getNumLaps();

    // Only increase the lap counter and set the new time if the
    // kart hasn't already finished the race (otherwise the race_gui
    // will begin another countdown).
    if(kart_info.m_finished_laps+1 <= lap_count)
    {
        assert(kart->getWorldKartId()==kart_index);
        kart_info.m_ticks_at_last_lap=getTimeTicks();
        kart_info.m_finished_laps++;
        m_kart_info[kart_index].m_overall_distance =
              m_kart_info[kart_index].m_finished_laps 
            * Track::getCurrentTrack()->getTrackLength()
            + getDistanceDownTrackForKart(kart->getWorldKartId(), true);
    }

    // The race positions must be updated here: consider the situation where
    // the first kart does not cross the finish line in its last lap, instead
    // it passes it, the kart reverses and crosses the finishing line
    // backwards. Just before crossing the finishing line the kart will be on
    // the last lap, but with a distance along the track close to zero.
    // Therefore its position will be wrong. If the race position gets updated
    // after increasing the number of laps (but before tagging the kart to have
    // finished the race) the position will be correct (since the kart now
    // has one additional lap it will be ahead of the other karts).
    // Without this call the incorrect position for this kart would remain
    // (since a kart that has finished the race does not get its position
    // changed anymore), potentially resulting in a duplicated race position
    // (since the first kart does not have position 1, no other kart can get
    // position 1, so one rank will be duplicated).
    // Similarly the situation can happen if the distance along track should
    // go back to zero before actually crossing the finishing line. While this
    // should not happen, it could potentially be caused by floating point
    // errors. In this case the call to updateRacePosition will avoid
    // duplicated race positions as well.
    updateRacePosition();

    // Race finished
    // We compute the exact moment the kart crossed the line
    // This way, even with poor framerate, we get a time significant to the ms
    if(kart_info.m_finished_laps >= race_manager->getNumLaps() && raceHasLaps())
    {
        {
            float curr_distance_after_line = getDistanceDownTrackForKart(kart->getWorldKartId(),false);

            TrackSector prev_sector;
            prev_sector.update(kart->getRecentPreviousXYZ());
            float prev_distance_before_line = Track::getCurrentTrack()->getTrackLength()
                                              - prev_sector.getDistanceFromStart(false);

            float finish_proportion = curr_distance_after_line
                                      / (prev_distance_before_line + curr_distance_after_line);
        
            float prev_time = kart->getRecentPreviousXYZTime();
            float finish_time = prev_time*finish_proportion + getTime()*(1.0f-finish_proportion);

            kart->finishedRace(finish_time);
        }
    }
    int ticks_per_lap;
    if (kart_info.m_finished_laps == 1) // just completed first lap
    {
        ticks_per_lap = getTimeTicks();
    }
    else //completing subsequent laps
    {
        ticks_per_lap = getTimeTicks() - kart_info.m_lap_start_ticks;
    }

    // if new fastest lap
    if(ticks_per_lap < m_fastest_lap_ticks && raceHasLaps() &&
        kart_info.m_finished_laps>0)
    {
        m_fastest_lap_ticks = ticks_per_lap;

        std::string s = StringUtils::ticksTimeToString(ticks_per_lap);

        // Store the temporary string because clang would mess this up
        // (remove the stringw before the wchar_t* is used).
        const core::stringw &kart_name = kart->getController()->getName();
        m_fastest_lap_kart_name = kart_name;
    } // end if new fastest lap

    kart_info.m_lap_start_ticks = getTimeTicks();
    kart->getController()->newLap(kart_info.m_finished_laps);
}   // newLap

//-----------------------------------------------------------------------------
/** Returns the distance the kart has travelled along the track since
 *  crossing the start line..
 *  \param kart_id Index of the kart.
 */
float LinearWorld::getDistanceDownTrackForKart(const int kart_id, bool account_for_checklines) const
{
    return getTrackSector(kart_id)->getDistanceFromStart(account_for_checklines, true);
}   // getDistanceDownTrackForKart

//-----------------------------------------------------------------------------
/** Gets the distance of the kart from the center of the driveline. Positive
 *  is to the right of the center, negative values to the left.
 *  \param kart_id Index of kart.
 */
float LinearWorld::getDistanceToCenterForKart(const int kart_id) const
{
    return getTrackSector(kart_id)->getDistanceToCenter();
}   // getDistanceToCenterForKart

//-----------------------------------------------------------------------------
int LinearWorld::getLapForKart(const int kart_id) const
{
    assert(kart_id < (int)m_kart_info.size());
    return  m_kart_info[kart_id].m_finished_laps;
}   // getLapForKart

//-----------------------------------------------------------------------------
/** Returns the estimated finishing time.
 *  \param kart_id Id of the kart.
 */
float LinearWorld::getEstimatedFinishTime(const int kart_id) const
{
    assert(kart_id < (int)m_kart_info.size());
    return m_kart_info[kart_id].m_estimated_finish;
}   // getEstimatedFinishTime

//-----------------------------------------------------------------------------
int LinearWorld::getTicksAtLapForKart(const int kart_id) const
{
    assert(kart_id < (int)m_kart_info.size());
    return m_kart_info[kart_id].m_ticks_at_last_lap;
}   // getTicksAtLapForKart

//-----------------------------------------------------------------------------
/** Estimate the arrival time of any karts that haven't arrived yet by using
 *  their average speed up to now and the distance still to race. This
 *  approach guarantees that the order of the karts won't change anymore
 *  (karts ahead will have covered more distance and have therefore a higher
 *  average speed and therefore finish the race earlier than karts further
 *  behind), so the position doesn't have to be updated to get the correct
 *  scoring.
 *  As so often the devil is in the details: a kart that hasn't crossed the
 *  starting line has a negative distance (when it is crossing the start line
 *  its distance becomes 0), which can result in a negative average speed
 *  (and therefore incorrect estimates). This is partly taken care of by
 *  adding m_distance_increase to the distance covered by a kart. The value
 *  of m_distance_increase is a bit more than the distance the last kart
 *  has from the start line at start time. This guarantees that the distance
 *  used in computing the average speed is positive in most cases. Only
 *  exception is if a kart is driving backwards on purpose. While this
 *  shouldn't happen (the AI doesn't do it, and if it's a player the game
 *  won't finish so the time estimation won't be called and so the incorrect
 *  result won't be displayed), this is still taken care of: if the average
 *  speed is negative, the estimated arrival time of the kart is set to
 *  99:00 plus kart position. This means that even in this case all karts
 *  will have a different arrival time.
 *  \pre The position of the karts are set according to the distance they
 *       have covered.
 *  \param kart The kart for which to estimate the finishing times.
 */
float LinearWorld::estimateFinishTimeForKart(AbstractKart* kart)
{
    const KartInfo &kart_info = m_kart_info[kart->getWorldKartId()];

    float full_distance = race_manager->getNumLaps()
                        * Track::getCurrentTrack()->getTrackLength();

    if(full_distance == 0)
        full_distance = 1.0f;   // For 0 lap races avoid warning below

#ifdef DEBUG
    if(kart_info.m_overall_distance > full_distance)
    {
        Log::debug("[LinearWorld]", "Full distance < distance covered for kart '%s':",
               kart->getIdent().c_str());
        Log::debug("[LinearWorld]", "%f < %f", full_distance, kart_info.m_overall_distance);
    }
#endif
    // Avoid potential problems (floating point issues, coding bug?) if a
    // kart has driven more than the full distance, but not finished:
    // Return the current time plus initial position to spread arrival
    // times a bit. This code should generally not be used at all, it's
    // just here to avoid invalid finishing times.
    if(kart_info.m_overall_distance > full_distance)
        return getTime() + kart->getInitialPosition();

    // Finish time is the time needed for the whole race with
    // the computed average speed computed. The distance is always positive
    // due to the way m_distance_increase was computed, so average speed
    // is also always positive.
    float average_speed = getTime()==0
                        ? 1.0f
                        : (m_distance_increase + kart_info.m_overall_distance)
                          / getTime();

    // Avoid NAN or invalid results when average_speed is very low
    // or negative (which can happen if a kart drives backwards and
    // m_overall distance becomes smaller than -m_distance_increase).
    // In this case set the time to 59 minutes, offset by kart
    // position (to spread arrival times for all karts that arrive
    // even later). This works for up to 60 karts (otherwise the
    // time displayed would overflow to 00:yy).
    if(average_speed<0.01f)
        return 59*60.0f + kart->getPosition();

    float est_time = getTime() + (full_distance - kart_info.m_overall_distance)
                                 / average_speed;

    // Avoid times > 59:00 - in this case use kart position to spread
    // arrival time so that each kart has a unique value. The pre-condition
    // guarantees that this works correctly (higher position -> less distance
    // covered -> later arrival time).
    if(est_time>59*60.0f)
        return 59*60.0f + kart->getPosition();

    return est_time;
}   // estimateFinishTimeForKart

// ------------------------------------------------------------------------
/** Returns the number of rescue positions on a given track, which in
 *  linear races is just the number of driveline quads.
  */
unsigned int LinearWorld::getNumberOfRescuePositions() const
{
    return DriveGraph::get()->getNumNodes();
}   // getNumberOfRescuePositions

// ------------------------------------------------------------------------
unsigned int LinearWorld::getRescuePositionIndex(AbstractKart *kart)
{
    const unsigned int kart_id = kart->getWorldKartId();

    getTrackSector(kart_id)->rescue();
    // Setting XYZ for the kart is important since otherwise the kart
    // will not detect the right material again when doing the next
    // raycast to detect where it is driving on (--> potential rescue loop)
    int index = getTrackSector(kart_id)->getCurrentGraphNode();

    // Do not rescue to an ignored quad, find another (non-ignored) quad
    if (Graph::get()->getQuad(index)->isIgnored())
    {
        Vec3 pos = kart->getFrontXYZ();
        int sector = Graph::get()->findOutOfRoadSector(pos);
        return sector;
    }

    return index;
}   // getRescuePositionIndex

// ------------------------------------------------------------------------
btTransform LinearWorld::getRescueTransform(unsigned int index) const
{
    const Vec3 &xyz = DriveGraph::get()->getNode(index)->getCenter();
    const Vec3 &normal = DriveGraph::get()->getNode(index)->getNormal();
    btTransform pos;
    pos.setOrigin(xyz);

    // First rotate into the quad's plane (q1), then rotate so that the kart points in the
    // right direction (q2).
    btQuaternion q1 = shortestArcQuat(Vec3(0, 1, 0), normal);
    // First apply the heading change, than the 'parallelisation' to the plane
    btQuaternion q2(btVector3(0,1,0), Track::getCurrentTrack()->getAngle(index));
    pos.setRotation(q1*q2);
    return pos;
}   // getRescueTransform

//-----------------------------------------------------------------------------
/** Find the position (rank) of every kart. ATM it uses a stable O(n^2)
 *  algorithm by counting for each kart how many other karts are ahead of
 *  it.
 */
void LinearWorld::updateRacePosition()
{
    // Mostly for debugging:
    beginSetKartPositions();
    const unsigned int kart_amount = (unsigned int) m_karts.size();

#ifdef DEBUG
    bool rank_changed = false;
#endif

    // NOTE: if you do any changes to this loop, the next loop (see
    // DEBUG_KART_RANK below) needs to have the same changes applied
    // so that debug output is still correct!!!!!!!!!!!
    for (unsigned int i=0; i<kart_amount; i++)
    {
        AbstractKart* kart = m_karts[i].get();
        // Karts that are either eliminated or have finished the
        // race already have their (final) position assigned. If
        // these karts would get their rank updated, it could happen
        // that a kart that finished first will be overtaken after
        // crossing the finishing line and become second!
        if(kart->isEliminated() || kart->hasFinishedRace())
        {
            // This is only necessary to support debugging inconsistencies
            // in kart position parameters.
            setKartPosition(i, kart->getPosition());
            continue;
        }
        KartInfo& kart_info = m_kart_info[i];

        int p = 1 ;

        const unsigned int my_id = kart->getWorldKartId();
        const float my_distance  = m_kart_info[my_id].m_overall_distance;

        // Count karts ahead of the current kart, i.e. kart that are
        // already finished or have covered a larger overall distance.
        for (unsigned int j = 0 ; j < kart_amount ; j++)
        {
            // don't compare a kart with itself and ignore eliminated karts
            if(j == my_id || m_karts[j]->isEliminated())
                continue;

            // If the other kart has:
            // - finished the race (but this kart hasn't)
            // - or is ahead
            // - or has the same distance (very unlikely) but started earlier
            // it is ahead --> increase position
            if((!kart->hasFinishedRace() && m_karts[j]->hasFinishedRace()) ||
                m_kart_info[j].m_overall_distance > my_distance            ||
               (m_kart_info[j].m_overall_distance == my_distance &&
                m_karts[j]->getInitialPosition()<kart->getInitialPosition() ) )
            {
                p++;
            }

        } //next kart
        setKartPosition(i, p);

        // Switch on faster music if not already done so, if the
        // first kart is doing its last lap.
        if(!m_faster_music_active                                  &&
            p == 1                                                 &&
            kart_info.m_finished_laps == race_manager->getNumLaps() - 1 &&
            useFastMusicNearEnd()                                       )
        {
            m_faster_music_active=true;
        }
    }   // for i<kart_amount

    endSetKartPositions();
}   // updateRacePosition

//-----------------------------------------------------------------------------
/** Checks if a kart is going in the wrong direction. This is done only for
 *  player karts to display a message to the player.
 *  \param i Kart id.
 *  \param dt Time step size.
 */
void LinearWorld::checkForWrongDirection(unsigned int i, float dt)
{
    if (!m_karts[i]->getController()->isLocalPlayerController()) 
        return;

    KartInfo &ki = m_kart_info[i];
    
    const AbstractKart *kart=m_karts[i].get();
    // If the kart can go in more than one directions from the current track
    // don't do any reverse message handling, since it is likely that there
    // will be one direction in which it isn't going backwards anyway.
    int sector = getTrackSector(i)->getCurrentGraphNode();
    
    if (DriveGraph::get()->getNumberOfSuccessors(sector) > 1)
        return;

    // check if the player is going in the wrong direction
    const DriveNode* node = DriveGraph::get()->getNode(sector);
    Vec3 center_line = node->getUpperCenter() - node->getLowerCenter();
    float angle_diff = kart->getVelocity().angle(center_line);

    if (angle_diff > M_PI)
        angle_diff -= 2*M_PI;
    else if (angle_diff < -M_PI)
        angle_diff += 2*M_PI;

    // Display a warning message if the kart is going back way, i.e. if angle
    // is too big(unless the kart has already finished the race).
    if ((angle_diff > DEGREE_TO_RAD * 120.0f ||
        angle_diff < -DEGREE_TO_RAD * 120.0f) &&
        kart->getVelocityLC().getY() > 0.0f &&
        !kart->hasFinishedRace())
    {
        ki.m_wrong_way_timer += dt;
        
        if (ki.m_wrong_way_timer> 2.0f)
            ki.m_wrong_way_timer= 2.0f;
    }
    else
    {
        ki.m_wrong_way_timer -= dt;

        if (ki.m_wrong_way_timer < 0)
            ki.m_wrong_way_timer = 0;
    }
    
    if (kart->getKartAnimation())
        ki.m_wrong_way_timer = 0;
    
}   // checkForWrongDirection

//-----------------------------------------------------------------------------
void LinearWorld::setLastTriggeredCheckline(unsigned int kart_index, int index)
{
    if (m_kart_info.size() == 0) return;
    getTrackSector(kart_index)->setLastTriggeredCheckline(index);
}   // setLastTriggeredCheckline

//-----------------------------------------------------------------------------
std::pair<uint32_t, uint32_t> LinearWorld::getGameStartedProgress() const
{
    std::pair<uint32_t, uint32_t> progress(
        std::numeric_limits<uint32_t>::max(),
        std::numeric_limits<uint32_t>::max());
    AbstractKart* slowest_kart = NULL;
    for (unsigned i = (unsigned)m_karts.size(); i > 0; i--)
    {
        slowest_kart = getKartAtPosition(i);
        if (slowest_kart && !slowest_kart->isEliminated())
            break;
    }
    if (slowest_kart &&
        getFinishedLapsOfKart(slowest_kart->getWorldKartId()) != -1)
    {
        progress.second = (uint32_t)(
            getOverallDistance(slowest_kart->getWorldKartId()) /
            (Track::getCurrentTrack()->getTrackLength() *
            (float)race_manager->getNumLaps()) * 100.0f);
    }
    return progress;
}   // getGameStartedProgress

// ----------------------------------------------------------------------------
void LinearWorld::handleServerCheckStructureCount(unsigned count)
{
    if (count != CheckManager::get()->getCheckStructureCount())
    {
        Log::warn("LinearWorld",
            "Server has different check structures size.");
    }
}   // handleServerCheckStructureCount
