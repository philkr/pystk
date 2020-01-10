//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 Steve Baker <sjbaker1@airmail.net>
//  Copyright (C) 2006-2015 Joerg Henrichs, Steve Baker
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


#ifndef HEADER_LOCAL_PLAYER_CONTROLLER_HPP
#define HEADER_LOCAL_PLAYER_CONTROLLER_HPP

#include "karts/controller/player_controller.hpp"
#include "network/remote_kart_info.hpp"
#include <memory>

class AbstractKart;
class ParticleEmitter;

/** PlayerKart manages control events from the player and moves
  * them to the Kart
  *
  * \ingroup controller
  */
class LocalPlayerController : public PlayerController
{
private:
//     bool           m_has_started;

    std::unique_ptr<ParticleEmitter> m_sky_particles_emitter;

    /** The index of the camera attached to the kart for this controller. The
     *  camera object is managed in the Camera class, so no need to free it. */
    int  m_camera_index;

    PerPlayerDifficulty m_difficulty;

    virtual void steer(int, int) OVERRIDE;
    virtual void displayPenaltyWarning() OVERRIDE;

public:
                 LocalPlayerController(AbstractKart *kart,
                                       const int local_player_id,
                                       PerPlayerDifficulty d);
                ~LocalPlayerController();
    void         update            (int ticks) OVERRIDE;
    bool         action            (PlayerAction action, int value,
                                    bool dry_run=false) OVERRIDE;
            void initParticleEmitter();
    virtual void handleZipper      () OVERRIDE;
    void         collectedItem     (const ItemState &item,
                                    float previous_energy=0) OVERRIDE;
    virtual void setPosition       (int p) OVERRIDE;
    virtual void reset             () OVERRIDE;
    virtual void finishedRace      (float time) OVERRIDE;
    virtual void resetInputState   () OVERRIDE;
    virtual bool canGetAchievements() const OVERRIDE;

    // ------------------------------------------------------------------------
    virtual bool isPlayerController() const OVERRIDE {return true;}
    // ------------------------------------------------------------------------
    virtual bool isLocalPlayerController() const OVERRIDE {return true;}
    // ------------------------------------------------------------------------
    /** Returns the name of the player profile. */
    core::stringw getName() const OVERRIDE;

};   // LocalPlayerController

#endif
