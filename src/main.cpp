
//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 Steve Baker <sjbaker1@airmail.net>
//  Copyright (C) 2011-2015 Joerg Henrichs, Marianne Gagnon
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


/**
 * \mainpage SuperTuxKart developer documentation
 *
 * This document contains the developer documentation for SuperTuxKart,
 * including the list of modules, the list of classes, the API reference,
 * and some pages that describe in more depth some parts of the code/engine.
 *
 * \section Overview
 *
 * Here is an overview of the high-level interactions between modules :
 \dot
 digraph interaction {
# race -> modes
 race -> tracks
 race -> karts
# modes -> tracks
# modes -> karts
 tracks -> graphics
 karts -> graphics
 tracks -> items
 items -> graphics
 animations -> graphics
 graphics -> "Antarctica/irrlicht"
# guiengine -> irrlicht
# states_screens -> guiengine
# input -> states_screens
 input -> guiengine
 guiengine -> font_system
 karts -> physics
 physics -> karts
 tracks -> physics
 ai -> controller
 controller -> karts
 input -> controller
 tracks -> animations
 physics -> animations
 animations -> physics
 karts -> audio
 physics -> audio
 "translations\n(too many connections\nto draw)"
 "configuration\n(too many connections\nto draw)"
 addons -> tracks
 addons -> karts
 guiengine -> addons
 guiengine -> race
 addons -> online_manager
 challenges -> race
# challenges -> modes
 guiengine -> challenges
 online_manager -> addons
 online_manager -> "STK Server"
 "STK Server" -> online_manager
 karts -> replay
 replay 
 # force karts and tracks on the same level, looks better this way
 subgraph { 
  rank = same; karts; tracks; 
 } 

}
 \enddot

 Note that this graph is only an approximation because the real one would be
 much too complicated :)


 \section Modules

 \li \ref addonsgroup :
   Handles add-ons that can be downloaded.
 \li \ref animations :
   This module manages interpolation-based animation (of position, rotation
   and/or scale)
 \li \ref audio :
   This module handles audio (sound effects and music).
 \li \ref challenges :
   This module handles the challenge system, which locks features (tracks, karts
   modes, etc.) until the user completes some task.
 \li \ref config :
   This module handles the user configuration, the supertuxkart configuration
   file (which contains options usually not edited by the player) and the input
   configuration file.
 \li \ref font :
   This module stores font files and tools used to draw characters in STK.
 \li \ref graphics :
   This module contains the core graphics engine, that is mostly a thin layer
   on top of irrlicht providing some additional features we need for STK
   (like particles, more scene node types, mesh manipulation tools, material
   management, etc...)
 \li \ref guiengine :
   Contains the generic GUI engine (contains the widgets and the backing logic
   for event handling, the skin, screens and dialogs). See module @ref states_screens
   for the actual STK GUI screens. Note that all input comes through this module
   too.
 \li \ref widgetsgroup :
   Contains the various types of widgets supported by the GUI engine.
 \li \ref input :
   Contains classes for input management (keyboard and gamepad)
 \li \ref io :
  Contains generic utility classes for file I/O (especially XML handling).
 \li \ref items :
   Defines the various collectibles and weapons of STK.
 \li \ref karts :
   Contains classes that deal with the properties, models and physics
   of karts.
 \li \ref controller :
   Contains kart controllers, which are either human players or AIs
   (this module thus contains the AIs)
 \li \ref modes :
   Contains the logic for the various game modes (race, follow the leader,
   battle, etc.)
 \li \ref physics :
   Contains various physics utilities.
 \li \ref race :
   Contains the race information that is conceptually above what you can find
   in group Modes. Handles highscores, grands prix, number of karts, which
   track was selected, etc.
 \li \ref states_screens :
   Contains the various screens and dialogs of the STK user interface,
   using the facilities of the guiengine module. Also contains the
   stack of menus and handles state management (in-game vs menu).
 \li \ref tracks :
   Contains information about tracks, namely drivelines, checklines and track
   objects.
 \li \ref tutorial :
   Work in progress
 */

#ifdef WIN32
#  ifdef __CYGWIN__
#    include <unistd.h>
#  endif
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  ifdef _MSC_VER
#    include <direct.h>
#  endif
#else
#  include <signal.h>
#  include <unistd.h>
#endif
#include <stdexcept>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <limits>

#include <IEventReceiver.h>

#include "main_loop.hpp"
#include "config/hardware_stats.hpp"
#include "config/player_profile.hpp"
#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "font/font_manager.hpp"
#include "graphics/camera.hpp"
#include "graphics/camera_debug.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/graphics_restrictions.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/material_manager.hpp"
#include "graphics/particle_kind_manager.hpp"
#include "graphics/referee.hpp"
#include "graphics/sp/sp_base.hpp"
#include "graphics/sp/sp_shader.hpp"
#include "input/input.hpp"
#include "io/file_manager.hpp"
#include "items/attachment_manager.hpp"
#include "items/item_manager.hpp"
#include "items/powerup_manager.hpp"
#include "items/projectile_manager.hpp"
#include "karts/combined_characteristic.hpp"
#include "karts/controller/ai_base_lap_controller.hpp"
#include "karts/kart_model.hpp"
#include "karts/kart_properties.hpp"
#include "karts/kart_properties_manager.hpp"
#include "modes/world.hpp"
#include "network/network_string.hpp"
#include "network/rewind_manager.hpp"
#include "network/rewind_queue.hpp"
#include "race/highscore_manager.hpp"
#include "race/history.hpp"
#include "race/race_manager.hpp"
#include "replay/replay_play.hpp"
#include "replay/replay_recorder.hpp"
#include "tracks/arena_graph.hpp"
#include "tracks/track.hpp"
#include "tracks/track_manager.hpp"
#include "utils/command_line.hpp"
#include "utils/constants.hpp"
#include "utils/crash_reporting.hpp"
#include "utils/leak_check.hpp"
#include "utils/log.hpp"
#include "utils/mini_glm.hpp"
#include "utils/profiler.hpp"
#include "utils/string_utils.hpp"
#include "utils/translation.hpp"

static void cleanSuperTuxKart();
static void cleanUserConfig();
void runUnitTests();

// ============================================================================
//                        gamepad visualisation screen
// ============================================================================

