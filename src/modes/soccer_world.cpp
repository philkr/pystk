//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006-2015 SuperTuxKart-Team
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

#include "modes/soccer_world.hpp"

#include "io/file_manager.hpp"
#include "graphics/irr_driver.hpp"
#include "karts/abstract_kart_animation.hpp"
#include "karts/kart_model.hpp"
#include "karts/kart_properties.hpp"
#include "karts/controller/local_player_controller.hpp"

#include "physics/physics.hpp"
#include "tracks/graph.hpp"
#include "tracks/quad.hpp"
#include "tracks/track.hpp"
#include "tracks/track_object_manager.hpp"
#include "tracks/track_sector.hpp"
#include "utils/constants.hpp"
#include "utils/string_utils.hpp"

#include <IMeshSceneNode.h>
#include <numeric>
#include <string>
//-----------------------------------------------------------------------------
/** Constructor. Sets up the clock mode etc.
 */
SoccerWorld::SoccerWorld() : WorldWithRank()
{
    if (race_manager->hasTimeTarget())
    {
        WorldStatus::setClockMode(WorldStatus::CLOCK_COUNTDOWN,
            race_manager->getTimeTarget());
    }
    else
    {
        WorldStatus::setClockMode(CLOCK_CHRONO);
    }

    m_frame_count = 0;
    m_red_ai = 0;
    m_blue_ai = 0;
    m_ball_track_sector = NULL;
}   // SoccerWorld

//-----------------------------------------------------------------------------
/** The destructor frees all data structures.
 */
SoccerWorld::~SoccerWorld()
{
    delete m_ball_track_sector;
    m_ball_track_sector = NULL;
}   // ~SoccerWorld

//-----------------------------------------------------------------------------
/** Initializes the soccer world. It sets up the data structure
 *  to keep track of points etc. for each kart.
 */
void SoccerWorld::init()
{
    m_kart_team_map.clear();
    m_kart_position_map.clear();
    WorldWithRank::init();
    m_display_rank = false;
    m_ball_hitter  = -1;
    m_ball         = NULL;
    m_ball_body    = NULL;
    m_goal_target  = race_manager->getMaxGoal();

    Track *track = Track::getCurrentTrack();
    if (track->hasNavMesh())
    {
        // Init track sector for ball if navmesh is found
        m_ball_track_sector = new TrackSector();
    }

    TrackObjectManager* tom = track->getTrackObjectManager();
    assert(tom);
    PtrVector<TrackObject>& objects = tom->getObjects();
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        TrackObject* obj = objects.get(i);
        if(!obj->isSoccerBall())
            continue;
        m_ball = obj;
        m_ball_body = m_ball->getPhysicalObject()->getBody();
        // Handle one ball only
        break;
    }
    if (!m_ball)
        Log::fatal("SoccerWorld","Ball is missing in soccer field, abort.");

    m_bgd.init(m_ball->getPhysicalObject()->getRadius());

}   // init

//-----------------------------------------------------------------------------
/** Called when a soccer game is restarted.
 */
void SoccerWorld::reset(bool restart)
{
    WorldWithRank::reset(restart);
    if (race_manager->hasTimeTarget())
    {
        WorldStatus::setClockMode(WorldStatus::CLOCK_COUNTDOWN,
            race_manager->getTimeTarget());
    }
    else
    {
        WorldStatus::setClockMode(CLOCK_CHRONO);
    }

    m_count_down_reached_zero = false;
    m_red_scorers.clear();
    m_blue_scorers.clear();
    m_ball_hitter = -1;
    m_red_kdm.clear();
    m_blue_kdm.clear();
    m_ball_heading = 0.0f;
    m_ball_invalid_timer = 0;
    m_goal_transforms.clear();
    m_goal_transforms.resize(m_karts.size());

    if (Track::getCurrentTrack()->hasNavMesh())
    {
        m_ball_track_sector->reset();
    }

    m_reset_ball_ticks = -1;
    m_ball->reset();
    m_bgd.reset();
    m_ticks_back_to_own_goal = -1;
    m_ball->setEnabled(false);

}   // reset

