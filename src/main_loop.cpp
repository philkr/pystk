//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 Ingo Ruhnke <grumbel@gmx.de>
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

#include "main_loop.hpp"

#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/material_manager.hpp"
#include "graphics/sp/sp_texture_manager.hpp"
#include "input/input.hpp"
#include "modes/linear_world.hpp"
#include "modes/world.hpp"
#include "network/rewind_manager.hpp"
#include "race/history.hpp"
#include "race/race_manager.hpp"
#include "utils/profiler.hpp"
#include "utils/string_utils.hpp"
#include "utils/time.hpp"
#include "utils/translation.hpp"

#ifndef WIN32
#include <unistd.h>
#endif

MainLoop* main_loop = 0;

#ifdef WIN32
LRESULT CALLBACK separateProcessProc(_In_ HWND hwnd, _In_ UINT uMsg, 
                                     _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};
#endif

// ----------------------------------------------------------------------------
MainLoop::MainLoop(unsigned parent_pid, bool download_assets)
        : m_abort(false), m_request_abort(false), m_ticks_adjustment(0), 
          m_parent_pid(parent_pid)
{
    m_curr_time       = 0;
    m_prev_time       = 0;
    m_throttle_fps    = true;
    m_allow_large_dt  = false;
    m_frame_before_loading_world = false;
    m_download_assets = download_assets;
#ifdef WIN32
    if (parent_pid != 0)
    {
        core::stringw class_name = L"separate_process";
        class_name += StringUtils::toWString(GetCurrentProcessId());
        WNDCLASSEXW wx = {};
        wx.cbSize = sizeof(WNDCLASSEX);
        wx.lpfnWndProc = separateProcessProc;
        wx.hInstance = GetModuleHandle(0);
        wx.lpszClassName = class_name.c_str();
        if (RegisterClassExW(&wx))
        {
            CreateWindowExW(0, class_name.c_str(), L"stk_server_only",
                0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);
        }
    }
#endif
}  // MainLoop

//-----------------------------------------------------------------------------
MainLoop::~MainLoop()
{
}   // ~MainLoop

//-----------------------------------------------------------------------------
/** Returns the current dt, which guarantees a limited frame rate. If dt is
 *  too low (the frame rate too high), the process will sleep to reach the
 *  maximum frame rate.
 */
float MainLoop::getLimitedDt()
{
    m_prev_time = m_curr_time;
    float dt = 0;

    while( 1 )
    {
        m_curr_time = StkTime::getMonoTimeMs();
        if (m_prev_time > m_curr_time)
        {
            m_prev_time = m_curr_time;
        }
        dt = (float)(m_curr_time - m_prev_time);
        // On a server (i.e. without graphics) the frame rate can be under
        // 1 ms, i.e. dt = 0. Additionally, the resolution of a sleep
        // statement is not that precise either: if the sleep statement
        // would be consistent < 1ms, but the stk time would increase by
        // 1 ms, the stk clock would be desynchronised from real time
        // (it would go faster), resulting in synchronisation problems
        // with clients (server time is supposed to be behind client time).
        // So we play it safe by adding a loop to make sure at least 1ms
        // (minimum time that can be handled by the integer timer) delay here.
        while (dt == 0)
        {
            StkTime::sleep(1);
            m_curr_time = StkTime::getMonoTimeMs();
            if (m_prev_time > m_curr_time)
            {
                Log::error("MainLopp", "System clock keeps backwards!");
                m_prev_time = m_curr_time;
            }
            dt = (float)(m_curr_time - m_prev_time);
        }

        // Don't allow the game to run slower than a certain amount.
        // when the computer can't keep it up, slow down the shown time instead
        // But this can not be done in networking, otherwise the game time on
        // client and server will not be in synch anymore
        if (!m_allow_large_dt)
        {
            /* time 3 internal substeps take */
            const float MAX_ELAPSED_TIME = 3.0f*1.0f / 60.0f*1000.0f;
            if (dt > MAX_ELAPSED_TIME) dt = MAX_ELAPSED_TIME;
        }
        if (!m_throttle_fps) break;

        // Throttle fps if more than maximum, which can reduce
        // the noise the fan on a graphics card makes.
        // When in menus, reduce FPS much, it's not necessary to push to the
        // maximum for plain menus
        const int max_fps = UserConfigParams::m_max_fps;
        const int current_fps = (int)(1000.0f / dt);
        if (!m_throttle_fps || current_fps <= max_fps)  break;

        int wait_time = 1000 / max_fps - 1000 / current_fps;
        if (wait_time < 1) wait_time = 1;

        PROFILER_PUSH_CPU_MARKER("Throttle framerate", 0, 0, 0);
        StkTime::sleep(wait_time);
        PROFILER_POP_CPU_MARKER();
    }   // while(1)

    dt *= 0.001f;
    return dt;
}   // getLimitedDt