void gamepadVisualisation()
{

    core::array<SJoystickInfo>          irrlicht_gamepads;
    irr_driver->getDevice()->activateJoysticks(irrlicht_gamepads);


    struct Gamepad
    {
        s16   m_axis[SEvent::SJoystickEvent::NUMBER_OF_AXES];
        bool  m_button_state[SEvent::SJoystickEvent::NUMBER_OF_BUTTONS];
    };

    #define GAMEPAD_COUNT 8 // const won't work

    class EventReceiver : public IEventReceiver
    {
    public:
        Gamepad m_gamepads[GAMEPAD_COUNT];

        EventReceiver()
        {
            for (int n=0; n<GAMEPAD_COUNT; n++)
            {
                Gamepad& g = m_gamepads[n];
                for (int i=0; i<SEvent::SJoystickEvent::NUMBER_OF_AXES; i++)
                    g.m_axis[i] = 0;
                for (int i=0; i<SEvent::SJoystickEvent::NUMBER_OF_BUTTONS; i++)
                    g.m_button_state[i] = false;
            }
        }

        virtual bool OnEvent (const irr::SEvent &event)
        {
            switch (event.EventType)
            {
                case EET_JOYSTICK_INPUT_EVENT :
                {
                    const SEvent::SJoystickEvent& evt = event.JoystickEvent;
                    if (evt.Joystick >= GAMEPAD_COUNT) return true;

                    Gamepad& g = m_gamepads[evt.Joystick];
                    for (int i=0; i<SEvent::SJoystickEvent::NUMBER_OF_AXES;i++)
                    {
                        g.m_axis[i] = evt.Axis[i];
                    }
                    for (int i=0; i<SEvent::SJoystickEvent::NUMBER_OF_BUTTONS;
                         i++)
                    {
                        g.m_button_state[i] = evt.IsButtonPressed(i);
                    }
                    break;
                }

                case EET_KEY_INPUT_EVENT:
                {
                    const SEvent::SKeyInput& evt = event.KeyInput;

                    if (evt.PressedDown)
                    {
                        if (evt.Key == IRR_KEY_RETURN || 
                            evt.Key == IRR_KEY_ESCAPE ||
                            evt.Key == IRR_KEY_SPACE)
                        {
                            exit(0);
                        }
                    }

                }

                default:
                    // don't care about others
                    break;
            }
            return true;
        }
    };

    EventReceiver* events = new EventReceiver();
    irr_driver->getDevice()->setEventReceiver(events);

    while (true)
    {
        if (!irr_driver->getDevice()->run()) break;

        video::IVideoDriver* driver = irr_driver->getVideoDriver();
        const core::dimension2du size = driver ->getCurrentRenderTargetSize();

        driver->beginScene(true, true, video::SColor(255,0,0,0));

        for (int n=0; n<GAMEPAD_COUNT; n++)
        {
            Gamepad& g = events->m_gamepads[n];

            const int MARGIN = 10;
            const int x = (n & 1 ? size.Width/2 + MARGIN : MARGIN );
            const int w = size.Width/2 - MARGIN*2;
            const int h = size.Height/(GAMEPAD_COUNT/2) - MARGIN*2;
            const int y = size.Height/(GAMEPAD_COUNT/2)*(n/2) + MARGIN;

            driver->draw2DRectangleOutline( core::recti(x, y, x+w, y+h) );

            const int btn_y = y + 5;
            const int btn_x = x + 5;
            const int BTN_SIZE =
                (w - 10)/SEvent::SJoystickEvent::NUMBER_OF_BUTTONS;

            for (int b=0; b<SEvent::SJoystickEvent::NUMBER_OF_BUTTONS; b++)
            {
                core::position2di pos(btn_x + b*BTN_SIZE, btn_y);
                core::dimension2di size(BTN_SIZE, BTN_SIZE);

                if (g.m_button_state[b])
                {
                    driver->draw2DRectangle (video::SColor(255,255,0,0),
                                             core::recti(pos, size));
                }

                driver->draw2DRectangleOutline( core::recti(pos, size) );
            }

            const int axis_y = btn_y + BTN_SIZE + 5;
            const int axis_x = btn_x;
            const int axis_w = w - 10;
            const int axis_h = (h - BTN_SIZE - 15)
                            / SEvent::SJoystickEvent::NUMBER_OF_AXES;

            for (int a=0; a<SEvent::SJoystickEvent::NUMBER_OF_AXES; a++)
            {
                const float rate = g.m_axis[a] / 32767.0f;

                core::position2di pos(axis_x, axis_y + a*axis_h);
                core::dimension2di size(axis_w, axis_h);

                // Assume a default deadzone value of 4096
                const bool deadzone = (abs(g.m_axis[a]) < 4096);

                core::recti fillbar(core::position2di(axis_x + axis_w/2,
                                                      axis_y + a*axis_h),
                                    core::dimension2di( (int)(axis_w/2*rate),
                                                        axis_h)               );
                fillbar.repair(); // dimension may be negative
                driver->draw2DRectangle (deadzone ? video::SColor(255,255,0,0)
                                                  : video::SColor(255,0,255,0),
                                         fillbar);
                driver->draw2DRectangleOutline( core::recti(pos, size) );
            }
        }

        driver->endScene();
    }
}   // gamepadVisualisation

// ============================================================================
/** Sets the hat mesh name depending on the current christmas mode
 *  m_xmas_mode (0: use current date, 1: always on, 2: always off).
 */
void handleXmasMode()
{
    bool xmas = false;
    switch(UserConfigParams::m_xmas_mode)
    {
    case 0:
        {
            int day, month;
            StkTime::getDate(&day, &month);
            // Christmat hats are shown between 17. of December
            // and 5th of January
            xmas = (month == 12 && day>=17)  || (month ==  1 && day <=5);
            break;
        }
    case 1:  xmas = true;  break;
    default: xmas = false; break;
    }   // switch m_xmas_mode

    if(xmas)
        kart_properties_manager->setHatMeshName("christmas_hat.spm");
}   // handleXmasMode
// ============================================================================
/** Determines if Easter Ears should be used
 *  m_easter_ear_mode (0: use current date, 1: always on, 2: always off).
 */
bool isEasterMode(int day, int month, int year, int before_after_days)
{
    if (UserConfigParams::m_easter_ear_mode == 1) {
        return true;
    }

    if (UserConfigParams::m_easter_ear_mode == 0)
    {
        // Compute Easter date, based on wikipedia formula
        // http://en.wikipedia.org/wiki/Computus
        int a = year % 19;
        int b = year >> 2;
        int c = int(floor(b / 25)) + 1;
        int d = (c * 3) >> 2;
        int e = ((a * 19) - int(floor((c * 8 + 5) / 25)) + d + 15) % 30;
        e += (29578 - a - e * 32) >> 10;
        e -= ((year % 7) + b - d + e + 2) % 7;
        d = e >> 5;
        int easter_day = e - d * 31;
        int easter_month = d + 3;

        int easter_start_day = easter_day - before_after_days;
        int easter_start_month = easter_month;
        if (easter_start_day < 1)
        {
            easter_start_day += 31; // Month is April, going into March
            easter_start_month--;
        }
        int easter_end_day = easter_day + before_after_days;
        int easter_end_month = easter_month;
        int month_length = easter_end_month == 3 ? 31 : 30;
        if (easter_end_day > month_length)
        {
            easter_end_day -= month_length;
            easter_end_month++;
        }
        return (month > easter_start_month || (month == easter_start_month && day >= easter_start_day)) &&
               (month < easter_end_month   || (month == easter_end_month   && day <= easter_end_day));
    }

    return false;
}   // isEasterMode(day, month, year, before_after_days)