//-----------------------------------------------------------------------------
void SoccerWorld::onGo()
{
    m_ball->setEnabled(true);
    m_ball->reset();
    WorldWithRank::onGo();
}   // onGo

//-----------------------------------------------------------------------------
void SoccerWorld::terminateRace()
{
    const unsigned int kart_amount = getNumKarts();
    for (unsigned int i = 0; i < kart_amount ; i++)
    {
        // Soccer mode use goal for race result, and each goal time is
        // handled by handlePlayerGoalFromServer already
        m_karts[i]->finishedRace(0.0f, true/*from_server*/);
    }   // i<kart_amount
    WorldWithRank::terminateRace();
}   // terminateRace

//-----------------------------------------------------------------------------
/** Returns the internal identifier for this race.
 */
const std::string& SoccerWorld::getIdent() const
{
    return IDENT_SOCCER;
}   // getIdent

//-----------------------------------------------------------------------------
/** Update the world and the track.
 *  \param ticks Physics time steps - should be 1.
 */
void SoccerWorld::update(int ticks)
{
    updateBallPosition(ticks);
    if (Track::getCurrentTrack()->hasNavMesh())
    {
        updateSectorForKarts();
        updateAIData();
    }

    WorldWithRank::update(ticks);
    WorldWithRank::updateTrack(ticks);

    if (isGoalPhase())
    {
        for (unsigned int i = 0; i < m_karts.size(); i++)
        {
            auto& kart = m_karts[i];
            if (kart->isEliminated())
                continue;
            if (kart->getKartAnimation())
            {
                AbstractKartAnimation* ka = kart->getKartAnimation();
                kart->setKartAnimation(NULL);
                delete ka;
            }
            kart->getBody()->setLinearVelocity(Vec3(0.0f));
            kart->getBody()->setAngularVelocity(Vec3(0.0f));
            kart->getBody()->proceedToTransform(m_goal_transforms[i]);
            kart->setTrans(m_goal_transforms[i]);
        }
        if (m_ticks_back_to_own_goal - getTicksSinceStart() == 1 &&
            !isRaceOver())
        {
            // Reset all karts and ball
            resetKartsToSelfGoals();
        }
    }
}   // update

//-----------------------------------------------------------------------------
void SoccerWorld::onCheckGoalTriggered(bool first_goal)
{
    if (isRaceOver())
        return;

    m_ticks_back_to_own_goal = getTicksSinceStart() +
        stk_config->time2Ticks(3.0f);
    m_ball->reset();
    m_ball->setEnabled(false);
    if (m_ball_hitter != -1)
    {
        ScorerData sd = {};
        sd.m_id = m_ball_hitter;
        sd.m_correct_goal = isCorrectGoal(m_ball_hitter, first_goal);
        sd.m_kart = getKart(m_ball_hitter)->getIdent();
        sd.m_player = getKart(m_ball_hitter)->getController()->getName();
        if (sd.m_correct_goal)
        {
            m_karts[m_ball_hitter]->getKartModel()
                ->setAnimation(KartModel::AF_WIN_START, true/* play_non_loop*/);
        }

        else if (!sd.m_correct_goal)
        {
            m_karts[m_ball_hitter]->getKartModel()
                ->setAnimation(KartModel::AF_LOSE_START, true/* play_non_loop*/);
        }

        if (first_goal)
        {
            if (race_manager->hasTimeTarget())
            {
                sd.m_time = race_manager->getTimeTarget() - getTime();
            }
            else
                sd.m_time = getTime();
            // Notice: true first_goal means it's blue goal being shoot,
            // so red team can score
            m_red_scorers.push_back(sd);
        }
        else
        {
            if (race_manager->hasTimeTarget())
            {
                sd.m_time = race_manager->getTimeTarget() - getTime();
            }
            else
                sd.m_time = getTime();
            m_blue_scorers.push_back(sd);
        }
    }
    for (unsigned i = 0; i < m_karts.size(); i++)
    {
        auto& kart = m_karts[i];
        kart->getBody()->setLinearVelocity(Vec3(0.0f));
        kart->getBody()->setAngularVelocity(Vec3(0.0f));
        m_goal_transforms[i] = kart->getBody()->getWorldTransform();
    }
}   // onCheckGoalTriggered

