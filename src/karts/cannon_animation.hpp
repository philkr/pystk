//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2012-2015 Joerg Henrichs
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

#ifndef HEADER_CANNON_ANIMATION_HPP
#define HEADER_CANNON_ANIMATION_HPP

#include "karts/abstract_kart_animation.hpp"
#include "utils/vec3.hpp"

#include "LinearMath/btQuaternion.h"

class AbstractKart;
class AnimationBase;
class CheckCannon;
class Flyable;
class Ipo;

/** This animation shoots the kart to a specified point on the track.
 *
 * \ingroup karts
 */

class CannonAnimation: public AbstractKartAnimation
{
protected:
friend class Flyable;
    // ------------------------------------------------------------------------
    void init(Ipo *ipo, const Vec3 &start_left, const Vec3 &start_right,
              const Vec3 &end_left, const Vec3 &end_right, float skid_rot);
    // ------------------------------------------------------------------------
    void initDeltaHeading(float skidding_rotation);
private:
    /** The \ref CheckCannon which created this animation. */
    CheckCannon*   m_check_cannon;

    /* Skidding rotation by the time the kart enter this cannon,
     * will be restored during rewind, */
    float m_skid_rot;

    /** This is the difference between the position of the kart when the
     *  cannon line is crossed and the curve interpolation at t=0. This
     *  is added to each interpolated curve value to give the final
     *  kart position (so the kart moves relative to the curve). */
    Vec3           m_delta;

    /** Stores the curve interpolation for the cannon. */
    AnimationBase *m_curve;

    /** If this animation is used for a flyable (e.g. basket ball) instead
     *  of a kart, m_flyable is defined and m_kart is NULL. */
    Flyable *m_flyable;

    /** Length of the (adjusted, i.e. taking kart width into account)
     *  start line. */
    float m_start_line_length;

    /** Length of the (adjusted, i.e. taking kart width into account) 
     *  end line. */
    float m_end_line_length;

    /** Stores the position of the kart relative to the line width
     *  at the current location. */
    float m_fraction_of_line;

    /** The initial heading of the kart when crossing the line. This is
     *  used to smoothly orient the kart towards the normal of the curve. */
    btQuaternion m_delta_heading;

    /** Current rotation of the object, saved for rewinding usage if needed,
     *  it will be compressed by MiniGLM. */
    uint32_t m_current_rotation;

public:
             CannonAnimation(AbstractKart *kart, CheckCannon* cc,
                             float skid_rot);
             CannonAnimation(Flyable *flyable, CheckCannon* cc);
             virtual ~CannonAnimation();
    virtual void  update(int ticks);
    // ------------------------------------------------------------------------
    virtual KartAnimationType getAnimationType() const   { return KAT_CANNON; }
};   // CannonAnimation
#endif