// ============================================================================
/** Wrapper around handleEasterEarMode(day, month, year, before_after_days).
 */
void handleEasterEarMode()
{
    int day, month, year;
    StkTime::getDate(&day, &month, &year);
    if (isEasterMode(day, month, year, /*before_after_days*/5))
        kart_properties_manager->setHatMeshName("easter_ears.spm");
}   // handleEasterMode

// ============================================================================
/** This function sets up all data structure for an immediate race start.
 *  It is used when the -N or -R command line options are used.
 */
void setupRaceStart()
{
    if (!kart_properties_manager->getKart(UserConfigParams::m_default_kart))
    {
        Log::warn("main", "Kart '%s' is unknown so will use the "
            "default kart.",
            UserConfigParams::m_default_kart.c_str());
        race_manager->setPlayerKart(0,
                           UserConfigParams::m_default_kart.getDefaultValue());
    }
    else
    {
        // Set up race manager appropriately
        if (race_manager->getNumPlayers() > 0)
            race_manager->setPlayerKart(0, UserConfigParams::m_default_kart);
    }
}   // setupRaceStart

// ----------------------------------------------------------------------------
/** Prints help for command line options to stdout.
 */
void cmdLineHelp()
{
    fprintf(stdout,
    "Usage: %s [OPTIONS]\n\n"
    "Run SuperTuxKart, a go-kart racing game that features "
    "Tux and friends.\n\n"
    "Options:\n"
    "  -N,  --no-start-screen  Immediately start race without showing a "
                              "menu.\n"
    "  -R,  --race-now         Same as -N but also skip the ready-set-go phase"
                              " and the music.\n"
    "  -t,  --track=NAME       Start track NAME.\n"
    "       --gp=NAME          Start the specified Grand Prix.\n"
    "       --add-gp-dir=DIR   Load Grand Prix files in DIR. Setting will be saved\n"
                              "in config.xml under additional_gp_directory. Use\n"
                              "--add-gp-dir=\"\" to unset.\n"
    "       --stk-config=FILE  use ./data/FILE instead of "
                              "./data/stk_config.xml\n"
    "  -k,  --numkarts=NUM     Set number of karts on the racetrack.\n"
    "       --kart=NAME        Use kart NAME.\n"
    "       --ai=a,b,...       Use the karts a, b, ... for the AI, and additional player kart.\n"
    "       --aiNP=a,b,...     Use the karts a, b, ... for the AI, no additional player kart.\n"
    "       --laps=N           Define number of laps to N.\n"
    "       --mode=N           N=0 Normal, N=1 Time trial, N=2 Battle, N=3 Soccer,\n"
    "                          N=4 Follow The Leader. In configure server use --battle-mode=n\n"
    "                          for battle server and --soccer-timed / goals for soccer server\n"
    "                          to control verbosely, see below:\n"
    "       --difficulty=N     N=0 Beginner, N=1 Intermediate, N=2 Expert, N=3 SuperTux.\n"
    "       --battle-mode=n    Specify battle mode in network, 0 is Free-For-All and\n"
    "                          1 is Capture The Flag.\n"
    "       --soccer-timed     Use time limit mode in network soccer game.\n"
    "       --soccer-goals     Use goals limit mode in network soccer game.\n"
    "       --reverse          Play track in reverse (if allowed)\n"
    "  -f,  --fullscreen       Use fullscreen display.\n"
    "  -w,  --windowed         Use windowed display (default).\n"
    "  -s,  --screensize=WxH   Set the display size (e.g. 320x200).\n"
    "  -v,  --version          Print version of SuperTuxKart.\n"
    "       --trackdir=DIR     A directory from which additional tracks are "
                              "loaded.\n"
    "       --seed=n           Seed for random number generation to provide reproducible behavior.\n"
    "       --profile-laps=n   Enable automatic driven profile mode for n "
                              "laps.\n"
    "       --profile-time=n   Enable automatic driven profile mode for n "
                              "seconds.\n"
    "       --unlock-all       Permanently unlock all karts and tracks for testing.\n"
    "       --no-unlock-all    Disable unlock-all (i.e. base unlocking on player achievement).\n"
    "       --no-graphics      Do not display the actual race.\n"
    "       --sp-shader-debug  Enables debug in sp shader, it will print all unavailable uniforms.\n"
    "       --demo-mode=t      Enables demo mode after t seconds of idle time in "
                               "main menu.\n"
    "       --demo-tracks=t1,t2 List of tracks to be used in demo mode. No\n"
    "                          spaces are allowed in the track names.\n"
    "       --demo-laps=n      Number of laps to use in a demo.\n"
    "       --demo-karts=n     Number of karts to use in a demo.\n"
    // "       --history          Replay history file 'history.dat'.\n"
    // "       --test-ai=n        Use the test-ai for every n-th AI kart.\n"
    // "                          (so n=1 means all Ais will be the test ai)\n"
    // "
    // "    --disable-item-collection Disable item collection. Useful for\n"
    // "                          debugging client/server item management.\n"
    // "    --network-item-debugging Print item handling debug information.\n"
    "       --server-config=file Specify the server_config.xml for server hosting, it will create\n"
    "                            one if not found.\n"
    "       --network-console  Enable network console.\n"
    "       --wan-server=name  Start a Wan server (not a playing client).\n"
    "       --public-server    Allow direct connection to the server (without stk server)\n"
    "       --lan-server=name  Start a LAN server (not a playing client).\n"
    "       --server-password= Sets a password for a server (both client&server).\n"
    "       --connect-now=ip   Connect to a server with IP known now\n"
    "                          (in format x.x.x.x:xxx(port)), the port should be its\n"
    "                          public port.\n"
    "       --server-id=n      Server id in stk addons for --connect-now.\n"
    "       --network-ai=n     Numbers of AI for connecting to linear race server, used\n"
    "                          together with --connect-now.\n"
    "       --login=s          Automatically log in (set the login).\n"
    "       --password=s       Automatically log in (set the password).\n"
    "       --init-user        Save the above login and password (if set) in config.\n"
    "       --disable-polling  Don't poll for logged in user.\n"
    "       --port=n           Port number to use.\n"
    "       --auto-connect     Automatically connect to fist server and start race\n"
    "       --max-players=n    Maximum number of clients (server only).\n"
    "       --min-players=n    Minimum number of clients for owner less server(server only).\n"
    "       --motd             Message showing in all lobby of clients, can specify a .txt file.\n"
    "       --auto-end         Automatically end network game after 1st player finished\n"
    "                          for some time (currently his finished time * 0.25 + 15.0). \n"
    "       --no-auto-end      Don't automatically end network game after 1st player finished\n"
    "       --team-choosing    Enable choosing team in lobby for team game.\n"
    "       --no-team-choosing Disable choosing team in lobby for team game.\n"
    "       --network-gp=n     Specify number of tracks used in network grand prix.\n"
    "       --graphical-server Enable graphical view in server.\n"
    "       --no-validation    Allow non validated and unencrypted connection in wan.\n"
    "       --ranked           Server will submit ranking to stk addons server.\n"
    "       --no-ranked        Server will not submit ranking to stk addons server.\n"
    "                          You require permission for that.\n"
    "       --owner-less       Race will auto start and no one can kick players in server.\n"
    "       --no-owner-less    Race will not auto start and server owner can kick players in server.\n"
    "       --firewalled-server Turn on all stun related code in server.\n"
    "       --no-firewalled-server Turn off all stun related code in server.\n"
    "       --connection-debug Print verbose info for sending or receiving packets.\n"
    "       --no-console-log   Does not write messages in the console but to\n"
    "                          stdout.log.\n"
    "  -h,  --help             Show this help.\n"
    "       --log=N            Set the verbosity to a value between\n"
    "                          0 (Debug) and 5 (Only Fatal messages)\n"
    "       --logbuffer=N      Buffers up to N lines log lines before writing.\n"
    "       --root=DIR         Path to add to the list of STK root directories.\n"
    "                          You can specify more than one by separating them\n"
    "                          with colons (:).\n"
    "       --cutscene=NAME    Launch the specified track as a cutscene.\n"
    "                          This is for internal debugging use only.\n"
    "       --enable-glow      Enable glow effect.\n"
    "       --disable-glow     Disable glow effect.\n"
    "       --enable-bloom     Enable bloom effect.\n"
    "       --disable-bloom    Disable bloom effect.\n"
    "       --enable-light-shaft Enable light shafts (God rays).\n"
    "       --disable-light-shaft Disable light shafts (God rays).\n"
    "       --enable-dof       Enable depth of field.\n"
    "       --disable-dof      Disable depth of field.\n"
    "       --enable-particles  Enable particles.\n"
    "       --disable-particles Disable particles.\n"
    "       --enable-animated-characters  Enable animated characters.\n"
    "       --disable-animated-characters Disable animated characters.\n"
    "       --enable-motion-blur Enable motion blur.\n"
    "       --disable-motion-blur Disable motion blur.\n"
    "       --enable-mlaa      Enable anti-aliasing.\n"
    "       --disable-mlaa     Disable anti-aliasing.\n"
    "       --enable-texture-compression Enable texture compression.\n"
    "       --disable-texture-compression Disable texture compression.\n"
    "       --enable-ssao      Enable screen space ambient occlusion.\n"
    "       --disable-ssao     Disable screen space ambient occlusion.\n"
    "       --enable-ibl       Enable image based lighting.\n"
    "       --disable-ibl      Disable image based lighting.\n"
    "       --enable-hd-textures Enable high definition textures.\n"
    "       --disable-hd-textures Disable high definition textures.\n"
    "       --enable-dynamic-lights Enable advanced pipline.\n"
    "       --disable-dynamic-lights Disable advanced pipline.\n"
    "       --anisotropic=n     Anisotropic filtering quality (0 to disable).\n"
    "                           Takes precedence over trilinear or bilinear\n"
    "                           texture filtering.\n"
    "       --shadows=n         Set resolution of shadows (0 to disable).\n"
    "       --apitrace          This will disable buffer storage and\n"
    "                           writing gpu query strings to opengl, which\n"
    "                           can be seen later in apitrace.\n"
#if defined(__linux__) || defined(__FreeBSD__)
    "\n"
    "Environment variables:\n"
    "       IRR_DEVICE_TYPE=[x11, wayland] Force x11/wayland device\n"
    "       IRR_DISABLE_NETWM=1            Force to use legacy fullscreen\n"
    "       IRR_VIDEO_OUTPUT=output_name   Force to use selected monitor for\n"
    "                                      fullscreen window, eg. HDMI-0\n"
#endif
    "\n"
    "You can visit SuperTuxKart's homepage at "
    "https://supertuxkart.net\n\n",
    CommandLine::getExecName().c_str()
    );
}   // cmdLineHelp