//-----------------------------------------------------------------------------
void SoccerWorld::resetKartsToSelfGoals()
{
    m_ball->setEnabled(true);
    m_ball->reset();
    m_bgd.resetCheckGoal(Track::getCurrentTrack());
    for (unsigned i = 0; i < m_karts.size(); i++)
    {
        auto& kart = m_karts[i];
        if (kart->isEliminated())
            continue;

        kart->getBody()->setLinearVelocity(Vec3(0.0f));
        kart->getBody()->setAngularVelocity(Vec3(0.0f));
        unsigned index = m_kart_position_map.at(kart->getWorldKartId());
        btTransform t = Track::getCurrentTrack()->getStartTransform(index);
        moveKartTo(kart.get(), t);
    }
}   // resetKartsToSelfGoals

//-----------------------------------------------------------------------------
/** Sets the last kart that hit the ball, to be able to
 * identify the scorer later.
 */
void SoccerWorld::setBallHitter(unsigned int kart_id)
{
    m_ball_hitter = kart_id;
}   // setBallHitter

//-----------------------------------------------------------------------------
/** The soccer game is over if time up or either team wins.
 */
bool SoccerWorld::isRaceOver()
{
    if (m_unfair_team)
        return true;

    if (race_manager->hasTimeTarget())
    {
        return m_count_down_reached_zero;
    }
    // One team scored the target goals ...
    else
    {
        return (getScore(KART_TEAM_BLUE) >= m_goal_target ||
            getScore(KART_TEAM_RED) >= m_goal_target);
    }

}   // isRaceOver

//-----------------------------------------------------------------------------
/** Called when the match time ends.
 */
void SoccerWorld::countdownReachedZero()
{
    // Prevent negative time in network soccer when finishing
    m_time_ticks = 0;
    m_time = 0.0f;
    m_count_down_reached_zero = true;
}   // countdownReachedZero

//-----------------------------------------------------------------------------
bool SoccerWorld::getKartSoccerResult(unsigned int kart_id) const
{
    if (m_red_scorers.size() == m_blue_scorers.size()) return true;

    bool red_win = m_red_scorers.size() > m_blue_scorers.size();
    KartTeam team = getKartTeam(kart_id);

    if ((red_win && team == KART_TEAM_RED) ||
        (!red_win && team == KART_TEAM_BLUE))
        return true;
    else
        return false;

}   // getKartSoccerResult

//-----------------------------------------------------------------------------
/** Localize the ball on the navigation mesh.
 */
void SoccerWorld::updateBallPosition(int ticks)
{
    if (isRaceOver()) return;

    if (!ballNotMoving())
    {
        // Only update heading if the ball is moving
        m_ball_heading = atan2f(m_ball_body->getLinearVelocity().getX(),
            m_ball_body->getLinearVelocity().getZ());
    }

    if (Track::getCurrentTrack()->hasNavMesh())
    {
        m_ball_track_sector
            ->update(getBallPosition(), true/*ignore_vertical*/);

        if (getTicksSinceStart() > m_reset_ball_ticks &&
            !m_ball_track_sector->isOnRoad())
        {
            m_ball_invalid_timer += ticks;
            // Reset the ball and karts if out of navmesh after 2 seconds
            if (m_ball_invalid_timer >= stk_config->time2Ticks(2.0f))
            {
                {
                    m_ball_invalid_timer = 0;
                    resetKartsToSelfGoals();
                }
            }
        }
        else
            m_ball_invalid_timer = 0;
        if (m_reset_ball_ticks == World::getWorld()->getTicksSinceStart())
        {
            resetKartsToSelfGoals();
        }
    }

}   // updateBallPosition

//-----------------------------------------------------------------------------
int SoccerWorld::getBallNode() const
{
    assert(m_ball_track_sector != NULL);
    return m_ball_track_sector->getCurrentGraphNode();
}   // getBallNode

//-----------------------------------------------------------------------------
bool SoccerWorld::isCorrectGoal(unsigned int kart_id, bool first_goal) const
{
    KartTeam team = getKartTeam(kart_id);
    if (first_goal)
    {
        if (team == KART_TEAM_RED)
            return true;
    }
    else if (!first_goal)
    {
        if (team == KART_TEAM_BLUE)
            return true;
    }
    return false;
}   // isCorrectGoal