//-----------------------------------------------------------------------------
/** Updates all race related objects.
 *  \param ticks Number of ticks (physics steps) to simulate - should be 1.
 *  \param fast_forward If true, then only rewinders in network will be
 *  updated, but not the physics.
 */
void MainLoop::updateRace(int ticks, bool fast_forward)
{
    if (!World::getWorld())  return;   // No race on atm - i.e. we are in menu

    // The race event manager will update world in case of an online race
    World::getWorld()->updateWorld(ticks);
}   // updateRace

//-----------------------------------------------------------------------------
/** Run the actual main loop.
 *  The sequnce in which various parts of STK are updated is:
 *  - Determine next time step size (`getLimitedDt`). This takes maximum fps
 *    into account (i.e. sleep if the fps would be too high), and will actually
 *    slow down the in-game clock if the fps are too low (if more than 3/60 of
 *    a second have passed, more than 3 physics time steps would be needed, 
 *    and physics do at most 3 time steps).
 *  - if a race is taking place (i.e. not only a menu being shown), call
 *    `updateRace()`, which is a thin wrapper around a call to
 *    `World::updateWorld()`:
 *    - Update history manager (which will either set the kart position and/or
 *      controls when replaying, or store the current info for a replay).
 *      This is mostly for debugging only (though available even in release
 *      mode).
 *    - Updates Replays - either storing data when not replaying, or
 *      updating kart positions/control when replaying).
 *    - Calls `WorldStatus::update()`, which updates the race state (e.g.
 *      go from 'ready' to 'set' etc), and clock.
 *    - Updates the physics (`Physics::update()`). This will simulate all
 *      physical objects for the specified time with bullet.
 *    - Updates all karts (`Kart::update()`). Obviously the update function
 *      does a lot more than what is described here, this is only supposed to
 *      be a _very_ high level overview:
 *      - Updates its rewinder (to store potentially changed controls
 *        as events) in `KartRewinder::update()`.
 *      - Calls `Moveable::update()`, which takes the new position from
 *        the physics and saves it (and computes dependent values, like
 *        heading, local velocity).
 *      - Updates its controller. This is either:
 *        - an AI using `SkiddingController::update()` (which then will
 *          compute the new controls), or 
 *        - a player controller using `PlayerController::update()`, which will
 *          handle smooth steering (in case of digital input devices steering
 *          is adjusted a bit over time to avoid an instant change from all
 *          left to all right). Input events will be handled when updating
 *          the irrlicht driver later at the end of the main loop.
 *      - Updates kart animation (like rescue, ...) if one is shown atm.
 *      - Update attachments.
 *      - update physics, i.e. taking the current steering and updating
 *        the bullet raycast vehicle with that data. The settings are actually
 *        only used in the next frame when the physics are updated.
 *    - Updates all cameras via `Camera::update()`. The camera position and
 *      rotation is adjusted according to the position etc of the kart (and
 *      special circumstances like rescue, falling).
 *    - Updates all projectiles using the projectile manager. Some of the
 *      projectiles are mostly handled by the physics (e.g. a cake will mainly
 *      check if it's out of bounds), others (like basket ball) do all 
 *      their aiming and movement here.
 *    - Updates the rewind manager to store rewind states.
 *  - Updates the music manager.
 *  - Updates the input manager (which only updates internal time, actual
 *    input handling follows late)
 *  - Updates the wiimote manager. This will read the data of all wiimotes
 *    and feed the corresponding events to the irrlicht event system.
 *  - Updates the STK internal gui engine. This updates all widgets, and
 *    e.g. takes care of the rotation of the karts in the KartSelection
 *    screen using the ModelViewWidget.
 *  - Updates STK's irrlicht driver `IrrDriver::update()`:
 *    - Calls Irrlicht's `beginScene()` .
 *    - Renders the scene (several times with different viewport if
 *      split screen is being used)
 *    - Calls `GUIEngine::render()`, which renders all widgets with the
 *      help of Irrlicht's GUIEnvironment (`drawAll()`). This will also
 *      handle all events, i.e. all input is now handled (e.g. steering,
 *      firing etc are all set in the corresponding karts depending on
 *      user input).
 *    - Calls Irrlicht's `endScene()`
 */