//=============================================================================
/** For base options that modify the output (loglevel/color) or exit right
 * after being processed (version/help).
 */
int handleCmdLineOutputModifier()
{
    if (CommandLine::has("--help") || CommandLine::has("-help") ||
        CommandLine::has("-h"))
    {
        cmdLineHelp();
        cleanUserConfig();
        exit(0);
    }

    if(CommandLine::has("--version") || CommandLine::has("-v"))
    {
        Log::info("main", "==============================");
        Log::info("main", "SuperTuxKart, %s.", STK_VERSION ) ;
        Log::info("main", "==============================");
        cleanUserConfig();
        exit(0);
    }

    int n;
    if(CommandLine::has("--log", &n))
        Log::setLogLevel(n);
    if (CommandLine::has("--logbuffer", &n))
        Log::setBufferSize(n);

    if(CommandLine::has("--log=nocolor"))
    {
        Log::disableColor();
        Log::verbose("main", "Colours disabled.");
    }
    if(CommandLine::has("--no-console-log"))
        Log::toggleConsoleLog(false);

    return 0;
}

//=============================================================================
/** For base options that don't need much to be inited (and, in some cases,
 *  that need to be read before initing stuff) - it only assumes that
 *  user config is loaded (necessary to check for blacklisted screen
 *  resolutions), but nothing else (esp. not kart_properties_manager and
 *  track_manager, since their search path might be extended by command
 *  line options).
 */