//-----------------------------------------------------------------------------
void SoccerWorld::updateAIData()
{
    if (isRaceOver()) return;

    // Fill the kart distance map
    m_red_kdm.clear();
    m_blue_kdm.clear();

    for (unsigned int i = 0; i < m_karts.size(); ++i)
    {
        if (getKartTeam(m_karts[i]->getWorldKartId()) == KART_TEAM_RED)
        {
            Vec3 rd = m_karts[i]->getXYZ() - getBallPosition();
            m_red_kdm.push_back(KartDistanceMap(i, rd.length_2d()));
        }
        else
        {
            Vec3 bd = m_karts[i]->getXYZ() - getBallPosition();
            m_blue_kdm.push_back(KartDistanceMap(i, bd.length_2d()));
        }
    }
    // Sort the vectors, so first vector will have the min distance
    std::sort(m_red_kdm.begin(), m_red_kdm.end());
    std::sort(m_blue_kdm.begin(), m_blue_kdm.end());

    // Fill Ball and goals data
    m_bgd.updateBallAndGoal(getBallPosition(), getBallHeading());

}   // updateAIData

//-----------------------------------------------------------------------------
int SoccerWorld::getAttacker(KartTeam team) const
{
    if (team == KART_TEAM_BLUE && m_blue_kdm.size() > 1)
    {
        for (unsigned int i = 1; i < m_blue_kdm.size(); i++)
        {
            // Only AI will do the attack job
            if (getKart(m_blue_kdm[i].m_kart_id)
                ->getController()->isPlayerController())
                continue;
            return m_blue_kdm[i].m_kart_id;
        }
    }
    else if (team == KART_TEAM_RED && m_red_kdm.size() > 1)
    {
        for (unsigned int i = 1; i < m_red_kdm.size(); i++)
        {
            if (getKart(m_red_kdm[i].m_kart_id)
                ->getController()->isPlayerController())
                continue;
            return m_red_kdm[i].m_kart_id;
        }
    }

    // No attacker
    return -1;
}   // getAttacker

//-----------------------------------------------------------------------------
unsigned int SoccerWorld::getRescuePositionIndex(AbstractKart *kart)
{
    if (!Track::getCurrentTrack()->hasNavMesh())
        return m_kart_position_map.at(kart->getWorldKartId());

    int last_valid_node =
        getTrackSector(kart->getWorldKartId())->getLastValidGraphNode();
    if (last_valid_node >= 0)
        return last_valid_node;
    Log::warn("SoccerWorld", "Missing last valid node for rescuing");
    return 0;
}   // getRescuePositionIndex

//-----------------------------------------------------------------------------
btTransform SoccerWorld::getRescueTransform(unsigned int rescue_pos) const
{
    if (!Track::getCurrentTrack()->hasNavMesh())
        return WorldWithRank::getRescueTransform(rescue_pos);

    const Vec3 &xyz = Graph::get()->getQuad(rescue_pos)->getCenter();
    const Vec3 &normal = Graph::get()->getQuad(rescue_pos)->getNormal();
    btTransform pos;
    pos.setOrigin(xyz);
    btQuaternion q1 = shortestArcQuat(Vec3(0.0f, 1.0f, 0.0f), normal);
    pos.setRotation(q1);
    return pos;
}   // getRescueTransform

//-----------------------------------------------------------------------------
void SoccerWorld::enterRaceOverState()
{
    WorldWithRank::enterRaceOverState();
}   // enterRaceOverState

const uint32_t SoccerWorld::ballID() const {
	return m_ball->objectID();
}

void SoccerWorld::setBallPosition(const Vec3 & p, const Vec3 & v, const Vec3 & a) {
	m_ball->reset();
	btTransform new_comt = m_ball_body->getCenterOfMassTransform();
	new_comt.setOrigin(p);
	m_ball_body->setCenterOfMassTransform(new_comt);
	m_ball_body->setLinearVelocity(v);
	m_ball_body->setAngularVelocity(a);
}