void MainLoop::run()
{
    m_curr_time = StkTime::getMonoTimeMs();
    // DT keeps track of the leftover time, since the race update
    // happens in fixed timesteps
    float left_over_time = 0;

#ifdef WIN32
    HANDLE parent = 0;
    if (m_parent_pid != 0)
    {
        parent = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_parent_pid);
        if (parent == 0 || parent == INVALID_HANDLE_VALUE)
        {
            Log::warn("MainLoop", "Cannot open parent handle, this child "
                "may not be auto destroyed when parent is terminated");
        }
    }
#endif

    while (!m_abort)
    {
#ifdef WIN32
        if (parent != 0 && parent != INVALID_HANDLE_VALUE)
        {
            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                {
                    m_request_abort = true;
                }
            }
            // If parent is killed, abort the child main loop too
            if (WaitForSingleObject(parent, 0) != WAIT_TIMEOUT)
            {
                m_request_abort = true;
            }
        }
#else
        // POSIX equivalent
        if (m_parent_pid != 0 && getppid() != (int)m_parent_pid)
        {
            m_request_abort = true;
        }
#endif

        PROFILER_PUSH_CPU_MARKER("Main loop", 0xFF, 0x00, 0xF7);

        left_over_time += getLimitedDt();
        int num_steps   = stk_config->time2Ticks(left_over_time);
        float dt = stk_config->ticks2Time(1);
        left_over_time -= num_steps * dt ;

        // Shutdown next frame if shutdown request is sent while loading the
        // world
        if (m_request_abort)
        {
#ifndef SERVER_ONLY
            if (CVS->isGLSL() && !m_download_assets)
            {
                // Flush all command before delete world, avoid later access
                SP::SPTextureManager::get()
                    ->checkForGLCommand(true/*before_scene*/);
                // Reset screen in case the minimap was drawn
                glViewport(0, 0, irr_driver->getActualScreenSize().Width,
                    irr_driver->getActualScreenSize().Height);
            }
#endif

            // In case the user opened a race pause dialog
            if (World::getWorld())
            {
                race_manager->exitRace();
            }

            if (m_request_abort)
            {
                m_abort = true;
            }
        }

        if (!m_abort)
        {
            float frame_duration = num_steps * dt;
            {
                PROFILER_PUSH_CPU_MARKER("Update race", 0, 255, 255);
                if (World::getWorld())
                    World::getWorld()->updateGraphics(frame_duration);
                PROFILER_POP_CPU_MARKER();

                // Render the previous frame, and also handle all user input.
                PROFILER_PUSH_CPU_MARKER("IrrDriver update", 0x00, 0x00, 0x7F);
                irr_driver->update(frame_duration);
                PROFILER_POP_CPU_MARKER();
            }

            m_ticks_adjustment.lock();
            if (m_ticks_adjustment.getData() != 0)
            {
                if (m_ticks_adjustment.getData() > 0)
                {
                    num_steps += m_ticks_adjustment.getData();
                    m_ticks_adjustment.getData() = 0;
                }
                else if (m_ticks_adjustment.getData() < 0)
                {
                    int new_steps = num_steps + m_ticks_adjustment.getData();
                    if (new_steps < 0)
                    {
                        num_steps = 0;
                        m_ticks_adjustment.getData() = new_steps;
                    }
                    else
                    {
                        num_steps = new_steps;
                        m_ticks_adjustment.getData() = 0;
                    }
                }
            }
            m_ticks_adjustment.unlock();

            // Avoid hang when some function in world takes too long time or
            // when leave / come back from android home button
            bool fast_forward = false;
            for (int i = 0; i < num_steps; i++)
            {
                if (World::getWorld() && history->replayHistory())
                {
                    history->updateReplay(
                                       World::getWorld()->getTicksSinceStart());
                }

                PROFILER_PUSH_CPU_MARKER("Update race", 0, 255, 255);
                if (World::getWorld())
                {
                    updateRace(1, fast_forward);
                }
                PROFILER_POP_CPU_MARKER();

                // We need to check again because update_race may have requested
                // the main loop to abort; and it's not a good idea to continue
                // since the GUI engine is no more to be called then.
                if (m_abort || m_request_abort) 
                    break;

                if (m_frame_before_loading_world)
                {
                    // This will be called when changing introcutscene 1 and 2
                    // in CutsceneWorld::enterRaceOverState
                    // Reset the timer for correct time for cutscene
                    m_frame_before_loading_world = false;
                    m_curr_time = StkTime::getMonoTimeMs();
                    left_over_time = 0.0f;
                    break;
                }

                if (World::getWorld())
                {
                    if (World::getWorld()->getPhase()==WorldStatus::SETUP_PHASE)
                    {
                        // Skip the large num steps contributed by loading time
                        World::getWorld()->updateTime(1);
                        break;
                    }
                    World::getWorld()->updateTime(1);
                }
            }   // for i < num_steps

            // Handle controller the last to avoid slow PC sending actions too 
            // late
            {
                // User aborted (e.g. closed window)
                bool abort = !irr_driver->getDevice()->run();

                if (m_frame_before_loading_world)
                {
                    // irr_driver->getDevice()->run() loads the world
                    m_frame_before_loading_world = false;
                    m_curr_time = StkTime::getMonoTimeMs();
                    left_over_time = 0.0f;
                }

                if (abort)
                {
                    m_request_abort = true;
                }
            }
        }
        PROFILER_POP_CPU_MARKER();   // MainLoop pop
        PROFILER_SYNC_FRAME();
    }  // while !m_abort