int handleCmdLinePreliminary()
{
    if(CommandLine::has("--debug=memory"))
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_MEMORY;
    if(CommandLine::has("--debug=addons"))
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_ADDONS;
    if(CommandLine::has("--debug=mgui"))
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_GUI;
    if(CommandLine::has("--debug=flyable"))
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_FLYABLE;
    if(CommandLine::has("--debug=mist"))
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_MISC;
    if(CommandLine::has("--debug=all") )
        UserConfigParams::m_verbosity |= UserConfigParams::LOG_ALL;
    if(CommandLine::has("--online"))
        History::m_online_history_replay = true;
#if !(defined(SERVER_ONLY) || defined(ANDROID))
    if(CommandLine::has("--apitrace"))
    {
        SP::sp_apitrace = true;
    }
#endif

    std::string s;
    if(CommandLine::has("--stk-config", &s))
    {
        stk_config->load(file_manager->getAsset(s));
        Log::info("main", "STK config will be read from %s.",s.c_str());
    }
    if(CommandLine::has("--trackdir", &s))
        TrackManager::addTrackSearchDir(s);
    if(CommandLine::has("--kartdir", &s))
        KartPropertiesManager::addKartSearchDir(s);

    if (CommandLine::has("--sp-shader-debug"))
        SP::SPShader::m_sp_shader_debug = true;

    if(CommandLine::has("--screensize", &s) || CommandLine::has("-s", &s))
    {
        //Check if fullscreen and new res is blacklisted
        int width, height;
        if (sscanf(s.c_str(), "%dx%d", &width, &height) == 2)
        {
            // Reassemble the string in case that the original width or
            // height contained a leading 0
            std::ostringstream o;
            o << width << "x" << height;
            std::string res = o.str();
            if (!UserConfigParams::m_fullscreen ||
                std::find(UserConfigParams::m_blacklist_res.begin(),
                UserConfigParams::m_blacklist_res.end(),res) ==
                UserConfigParams::m_blacklist_res.end())
            {
                UserConfigParams::m_prev_width =
                    UserConfigParams::m_width = width;
                UserConfigParams::m_prev_height =
                    UserConfigParams::m_height = height;
                Log::verbose("main", "You choose to use %dx%d.",
                    (int)UserConfigParams::m_width,
                    (int)UserConfigParams::m_height );
            }
            else
                Log::warn("main", "Resolution %s has been blacklisted, so "
                "it is not available!", res.c_str());
        }
        else
        {
            Log::fatal("main", "Error: --screensize argument must be "
                "given as WIDTHxHEIGHT");
        }
    }

    if(CommandLine::has("--fullscreen") || CommandLine::has("-f"))
    {
        // Check that current res is not blacklisted
        std::ostringstream o;
        o << UserConfigParams::m_width << "x" << UserConfigParams::m_height;
        std::string res = o.str();
        if (std::find(UserConfigParams::m_blacklist_res.begin(),
                      UserConfigParams::m_blacklist_res.end(),res)
                   == UserConfigParams::m_blacklist_res.end())
            UserConfigParams::m_fullscreen = true;
        else
            Log::warn("main", "Resolution %s has been blacklisted, so it "
            "is not available!", res.c_str());
    }

    if(CommandLine::has("--windowed") || CommandLine::has("-w"))
        UserConfigParams::m_fullscreen = false;

    // toggle graphical options
    if (CommandLine::has("--enable-glow"))
        UserConfigParams::m_glow = true;
    else if (CommandLine::has("--disable-glow"))
        UserConfigParams::m_glow = false;
    if (CommandLine::has("--enable-bloom"))
        UserConfigParams::m_bloom = true;
    else if (CommandLine::has("--disable-bloom"))
        UserConfigParams::m_bloom = false;
    if (CommandLine::has("--enable-light-shaft"))
        UserConfigParams::m_light_shaft = true;
    else if (CommandLine::has("--disable-light-shaft"))
        UserConfigParams::m_light_shaft = false;
    if (CommandLine::has("--enable-dynamic-lights"))
        UserConfigParams::m_dynamic_lights = true;
    else if (CommandLine::has("--disable-dynamic-lights"))
        UserConfigParams::m_dynamic_lights = false;
    // depth of field
    if (CommandLine::has("--enable-dof"))
        UserConfigParams::m_dof = true;
    else if (CommandLine::has("--disable-dof"))
        UserConfigParams::m_dof = false;
    // particles effects
    if (CommandLine::has("--enable-particles"))
        UserConfigParams::m_particles_effects = 2;
    else if (CommandLine::has("--disable-particles"))
        UserConfigParams::m_particles_effects = 0;
    // animated characters
    if (CommandLine::has("--enable-animated-characters"))
        UserConfigParams::m_animated_characters = true;
    else if (CommandLine::has("--disable-animated-characters"))
        UserConfigParams::m_animated_characters = false;
    if (CommandLine::has("--enable-motion-blur"))
        UserConfigParams::m_motionblur = true;
    else if (CommandLine::has("--disable-motion-blur"))
        UserConfigParams::m_motionblur = false;
    // anti-aliasing
    if (CommandLine::has("--enable-mlaa"))
        UserConfigParams::m_mlaa = true;
    else if (CommandLine::has("--disable-mlaa"))
        UserConfigParams::m_mlaa = false;
    if (CommandLine::has("--enable-texture-compression"))
        UserConfigParams::m_texture_compression = true;
    else if (CommandLine::has("--disable-texture-compression"))
        UserConfigParams::m_texture_compression = false;
    // screen space ambient occluison
    if (CommandLine::has("--enable-ssao"))
        UserConfigParams::m_ssao = true;
    else if (CommandLine::has("--disable-ssao"))
        UserConfigParams::m_ssao = false;
    // image based lighting
    if (CommandLine::has("--enable-ibl"))
        UserConfigParams::m_degraded_IBL = false;
    else if (CommandLine::has("--disable-ibl"))
        UserConfigParams::m_degraded_IBL = true;
    // high definition textures user choice
    if (CommandLine::has("--enable-hd-textures"))
        UserConfigParams::m_high_definition_textures =  2 | 1;
    else if (CommandLine::has("--disable-hd-textures"))
        UserConfigParams::m_high_definition_textures = 2;

    int n;
    if(CommandLine::has("--xmas", &n))
        UserConfigParams::m_xmas_mode = n;
    if (CommandLine::has("--easter", &n))
        UserConfigParams::m_easter_ear_mode = n;
    if (CommandLine::has("--shadows", &n))
        UserConfigParams::m_shadows_resolution = n;
    if (CommandLine::has("--anisotropic", &n))
        UserConfigParams::m_anisotropic = n;

    // Useful for debugging: the temple navmesh needs 12 minutes in debug
    // mode to compute the distance matrix!!
    if(CommandLine::has("--dont-load-navmesh"))
        Track::m_dont_load_navmesh = true;

    if (CommandLine::has("--seed", &n))
    {
        srand(n);
        Log::info("main", "STK using random seed (%d)", n);
    }

    return 0;
}   // handleCmdLinePreliminary

