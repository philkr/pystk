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

#include "karts/controller/local_player_controller.hpp"

#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "graphics/camera.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/particle_emitter.hpp"
#include "graphics/particle_kind.hpp"
#include "input/input.hpp"
#include "items/attachment.hpp"
#include "items/item.hpp"
#include "items/powerup.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/player_controller.hpp"
#include "karts/kart_properties.hpp"
#include "karts/skidding.hpp"
#include "karts/rescue_animation.hpp"
#include "modes/world.hpp"
#include "tracks/track.hpp"
#include "utils/constants.hpp"
#include "utils/log.hpp"
#include "utils/string_utils.hpp"

/** The constructor for a loca player kart, i.e. a player that is playing
 *  on this machine (non-local player would be network clients).
 *  \param kart_name Name of the kart.
 *  \param position The starting position (1 to n).
 *  \param player The player to which this kart belongs.
 *  \param init_pos The start coordinates and heading of the kart.
 */
LocalPlayerController::LocalPlayerController(AbstractKart *kart,
                                             const int local_player_id,
                                             PerPlayerDifficulty d)
                     : PlayerController(kart)
{
//     m_has_started = false;
    m_difficulty = d;

    // Keep a pointer to the camera to remove the need to search for
    // the right camera once per frame later.
    Camera *camera = Camera::createCamera(kart, local_player_id);

    m_camera_index = camera->getIndex();

    initParticleEmitter();
}   // LocalPlayerController

//-----------------------------------------------------------------------------
/** Destructor for a player kart.
 */
LocalPlayerController::~LocalPlayerController()
{
}   // ~LocalPlayerController

//-----------------------------------------------------------------------------
void LocalPlayerController::initParticleEmitter()
{
    // Attach Particle System
    m_sky_particles_emitter = nullptr;
    Track *track = Track::getCurrentTrack();
#ifndef SERVER_ONLY
    if (UserConfigParams::m_particles_effects > 1 &&
        track->getSkyParticles() != NULL)
    {
        track->getSkyParticles()->setBoxSizeXZ(150.0f, 150.0f);

        m_sky_particles_emitter.reset(
            new ParticleEmitter(track->getSkyParticles(),
                                core::vector3df(0.0f, 30.0f, 100.0f),
                                m_kart->getNode(),
                                true));

        // FIXME: in multiplayer mode, this will result in several instances
        //        of the heightmap being calculated and kept in memory
        m_sky_particles_emitter->addHeightMapAffector(track);
    }
#endif
}   // initParticleEmitter

//-----------------------------------------------------------------------------
/** Resets the player kart for a new or restarted race.
 */
void LocalPlayerController::reset()
{
    PlayerController::reset();
//     m_has_started = false;
}   // reset

// ----------------------------------------------------------------------------
/** Resets the state of control keys. This is used after the in-game menu to
 *  avoid that any keys pressed at the time the menu is opened are still
 *  considered to be pressed.
 */
void LocalPlayerController::resetInputState()
{
    PlayerController::resetInputState();
}   // resetInputState

// ----------------------------------------------------------------------------
/** This function interprets a kart action and value, and set the corresponding
 *  entries in the kart control data structure. This function handles esp.
 *  cases like 'press left, press right, release right' - in this case after
 *  releasing right, the steering must switch to left again. Similarly it
 *  handles 'press left, press right, release left' (in which case still
 *  right must be selected). Similarly for braking and acceleration.
 * \param action  The action to be executed.
 * \param value   If 32768, it indicates a digital value of 'fully set'
 *                if between 1 and 32767, it indicates an analog value,
 *                and if it's 0 it indicates that the corresponding button
 *                was released.
 *  \param dry_run If set it will return if this action will trigger a
 *                 state change or not.
 *  \return       True if dry_run==true and a state change would be triggered.
 *                If dry_run==false, it returns true.
 */
bool LocalPlayerController::action(PlayerAction action, int value,
                                   bool dry_run)
{
//     if (action == PA_ACCEL && value != 0 && !m_has_started)
//     {
//         m_has_started = true;
//         
//         {
//             float f = m_kart->getStartupBoostFromStartTicks(0);
//             m_kart->setStartupBoost(f);
//         }
//         
//     }

    // If this event does not change the control state (e.g.
    // it's a (auto) repeat event), do nothing. This especially
    // optimises traffic to the server and other clients.
    if (!PlayerController::action(action, value, /*dry_run*/true)) return false;

    return PlayerController::action(action, value, /*dry_run*/false);
}   // action

