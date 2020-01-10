
//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015  Steve Baker <sjbaker1@airmail.net>
//  Copyright (C) 2006-2015  Eduardo Hernandez Munoz
//  Copyright (C) 2010-2015  Joerg Henrichs
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

#ifndef HEADER_SKIDDING_AI_HPP
#define HEADER_SKIDDING_AI_HPP

// Some debugging features for the AI. For example you can visualise the
// point the AI is aiming at, or visualise the curve the AI is predicting.
// It works best with just 1 AI kart, so set the number of karts
// to 2 in main.cpp with quickstart and run supertuxkart with the arg -N.
// Or use --profile-laps=99 and run just one AI. Using the debug camera
// (top view) is useful, too

#ifdef DEBUG
   // Enable AI graphical debugging
#  undef AI_DEBUG
   // Shows left and right lines when using new findNonCrashing function
#  undef AI_DEBUG_NEW_FIND_NON_CRASHING
   // Show the predicted turn circles
#  undef AI_DEBUG_CIRCLES
   // Show the heading of the kart
#  undef AI_DEBUG_KART_HEADING
   // Shows line from kart to its aim point
#  undef AI_DEBUG_KART_AIM
#endif


#include "karts/controller/ai_base_lap_controller.hpp"
#include "race/race_manager.hpp"
#include "tracks/drive_node.hpp"
#include "utils/random_generator.hpp"

#include <line3d.h>

class ItemState;
class LinearWorld;
class Track;

namespace irr
{
    namespace scene
    {
        class ISceneNode;
    }
}

/**
\brief This is the actual racing AI.

The main entry point, called once per frame for each AI, is update().
After handling some standard cases (race start, AI being rescued)
the AI does the following steps:
- compute nearest karts (one ahead and one behind)
- check if the kart is about to crash with another kart or the
  track. This is done by simply testing a certain number of timesteps
  ahead and estimating the future position of any kart by using
  current_position  + velocity * time
  (so turns are not taken into account). It also checks if the kart
  would be outside the quad graph, which indicates a 'collision with
  track' (though technically this only means the kart would be off track).
  This information is stored in the m_crashes data structure.
- Determine track direction (straight, left, or right), which the
  function determineTrackDirection stores in m_current_track_direction
- If the kart has a bomb attached, it will try to hit the kart ahead,
  using nitro if necessary. The kart will aim at the target kart,
  nothing els is done (idea: if the kart has a plunger, fire it).
- Otherwise, the AI will:
  - set acceleration (handleAcceleration)
  - decide where to steer to (handleSteering()): it will first check if it
    is outside of the track, and if so, steer towards the center of the
    next quad. If it was detected that the AI is going to hit another
    kart, it will try to avoid this. Otherwise it will aim at the center
    of the quad furthest away so that a straight line from the current
    position to this center is on track (see findNonCrashingPoint).
    There are actually three different implementations of this, but the
    (somewhat buggy) default one results in reality with the best AI
    behaviour.
    The function handleSteering() then calls setSteering() to set the
    actually steering amount. The latter function also decides if skidding
    should be done or not (by calling canSkid()).
  - decide if to try to collect or avoid items (handeItems).
    It considers all items on quads between the current quad of the kart
    and the quad the AI is aiming at (see handleSteering). If it finds
    an item to collect, it pre-selects this items, which means it will
    not select another item for collection until this pre-selected item
    is clearly uncollectable (gone or too far out of the way). This avoids
    problems that the AI is between two items it can collects, and keeps
    switching between both items, at the end missing both.
  - detects if the AI is stuck and needs rescue (handleRescue)
  - decides if it needs to brake (handlebraking)
  - decides if nitro or zipper should be used
- Finally, it checks if it has a zipper but selected to use nitro, and
  under certain circumstances will use zipper instead of nitro.

\ingroup controller
*/
class SkiddingAI : public AIBaseLapController
{
private:

    class CrashTypes
    {
        public:

        bool m_road; //true if we are going to 'crash' with the bounds of the road
        int m_kart; //-1 if no crash, pos numbers are the kart it crashes with
        CrashTypes() : m_road(false), m_kart(-1) {};
        void clear() {m_road = false; m_kart = -1;}
    } m_crashes;

    /*General purpose variables*/

    /** Pointer to the closest kart ahead of this kart. NULL if this
     *  kart is first. */
    AbstractKart *m_kart_ahead;

    /** Distance to the kart ahead. */
    float m_distance_ahead;

    /** Pointer to the closest kart behind this kart. NULL if this kart
     *  is last. */
    AbstractKart *m_kart_behind;

    /** Distance to the kard behind. */
    float m_distance_behind;

    /** Distance to the leader kart (used only in FTL)
        If this kart is leader, contains a high value
        to avoid the leader slowing down */
    float m_distance_leader;


    /** Time an item has been collected and not used. */
    float m_time_since_last_shot;

    float m_time_since_stuck;

    /** Direction of crash: -1 = left, 1 = right, 0 = no crash. */
    int m_start_kart_crash_direction;

    /** The direction of the track where the kart is on atm. */
    DriveNode::DirectionType m_current_track_direction;

    /** The radius of the curve the kart is currently driving. Undefined
     *  when being on a straigt section. */
    float m_current_curve_radius;

    /** Stores the center of the curve (if the kart is in a curve,
     *  otherwise undefined). */
    Vec3  m_curve_center;