// ============================================================================
/** Handles command line options.
 *  \param argc Number of command line options
 */
int handleCmdLine(bool has_server_config, bool has_parent_process)
{
    // Some generic variables used in scanning:
    int n;
    std::string s;

    irr::core::stringw login, password;

    if(CommandLine::has("--ai-debug"))
        AIBaseController::enableDebug();
    if(CommandLine::has("--test-ai", &n))
        AIBaseController::setTestAI(n);
    if (CommandLine::has("--rewind") )
        RewindManager::setEnable(true);
    if (CommandLine::has( "--difficulty", &s))
    {
        int n = atoi(s.c_str());
        if (n < 0 || n > RaceManager::DIFFICULTY_LAST)
        {
            Log::warn("main", "Invalid difficulty '%s', use easy.\n",
                      s.c_str());
            race_manager->setDifficulty(RaceManager::Difficulty(0));
        }
        else
        {
            race_manager->setDifficulty(RaceManager::Difficulty(n));
        }
    }   // --difficulty

    if (CommandLine::has("--mode", &n))
    {
        switch (n)
        {
        // The order here makes server creation screen easier
        case 0:
        {
            race_manager->setMinorMode(RaceManager::MINOR_MODE_NORMAL_RACE);
            break;
        }
        case 1:
        {
            race_manager->setMinorMode(RaceManager::MINOR_MODE_TIME_TRIAL);
            break;
        }
        case 2:
        {
            race_manager->setMinorMode(RaceManager::MINOR_MODE_FREE_FOR_ALL);
            break;
        }
        case 3:
        {
            race_manager->setMinorMode(RaceManager::MINOR_MODE_SOCCER);
            break;
        }
        case 4:
        {
            race_manager->setMinorMode(RaceManager::MINOR_MODE_FOLLOW_LEADER);
            break;
        }
        default:
            Log::warn("main", "Invalid race mode '%d' - ignored.", n);
        }
    }   // --mode

    const bool is_soccer =
        race_manager->getMinorMode() == RaceManager::MINOR_MODE_SOCCER;
    const bool is_battle = race_manager->isBattleMode();

    if (CommandLine::has("--disable-item-collection"))
        ItemManager::disableItemCollection();

    // Race parameters
    if(CommandLine::has("--kartsize-debug"))
    {
        for(unsigned int i=0; i<kart_properties_manager->getNumberOfKarts();
           i++)
        {
            const KartProperties *km =
                kart_properties_manager->getKartById(i);
            Log::info("main", "%s:\t%swidth: %f length: %f height: %f "
                      "mesh-buffer count %d",
                      km->getIdent().c_str(),
                      (km->getIdent().size()<7) ? "\t" : "",
                      km->getMasterKartModel().getWidth(),
                      km->getMasterKartModel().getLength(),
                      km->getMasterKartModel().getHeight(),
                      km->getMasterKartModel().getModel()
                        ->getMeshBufferCount());
        }    // for i
    }   // --kartsize-debug

    if(CommandLine::has("--kart", &s))
    {
        const KartProperties *prop = kart_properties_manager->getKart(s);
        if (prop)
        {
            UserConfigParams::m_default_kart = s;

            // if a player was added with -N, change its kart.
            // Otherwise, nothing to do, kart choice will be picked
            // up upon player creation.
            race_manager->setPlayerKart(0, s);
            Log::verbose("main", "You chose to use kart '%s'.",
                         s.c_str());
        }
        else
        {
            Log::warn("main", "Kart '%s' not found, ignored.",
                      s.c_str());
        }
    }   // if --kart

    if(CommandLine::has("--ai", &s))
    {
        const std::vector<std::string> l=StringUtils::split(std::string(s),',');
        race_manager->setDefaultAIKartList(l);
        // Add 1 for the player kart
        race_manager->setNumKarts((int)l.size()+1);
    }   // --ai

    if(CommandLine::has("--aiNP", &s))
    {
        const std::vector<std::string> l=StringUtils::split(std::string(s),',');
        race_manager->setDefaultAIKartList(l);
        race_manager->setNumKarts((int)l.size());
    }   // --aiNP

    if(CommandLine::has("--track", &s) || CommandLine::has("-t", &s))
    {
        race_manager->setTrack(s);
        Log::verbose("main", "You chose to start in track '%s'.",
                     s.c_str());

        Track* t = track_manager->getTrack(s);
        if (!t)
        {
            Log::warn("main", "Can't find track named '%s'.", s.c_str());
        }
        else if (t->isArena())
        {
            //if it's arena, don't create AI karts
            const std::vector<std::string> l;
            race_manager->setDefaultAIKartList(l);
            // Add 1 for the player kart
            race_manager->setNumKarts(1);
            race_manager->setMinorMode(RaceManager::MINOR_MODE_3_STRIKES);
        }
        else if (t->isSoccer())
        {
            //if it's soccer, don't create AI karts
            const std::vector<std::string> l;
            race_manager->setDefaultAIKartList(l);
            // Add 1 for the player kart
            race_manager->setNumKarts(1);
            race_manager->setMinorMode(RaceManager::MINOR_MODE_SOCCER);
        }
    }   // --track

    if(CommandLine::has("--numkarts", &n) ||CommandLine::has("-k", &n))
    {
        UserConfigParams::m_default_num_karts = n;
        if(UserConfigParams::m_default_num_karts > stk_config->m_max_karts)
        {
            Log::warn("main", "Number of karts reset to maximum number %d.",
                      stk_config->m_max_karts);
            UserConfigParams::m_default_num_karts = stk_config->m_max_karts;
        }
        race_manager->setNumKarts( UserConfigParams::m_default_num_karts );
        Log::verbose("main", "%d karts will be used.",
                     (int)UserConfigParams::m_default_num_karts);
    }   // --numkarts

    UserConfigParams::m_race_now = true;

    if(CommandLine::has("--laps", &s))
    {
        int laps = atoi(s.c_str());
        if (laps < 0)
        {
            Log::error("main", "Invalid number of laps: %s.\n", s.c_str());
            return 0;
        }
        else
        {
            Log::verbose("main", "You chose to have %d laps.", laps);
            race_manager->setNumLaps(laps);
        }
    }   // --laps
    
    if(CommandLine::has("--history"))
    {
        history->setReplayHistory(true);
    }   // --history

#ifdef __APPLE__
    // on OS X, sometimes the Finder will pass a -psn* something parameter
    // to the application --> ignore it
    CommandLine::has("-psn");
#endif

    CommandLine::reportInvalidParameters();

    return 1;
}   // handleCmdLine