#ifdef WIN32
    if (parent != 0 && parent != INVALID_HANDLE_VALUE)
        CloseHandle(parent);
#endif

}   // run

// ----------------------------------------------------------------------------
/** Renders the GUI. This function is used during loading a track to get a
 *  responsive GUI, and allow GUI animations (like a progress bar) to be
 *  shown.
 *  \param phase An integer indicated a phase. The maximum number of phases
 *         is used to show a progress bar. The values are between 0 and 8200.
 *  \param loop_index If the call is from a loop, the current loop index.
 *  \param loop_size The number of loop iterations. Used to smooth update
 *         e.g. a progress bar.
 */
void MainLoop::renderGUI(int phase, int loop_index, int loop_size)
{
    return;
#ifdef SERVER_ONLY
    return;
#else
    // Rendering past phase 7000 causes the minimap to not work
    // on higher graphical settings
    if (phase > 7000)
    {
        m_request_abort = !irr_driver->getDevice()->run();
        return;
    }

    uint64_t now = StkTime::getMonoTimeMs();
    float dt = (now - m_curr_time)/1000.0f;
    
    if (dt < 1.0 / 30.0f) return;

    m_curr_time = now;
    
    // TODO: remove debug output
    //Log::verbose("mainloop", "Rendergui t %llu dt %f phase %d  index %d / %d",
    //             now, dt, phase, loop_index, loop_size);

    irr_driver->update(dt, /*is_loading*/true);
    m_request_abort = !irr_driver->getDevice()->run();
    
    //TODO: remove debug output
    // uint64_t now2 = StkTime::getMonoTimeMs();
    // Log::verbose("mainloop", "  duration t %llu dt %llu", now, now2-now);
#endif
}   // renderGUI
/* EOF */
