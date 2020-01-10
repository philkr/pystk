//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2015      Joerg Henrichs
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

#ifndef HEADER_AI_BASE_CONTROLLER_HPP
#define HEADER_AI_BASE_CONTROLLER_HPP

#include "karts/controller/controller.hpp"
#include "utils/cpp2011.hpp"
#include "utils/random_generator.hpp"

class AIProperties;
class Track;
class Vec3;

/** A base class for all AI karts. This class basically provides some
 *  common low level functions.
 * \ingroup controller
 */
class AIBaseController : public Controller
{
private:
    /** Stores the last N times when a collision happened. This is used
    *  to detect when the AI is stuck, i.e. N collisions happened in
    *  a certain period of time. */
    std::vector<int> m_collision_ticks;

    /** A flag that is set during the physics processing to indicate that
    *  this kart is stuck and needs to be rescued. */
    bool m_stuck;

protected:
    /** A random number generator for all AI decisions. */
    RandomGenerator m_random;

    /** Length of the kart, storing it here saves many function calls. */
    float m_kart_length;

    /** Cache width of kart. */
    float m_kart_width;

    /** Keep a pointer to the track to reduce calls */
    Track *m_track;

    /** A pointer to the AI properties for this kart. */
    const AIProperties *m_ai_properties;

    void         setControllerName(const std::string &name) OVERRIDE;
    float        steerToPoint(const Vec3 &point);
    float        normalizeAngle(float angle);
    // ------------------------------------------------------------------------
    /** This can be called to detect if the kart is stuck (i.e. repeatedly
    *  hitting part of the track). */
    bool         isStuck() const { return m_stuck; }
    // ------------------------------------------------------------------------
    void         determineTurnRadius(const Vec3 &end, Vec3 *center,
                                     float *radius) const;
    virtual void setSteering   (float angle, float dt);
    // ------------------------------------------------------------------------
    /** Return true if AI can skid now. */
    virtual bool canSkid(float steer_fraction) = 0;

public:
             AIBaseController(AbstractKart *kart);
    virtual ~AIBaseController() {};
    virtual void reset() OVERRIDE;
    virtual bool disableSlipstreamBonus() const OVERRIDE;
    virtual void crashed(const Material *m) OVERRIDE;
    virtual void crashed(const AbstractKart *k) OVERRIDE {};
    virtual void handleZipper() OVERRIDE {};
    virtual void finishedRace(float time) OVERRIDE {};
    virtual void collectedItem(const ItemState &item,
                               float previous_energy=0) OVERRIDE {};
    virtual void setPosition(int p) OVERRIDE {};
    virtual bool isPlayerController() const OVERRIDE { return false; }
    virtual bool isLocalPlayerController() const OVERRIDE { return false; }
    virtual bool action(PlayerAction action, int value, bool dry_run=false) OVERRIDE
    {
        return true;
    };
    virtual void skidBonusTriggered() OVERRIDE {}
    // ------------------------------------------------------------------------
    virtual void update(int ticks) OVERRIDE;

};   // AIBaseController

#endif

/* EOF */
