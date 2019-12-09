//
//  SuperTuxKart - a fun racing game with go-kart
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

#include "tracks/check_lap.hpp"

#include <string>

#include "io/xml_node.hpp"
#include "karts/abstract_kart.hpp"
#include "modes/linear_world.hpp"
#include "race/race_manager.hpp"
#include "tracks/track.hpp"

/** Constructor for a lap line.
 *  \param check_manager Pointer to the check manager, which is needed when
 *         resetting e.g. new lap counters.
 *  \param node XML node containing the parameters for this checkline.
 */
CheckLap::CheckLap(const XMLNode &node, unsigned int index)
         : CheckStructure(node, index)
{
    // Note that when this is called the karts have not been allocated
    // in world, so we can't call world->getNumKarts()
    m_previous_distance.resize(race_manager->getNumberOfKarts());
}   // CheckLap

// ----------------------------------------------------------------------------
void CheckLap::reset(const Track &track)
{
    CheckStructure::reset(track);
    for(unsigned int i=0; i<m_previous_distance.size(); i++)
    {
        m_previous_distance[i] = 0;
    }
}   // reset

// ----------------------------------------------------------------------------
/** True if going from old_pos to new_pos crosses this checkline. This function
 *  is called from update (of the checkline structure).
 *  \param old_pos    Position in previous frame.
 *  \param new_pos    Position in current frame.
 *  \param kart_index Index of the kart, can be used to store kart specific
 *                    additional data.
 */
bool CheckLap::isTriggered(const Vec3 &old_pos, const Vec3 &new_pos,
                           int kart_index)
{
    World* w = World::getWorld();
    LinearWorld* lin_world = dynamic_cast<LinearWorld*>(w);

    float track_length = Track::getCurrentTrack()->getTrackLength();
    // Can happen if a non-lap based race mode is used with a scene file that
    // has check defined.
    if(!lin_world)
        return false;

    // the lapline is considered crossed if the kart is on the road (off-road is not accepted)
    // near the beginning of the track while the lapline is active (meaning the proper
    // checklines were activated). "Near the beginning of the track" is arbitrarily
    // defined to be the first 1/10th of the track.
    float current_distance = lin_world->getDistanceDownTrackForKart(kart_index, false);
    float threshold = 0.1f * track_length;
    bool result = current_distance < threshold && lin_world->isOnRoad(kart_index);


    // Cannot cross lap when off-road, since we are not sure where the kart is
    if (lin_world->isOnRoad(kart_index))
        m_previous_distance[kart_index] = current_distance;

    if (result)
        lin_world->setLastTriggeredCheckline(kart_index, m_index);

    return result;
}   // isTriggered
