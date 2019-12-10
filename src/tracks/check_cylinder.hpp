//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009-2015  Joerg Henrichs
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

#ifndef HEADER_CHECK_CYLINDER_HPP
#define HEADER_CHECK_CYLINDER_HPP

#include "tracks/check_structure.hpp"
#include <functional>

class XMLNode;
class CheckManager;
class TriggerItemListener;

/** This class implements a check sphere that is used to change the ambient
 *  light if a kart is inside this sphere. Besides a normal radius this
 *  sphere also has a 2nd 'inner' radius: player karts inside the inner
 *  radius will have the full new ambient light, karts outside the default
 *  light, and karts in between will mix the light dependent on distance.
 *
 * \ingroup tracks
 */
class CheckCylinder : public CheckStructure
{
private:
    /** Center of the sphere. */
    Vec3         m_center_point;
    /** Squared radius of the cylinder. */
    float        m_radius2;
    float        m_height;
    /** A flag for each kart to indicate if it's inside of the sphere. */
    std::vector<bool> m_is_inside;
    /** Stores the distance of each kart from the center of this sphere.
     *  This saves some computations. */
    std::vector<float> m_distance2;
    /** Function to call when triggered. */
    std::function<void(int)> m_triggering_function;
public:
                 CheckCylinder(const XMLNode &node,
                     std::function<void(int)> triggering_function);
    virtual     ~CheckCylinder() {};
    virtual bool isTriggered(const Vec3 &old_pos, const Vec3 &new_pos,
                             int kart_id);
    // ------------------------------------------------------------------------
    /** Returns if kart indx is currently inside of the sphere. */
    bool isInside(int index) const            { return m_is_inside[index]; }
    // -------------------------------------------------------------------------
    /** Returns the squared distance of kart index from the enter of
     *  this sphere. */
    float getDistance2ForKart(int index) const { return m_distance2[index];}
    // -------------------------------------------------------------------------
    /** Returns the square of the radius of this sphere. */
    float getRadius2() const { return m_radius2; }
};   // CheckCylinder

#endif