//=============================================================================
/** Initialises the minimum number of managers to get access to user_config.
 */
void initUserConfig()
{
    file_manager = new FileManager();
    user_config  = new UserConfig();     // needs file_manager
    user_config->loadConfig();
    // Some parts of the file manager needs user config (paths for models
    // depend on artist debug flag). So init the rest of the file manager
    // after reading the user config file.
    file_manager->init();

    translations            = new Translations();   // needs file_manager
    stk_config              = new STKConfig();      // in case of --stk-config
                                                    // command line parameters
}   // initUserConfig

//=============================================================================
void clearGlobalVariables()
{
    // In android sometimes global variables is not reset when restart the app
    // we clear it here as much as possible
    race_manager = NULL;
    irr_driver = NULL;
#ifdef ENABLE_WIIUSE
    wiimote_manager = NULL;
#endif
}   // clearGlobalVariables

//=============================================================================
void initRest()
{
    SP::setMaxTextureSize();
    irr_driver = new IrrDriver();

    if (irr_driver->getDevice() == NULL)
    {
        Log::fatal("main", "Couldn't initialise irrlicht device. Quitting.\n");
    }

    StkTime::init();   // grabs the timer object from the irrlicht device

    // Now create the actual non-null device in the irrlicht driver
    irr_driver->initDevice();

    // Init GUI
    IrrlichtDevice* device = irr_driver->getDevice();
    video::IVideoDriver* driver = device->getVideoDriver();

    font_manager = new FontManager();
    font_manager->loadFonts();

    SP::loadShaders();
    // The order here can be important, e.g. KartPropertiesManager needs
    // defaultKartProperties, which are defined in stk_config.
    history                 = new History              ();
    ReplayPlay::create();
    ReplayRecorder::create();
    material_manager        = new MaterialManager      ();
    track_manager           = new TrackManager         ();
    kart_properties_manager = new KartPropertiesManager();
    projectile_manager      = new ProjectileManager    ();
    powerup_manager         = new PowerupManager       ();
    attachment_manager      = new AttachmentManager    ();
    highscore_manager       = new HighscoreManager     ();

    // The maximum texture size can not be set earlier, since
    // e.g. the background image needs to be loaded in high res.
    irr_driver->setMaxTextureSize();
    KartPropertiesManager::addKartSearchDir(
                 file_manager->getAddonsFile("karts/"));
    track_manager->addTrackSearchDir(
                 file_manager->getAddonsFile("tracks/"));

    {
        XMLNode characteristicsNode(file_manager->getAsset("kart_characteristics.xml"));
        kart_properties_manager->loadCharacteristics(&characteristicsNode);
    }

    track_manager->loadTrackList();

    race_manager            = new RaceManager          ();
    // default settings for Quickstart
    race_manager->setNumPlayers(1);
    race_manager->setNumLaps   (3);
    race_manager->setMinorMode (RaceManager::MINOR_MODE_NORMAL_RACE);
    race_manager->setDifficulty(
                 (RaceManager::Difficulty)(int)UserConfigParams::m_difficulty);

    if (!track_manager->getTrack(UserConfigParams::m_last_track))
        UserConfigParams::m_last_track.revertToDefaults();

    race_manager->setTrack(UserConfigParams::m_last_track);

}   // initRest

//=============================================================================
void askForInternetPermission()
{
    return;
}   // askForInternetPermission

//=============================================================================

#if defined(WIN32) && defined(_MSC_VER)
    #ifdef DEBUG
        #pragma comment(linker, "/SUBSYSTEM:console")
    #else
        #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
    #endif
#endif

// ----------------------------------------------------------------------------
#ifdef ANDROID
extern "C"
{
#endif
void main_abort()
{
    if (main_loop)
    {
        main_loop->requestAbort();
    }
}
#ifdef ANDROID
}
#endif

// ----------------------------------------------------------------------------
#ifdef IOS_STK
int ios_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    clearGlobalVariables();
    CommandLine::init(argc, argv);

    CrashReporting::installHandlers();
#ifndef WIN32
    signal(SIGTERM, [](int signum)
        {
            main_abort();
        });
#endif
    srand(( unsigned ) time( 0 ));

    try
    {
        std::string s, server_config;

        handleCmdLineOutputModifier();

        if (CommandLine::has("--server-config", &s))
        {
            const std::string& base_name = StringUtils::getBasename(s);
            if (base_name.find(".xml") != std::string::npos)
            {
                server_config = s;
                FileManager::setStdoutName(
                    StringUtils::removeExtension(base_name) + ".log");
            }
        }

        if(CommandLine::has("--root", &s))
            FileManager::addRootDirs(s);
        if (CommandLine::has("--stdout", &s))
            FileManager::setStdoutName(s);
        if (CommandLine::has("--stdout-dir", &s))
            FileManager::setStdoutDir(s);

        // Init the minimum managers so that user config exists, then
        // handle all command line options that do not need (or must
        // not have) other managers initialised:
        initUserConfig();

        CommandLine::addArgsFromUserConfig();

        handleCmdLinePreliminary();

        stk_config->load(file_manager->getAsset("stk_config.xml"));

        profiler.init();
        initRest();

        int parent_pid;
        bool has_parent_process = false;
        if (CommandLine::has("--parent-process", &parent_pid))
        {
            main_loop = new MainLoop(parent_pid);
            has_parent_process = true;
        }
        else
            main_loop = new MainLoop(0/*parent_pid*/);
        material_manager->loadMaterial();

        // Preload the explosion effects (explode.png)
        ParticleKindManager::get()->getParticles("explosion.xml");
        ParticleKindManager::get()->getParticles("explosion_bomb.xml");
        ParticleKindManager::get()->getParticles("explosion_cake.xml");
        ParticleKindManager::get()->getParticles("jump_explosion.xml");

        kart_properties_manager -> loadAllKarts    ();
        handleXmasMode();
        handleEasterEarMode();

        projectile_manager->loadData();

        // Both item_manager and powerup_manager load models and therefore
        // textures from the model directory. To avoid reading the
        // materials.xml twice, we do this here once for both:
        file_manager->pushTextureSearchPath(file_manager->getAsset(FileManager::MODEL,""), "models");
        const std::string materials_file =
            file_manager->getAsset(FileManager::MODEL,"materials.xml");
        if(materials_file!="")
        {
            // Some of the materials might be needed later, so just add
            // them all permanently (i.e. as shared). Adding them temporary
            // will actually not be possible: powerup_manager adds some
            // permanent icon materials, which would (with the current
            // implementation) make the temporary materials permanent anyway.
            material_manager->addSharedMaterial(materials_file);
        }
        Referee::init();
        powerup_manager->loadPowerupsModels();
        ItemManager::loadDefaultItemMeshes();

        attachment_manager->loadModels();
        file_manager->popTextureSearchPath();

        //handleCmdLine() needs InitTuxkart() so it can't be called first
        if (!handleCmdLine(!server_config.empty(), has_parent_process))
            exit(0);

        setupRaceStart();

        // Replay a race
        // =============
        if(history->replayHistory())
        {
            // This will setup the race manager etc.
            history->Load();
            if (!History::m_online_history_replay)
            {
                race_manager->setupPlayerKartInfo();
                race_manager->startNew();
                main_loop->run();
                // The run() function will only return if the user aborts.
                Log::flushBuffers();
                exit(-3);
            }   // if !online
        }
        {
            // Quickstart (-N)
            // ===============
            // all defaults are set in InitTuxkart()
            race_manager->setupPlayerKartInfo();
            race_manager->startNew();
        }
        main_loop->run();

    }  // try
    catch (std::exception &e)
    {
        Log::flushBuffers();
        Log::error("main", "Exception caught : %s.",e.what());
        Log::error("main", "Aborting SuperTuxKart.");
        Log::flushBuffers();
    }

    /* Program closing...*/

