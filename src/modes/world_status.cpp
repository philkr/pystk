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

#include "modes/world_status.hpp"

#include "config/stk_config.hpp"
#include "graphics/irr_driver.hpp"
#include "karts/abstract_kart.hpp"
#include "modes/world.hpp"
#include "tracks/track.hpp"

#include <irrlicht.h>

//-----------------------------------------------------------------------------
WorldStatus::WorldStatus()
{
    m_clock_mode        = CLOCK_CHRONO;
    m_phase             = SETUP_PHASE;

    IrrlichtDevice *device = irr_driver->getDevice();

    if (device->getTimer()->isStopped())
        device->getTimer()->start();
}   // WorldStatus

//-----------------------------------------------------------------------------
/** Resets all status information, used when starting a new race.
 */
void WorldStatus::reset(bool restart)
{
    m_time            = 0.0f;
    m_time_ticks      = 0;
    m_count_up_ticks  = 0;
    
    // Using SETUP_PHASE will play the track into sfx first, and has no
    // other side effects.
    m_phase           = SETUP_PHASE;

    IrrlichtDevice *device = irr_driver->getDevice();

    if (device->getTimer()->isStopped())
        device->getTimer()->start();

    // Set the right music
    Track::getCurrentTrack()->startMusic();
}   // reset

//-----------------------------------------------------------------------------
/** Destructor of WorldStatus.
 */
WorldStatus::~WorldStatus()
{
    IrrlichtDevice *device = irr_driver->getDevice();

    if (device->getTimer()->isStopped())
        device->getTimer()->start();
}   // ~WorldStatus

//-----------------------------------------------------------------------------
/** Sets the clock mode and the initial time of the world clock.
 *  \param mode The new clock mode.
 *  \param initial_time The new initial time for the world clock.
 */
void WorldStatus::setClockMode(const ClockType mode, const float initial_time)
{
    m_clock_mode = mode;
    m_time_ticks = stk_config->time2Ticks(initial_time);
    m_time       = stk_config->ticks2Time(m_time_ticks);
}   // setClockMode

//-----------------------------------------------------------------------------
/** Called when the race is finished, but it still leaves some time
 *  for an end of race animation, and potentially let some more AI karts
 *  finish the race.
 */
void WorldStatus::enterRaceOverState()
{
    // Don't enter race over if it's already race over
    if (m_phase == DELAY_FINISH_PHASE || m_phase == RESULT_DISPLAY_PHASE ||
        m_phase == FINISH_PHASE)
        return;

    m_phase = DELAY_FINISH_PHASE;
}   // enterRaceOverState

//-----------------------------------------------------------------------------
/** Called when it's really over (delay over if any). This function must be
 *  called after all stats were updated from the different modes!
 */
void WorldStatus::terminateRace()
{
}   // terminateRace

//-----------------------------------------------------------------------------
/** Update, called once per frame. Called early on before physics are
 *  updated.
 *  \param dt Time step.
 */
void WorldStatus::update(int ticks)
{
}   // update

//-----------------------------------------------------------------------------
/** Updates the world time and clock (which might be running backwards), and
 *  all status information, called once per frame at the end of the main
 *  loop.
 *  \param ticks Number of ticks (physics time steps) - should be 1.
 */
void WorldStatus::updateTime(int ticks)
{
    switch (m_phase.load())
    {
        // Note: setup phase must be a separate phase, since the race_manager
        // checks the phase when updating the camera: in the very first time
        // step dt is large (it includes loading time), so the camera might
        // tilt way too much. A separate setup phase for the first frame
        // simplifies this handling
        case SETUP_PHASE:
            m_phase = RACE_PHASE;
            // event
            onGo();
            m_time_ticks = 0;

            return;   // Do not increase time
        case RACE_PHASE:
            // Nothing to do for race phase, switch to delay finish phase
            // happens when
            break;
        case DELAY_FINISH_PHASE:
        {
            m_phase = RESULT_DISPLAY_PHASE;
            break;
        }
        case RESULT_DISPLAY_PHASE:
        {
            terminateRace();
            m_phase = FINISH_PHASE;
            break;
        }
        case FINISH_PHASE:
        default: break;
    }

    IrrlichtDevice *device = irr_driver->getDevice();
    
    switch (m_clock_mode)
    {
        case CLOCK_CHRONO:
            if (!device->getTimer()->isStopped())
            {
                m_time_ticks++;
                m_time  = stk_config->ticks2Time(m_time_ticks);
                m_count_up_ticks++;
            }
            break;
        case CLOCK_COUNTDOWN:
            // stop countdown when race is over
            if (m_phase == RESULT_DISPLAY_PHASE || m_phase == FINISH_PHASE)
            {
                m_time_ticks = 0;
                m_time = 0.0f;
                m_count_up_ticks = 0;
                break;
            }

            if (!device->getTimer()->isStopped())
            {
                m_time_ticks--;
                m_time = stk_config->ticks2Time(m_time_ticks);
                m_count_up_ticks++;
            }

            if (m_time_ticks <= 0)
            {
                // event
                countdownReachedZero();
            }

            break;
        default: break;
    }   // switch m_phase

}   // update

//-----------------------------------------------------------------------------
/** Sets the time for the clock.
 *  \param time New time to set.
 */
void WorldStatus::setTime(const float time)
{
    int new_time_ticks = stk_config->time2Ticks(time);
    m_time_ticks       = new_time_ticks;
    m_time             = stk_config->ticks2Time(new_time_ticks);
}   // setTime

//-----------------------------------------------------------------------------
/** Sets a new time for the world time, measured in ticks.
 *  \param ticks New time in ticks to set.
 */
void WorldStatus::setTicks(int ticks)
{
    m_time_ticks = ticks;
    m_time = stk_config->ticks2Time(ticks);
}   // setTicks