//-----------------------------------------------------------------------------
/** Handles steering for a player kart.
 */
void LocalPlayerController::steer(int ticks, int steer_val)
{
    PlayerController::steer(ticks, steer_val);
}   // steer

//-----------------------------------------------------------------------------
/** Updates the player kart, called once each timestep.
 */
void LocalPlayerController::update(int ticks)
{
    PlayerController::update(ticks);

    // look backward when the player requests or
    // if automatic reverse camera is active
#ifndef SERVER_ONLY
    Camera *camera = Camera::getCamera(m_camera_index);
    if (camera->getType() != Camera::CM_TYPE_END)
    {
        if (m_controls->getLookBack() || (UserConfigParams::m_reverse_look_threshold > 0 &&
            m_kart->getSpeed() < -UserConfigParams::m_reverse_look_threshold))
        {
            camera->setMode(Camera::CM_REVERSE);
            if (m_sky_particles_emitter)
            {
                m_sky_particles_emitter->setPosition(Vec3(0, 30, -100));
                m_sky_particles_emitter->setRotation(Vec3(0, 180, 0));
            }
        }
        else
        {
            if (camera->getMode() == Camera::CM_REVERSE)
            {
                camera->setMode(Camera::CM_NORMAL);
                if (m_sky_particles_emitter)
                {
                    m_sky_particles_emitter->setPosition(Vec3(0, 30, 100));
                    m_sky_particles_emitter->setRotation(Vec3(0, 0, 0));
                }
            }
        }
    }

#endif
}   // update

//-----------------------------------------------------------------------------
/** Displays a penalty warning for player controlled karts. Called from
 *  LocalPlayerKart::update() if necessary.
 */
void LocalPlayerController::displayPenaltyWarning()
{
    PlayerController::displayPenaltyWarning();
}   // displayPenaltyWarning

//-----------------------------------------------------------------------------
/** Called just before the kart position is changed. It checks if the kart was
 *  overtaken, and if so plays a sound from the overtaking kart.
 */
void LocalPlayerController::setPosition(int p)
{
    PlayerController::setPosition(p);


    if(m_kart->getPosition()<p)
    {
        World *world = World::getWorld();
        //have the kart that did the passing beep.
        //I'm not sure if this method of finding the passing kart is fail-safe.
        for(unsigned int i = 0 ; i < world->getNumKarts(); i++ )
        {
            AbstractKart *kart = world->getKart(i);
            if(kart->getPosition() == p + 1)
            {
                kart->beep();
                break;
            }
        }
    }
}   // setPosition

//-----------------------------------------------------------------------------
/** Called when a kart finishes race.
 *  /param time Finishing time for this kart.
 d*/
void LocalPlayerController::finishedRace(float time)
{
    // This will implicitly trigger setting the first end camera to be active
    Camera::changeCamera(m_camera_index, Camera::CM_TYPE_END);
}   // finishedRace

//-----------------------------------------------------------------------------
/** Called when a kart hits or uses a zipper.
 */
void LocalPlayerController::handleZipper()
{
    PlayerController::handleZipper();

    // Only play a zipper sound if it's not already playing, and
    // if the material has changed (to avoid machine gun effect
    // on conveyor belt zippers).

#ifndef SERVER_ONLY
    // Apply the motion blur according to the speed of the kart
    irr_driver->giveBoost(m_camera_index);
#endif

}   // handleZipper

//-----------------------------------------------------------------------------
/** Called when a kart hits an item. It plays certain sfx (e.g. nitro full,
 *  or item specific sounds).
 *  \param item Item that was collected.
 *  \param old_energy The previous energy value
 */
void LocalPlayerController::collectedItem(const ItemState &item_state,
                                          float old_energy)
{
}   // collectedItem

// ----------------------------------------------------------------------------
/** Returns true if the player of this controller can collect achievements.
 *  At the moment only the current player can collect them.
 *  TODO: check this, possible all local players should be able to
 *        collect achievements - synching to online account will happen
 *        next time the account gets online.
 */
bool LocalPlayerController::canGetAchievements() const 
{
    return false;
}   // canGetAchievements

// ----------------------------------------------------------------------------
core::stringw LocalPlayerController::getName() const
{
    return "";
}   // getName