#ifdef ENABLE_WIIUSE
    if(wiimote_manager)
        delete wiimote_manager;
#endif

    cleanSuperTuxKart();

#ifdef DEBUG
    MemoryLeaks::checkForLeaks();
#endif

    Log::flushBuffers();

#ifndef WIN32
    if (user_config) //close logfiles
    {
        Log::closeOutputFiles();
#endif
#ifndef ANDROID
        fclose(stderr);
        fclose(stdout);
#endif
#ifndef WIN32
    }
#endif

    delete file_manager;

    return 0 ;
}   // main

// ============================================================================
#ifdef WIN32
//routine for running under windows
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
}
#endif

//=============================================================================
/** Frees all manager and their associated memory.
 */
static void cleanSuperTuxKart()
{

    delete main_loop;

    // Stop music (this request will go into the sfx manager queue, so it needs
    // to be done before stopping the thread).
    irr_driver->updateConfigIfRelevant();
    Referee::cleanup();
    if(race_manager)            delete race_manager;
    if(highscore_manager)       delete highscore_manager;
    if(attachment_manager)      delete attachment_manager;
    ItemManager::removeTextures();
    if(powerup_manager)         delete powerup_manager;
    if(projectile_manager)      delete projectile_manager;
    if(kart_properties_manager) delete kart_properties_manager;
    if(track_manager)           delete track_manager;
    if(material_manager)        delete material_manager;
    if(history)                 delete history;
    ReplayPlay::destroy();
    ReplayRecorder::destroy();
    delete ParticleKindManager::get();
    if(font_manager)            delete font_manager;

    // Now finish shutting down objects which a separate thread. The
    // RequestManager has been signaled to shut down as early as possible,
    // the NewsManager thread should have finished quite early on anyway.
    // But still give them some additional time to finish. It avoids a
    // race condition where a thread might access the file manager after it
    // was deleted (in cleanUserConfig below), but before STK finishes and
    // the OS takes all threads down.
    // The add-ons manager might still be called from a currenty running request
    // in the request manager, so it can not be deleted earlier.

    cleanUserConfig();
}   // cleanSuperTuxKart

//=============================================================================
/**
 * Frees all the memory of initUserConfig()
 */
static void cleanUserConfig()
{
    if(stk_config)              delete stk_config;
    if(translations)            delete translations;
    if (user_config)
    {
        // In case that abort is triggered before user_config exists
        if (UserConfigParams::m_crashed) UserConfigParams::m_crashed = false;
        user_config->saveConfig();
        delete user_config;
    }

    if(irr_driver)              delete irr_driver;
}   // cleanUserConfig

//=============================================================================
void runUnitTests()
{
    Log::info("UnitTest", "Starting unit testing");
    Log::info("UnitTest", "=====================");
    Log::info("UnitTest", "MiniGLM");
    MiniGLM::unitTesting();
    Log::info("UnitTest", "GraphicsRestrictions");
    GraphicsRestrictions::unitTesting();
    Log::info("UnitTest", "StringUtils::versionToInt");
    StringUtils::unitTesting();

    Log::info("UnitTest", "Easter detection");
    // Test easter mode: in 2015 Easter is 5th of April - check with 0 days
    // before and after
    int saved_easter_mode = UserConfigParams::m_easter_ear_mode;
    UserConfigParams::m_easter_ear_mode = 0;   // disable always on or off mode
    assert( isEasterMode( 5, 4, 2015, 0));
    assert(!isEasterMode( 4, 4, 2015, 0));
    assert(!isEasterMode( 6, 4, 2015, 0));

    assert( isEasterMode( 1, 4, 2018, 0));
    assert( isEasterMode(27, 3, 2016, 0));

    // Check days before/after
    assert( isEasterMode( 2, 4, 2015, 3));
    assert(!isEasterMode( 1, 4, 2015, 3));
    assert( isEasterMode( 8, 4, 2015, 3));
    assert(!isEasterMode( 9, 4, 2015, 3));

    // Check if going to previous month is handled correctly: 1/4/2018
    assert( isEasterMode(27, 3, 2018, 5));
    assert(!isEasterMode(26, 3, 2018, 5));
    assert( isEasterMode( 6, 4, 2018, 5));
    assert(!isEasterMode( 7, 4, 2018, 5));

    // Check if going to previous month is handled correctly: 1/4/2018
    assert( isEasterMode( 1, 4, 2016, 5));
    assert(!isEasterMode( 2, 4, 2016, 5));
    assert( isEasterMode(22, 3, 2016, 5));
    assert(!isEasterMode(21, 3, 2016, 5));
    UserConfigParams::m_easter_ear_mode = saved_easter_mode;

    Log::info("UnitTest", "PowerupManager");
    PowerupManager::unitTesting();

    Log::info("UnitTest", "Kart characteristics");
    CombinedCharacteristic::unitTesting();

    Log::info("UnitTest", "Arena Graph");
    ArenaGraph::unitTesting();

    Log::info("UnitTest", "Fonts for translation");
    font_manager->unitTesting();

    Log::info("UnitTest", "RewindQueue");
    RewindQueue::unitTesting();

    Log::info("UnitTest", "=====================");
    Log::info("UnitTest", "Testing successful   ");
    Log::info("UnitTest", "=====================");
}   // runUnitTests