    /** The index of the last node with the same direction as the current
     *  node the kart is on. If kart is in a left turn, this will be
     *  the last node that is still turning left etc. */
    unsigned int m_last_direction_node;

    /** If set an item that the AI should aim for. */
    const ItemState *m_item_to_collect;

    /** True if items to avoid are close by. Used to avoid using zippers
     *  (which would make it more difficult to avoid items). */
    bool m_avoid_item_close;

    /** Distance to the player, used for rubber-banding. */
    float m_distance_to_player;

    /** Number of players ahead, used for rubber-banding. */
    int m_num_players_ahead;

    /** This bool allows to make the AI use nitro by series of two bursts */
    bool m_burster;

    /** This implements a simple finite state machine: it starts in
     *  NOT_YET. The first time the AI decides to skid, the state is changed
     *  randomly (depending on skid probability) to NO_SKID or SKID.
     *  As long as the AI keeps on deciding to skid, the state remains
     *  unchanged (so no new random decision is made) till it decides
     *  not to skid. In which case the state is set to NOT_YET again.
     *  This guarantees that for each 'skidable' section of the track
     *  the random decision is only done once. */
    enum {SKID_PROBAB_NOT_YET, SKID_PROBAB_NO_SKID, SKID_PROBAB_SKID}
          m_skid_probability_state;

    /** This is used by computeSkill to know what skill is used */
    enum SkillType {ITEM_SKILL, NITRO_SKILL};

    /** The last item selected for collection, for which a probability
     *  was determined. */
    const ItemState *m_last_item_random;

    /** True if m_last_item_random was randomly selected to be collected. */
    bool m_really_collect_item;
    
    /** A random number generator for collecting items. */
    RandomGenerator m_random_collect_item;

    /** \brief Determines the algorithm to use to select the point-to-aim-for
     *  There are two different Point Selection Algorithms:
     *  1. findNonCrashingPoint() is the default (which is actually slightly
     *     buggy, but so far best one after handling of 90 degree turns was
     *     added).
     *  2. findNonCrashingPointNew() A newly designed algorithm, which is
     *     faster than a fixed version of findNonCrashingPoint, but does not
     *     give as good results as the 'buggy' one.
     *
     *  So far the default one has by far the best performance, even though
     *  it has bugs. */
    enum {PSA_DEFAULT, PSA_NEW}
          m_point_selection_algorithm;

#ifdef AI_DEBUG
    /** For skidding debugging: shows the estimated turn shape. */
    ShowCurve **m_curve;

    /** For debugging purpose: a sphere indicating where the AI
     *  is targeting at. */
    irr::scene::ISceneNode *m_debug_sphere[4];

    /** For item debugging: set to the item that is selected to
     *  be collected. */
    irr::scene::ISceneNode *m_item_sphere;
#endif


    /*Functions called directly from update(). They all represent an action
     *that can be done, and end up setting their respective m_controls
     *variable, except handle_race_start() that isn't associated with any
     *specific action (more like, associated with inaction).
     */
    void  handleRaceStart();
    void  handleAccelerationAndBraking(int ticks);
    void  handleSteering(float dt);
    int   computeSkill(SkillType type);
    void  handleItems(const float dt, const Vec3 *aim_point,
                                int last_node, int item_skill);
    void  handleBubblegum(int item_skill,
                          const std::vector<const ItemState *> &items_to_collect,
                          const std::vector<const ItemState *> &items_to_avoid);
    void  handleCake(int item_skill);
    void  handleBowling(int item_skill);
    void  handleSwatter(int item_skill);
    void  handleSwitch(int item_skill,
                       const std::vector<const ItemState *> &items_to_collect,
                       const std::vector<const ItemState *> &items_to_avoid);
    void  handleRescue(const float dt);
    void  handleBraking(float max_turn_speed, float min_speed);
    void  handleNitroAndZipper(float max_safe_speed);
    void  computeNearestKarts();
    void  handleItemCollectionAndAvoidance(Vec3 *aim_point,
                                           int last_node);
    bool  handleSelectedItem(Vec3 kart_aim_direction, Vec3 *aim_point);
    bool  steerToAvoid(const std::vector<const ItemState *> &items_to_avoid,
                       const core::line3df &line_to_target,
                       Vec3 *aim_point);
    bool  hitBadItemWhenAimAt(const ItemState *item,
                              const std::vector<const ItemState *> &items_to_avoid);
    void  evaluateItems(const ItemState *item, Vec3 kart_aim_direction,
                        std::vector<const ItemState *> *items_to_avoid,
                        std::vector<const ItemState *> *items_to_collect);

    void  checkCrashes(const Vec3& pos);
    void  findNonCrashingPointNew(Vec3 *result, int *last_node);
    void  findNonCrashingPoint(Vec3 *result, int *last_node);

    void  determineTrackDirection();
    virtual bool canSkid(float steer_fraction);
    virtual void setSteering(float angle, float dt);
    void handleCurve();

protected:
    virtual unsigned int getNextSector(unsigned int index);

public:
                 SkiddingAI(AbstractKart *kart);
                ~SkiddingAI();
    virtual void update      (int ticks);
    virtual void reset       ();
    virtual const irr::core::stringw& getNamePostfix() const;
};

#endif

/* EOF */
