
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
#include "achievements/achievements_manager.hpp"
#include "addons/addons_manager.hpp"
#include "addons/news_manager.hpp"
#include "challenges/unlock_manager.hpp"
#include "config/hardware_stats.hpp"
#include "config/player_manager.hpp"
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
#include "guiengine/engine.hpp"
#include "guiengine/event_handler.hpp"
#include "guiengine/dialog_queue.hpp"
#include "input/device_manager.hpp"
#include "input/input_manager.hpp"
#include "input/keyboard_device.hpp"
#include "input/wiimote_manager.hpp"
#include "io/file_manager.hpp"
#include "items/attachment_manager.hpp"
#include "items/item_manager.hpp"
#include "items/network_item_manager.hpp"
#include "items/powerup_manager.hpp"
#include "items/projectile_manager.hpp"
#include "karts/combined_characteristic.hpp"
#include "karts/controller/ai_base_lap_controller.hpp"
#include "karts/kart_model.hpp"
#include "karts/kart_properties.hpp"
#include "karts/kart_properties_manager.hpp"
#include "modes/cutscene_world.hpp"
#include "modes/demo_world.hpp"
#include "modes/profile_world.hpp"
#include "network/protocols/connect_to_server.hpp"
#include "network/protocols/client_lobby.hpp"
#include "network/protocols/server_lobby.hpp"
#include "network/network_config.hpp"
#include "network/network_string.hpp"
#include "network/rewind_manager.hpp"
#include "network/rewind_queue.hpp"
#include "network/server.hpp"
#include "network/server_config.hpp"
#include "network/servers_manager.hpp"
#include "network/stk_host.hpp"
#include "network/stk_peer.hpp"
#include "online/profile_manager.hpp"
#include "online/request_manager.hpp"
#include "race/grand_prix_manager.hpp"
#include "race/highscore_manager.hpp"
#include "race/history.hpp"
#include "race/race_manager.hpp"
#include "replay/replay_play.hpp"
#include "replay/replay_recorder.hpp"
#include "states_screens/main_menu_screen.hpp"
#include "states_screens/online/networking_lobby.hpp"
#include "states_screens/online/register_screen.hpp"
#include "states_screens/state_manager.hpp"
#include "states_screens/options/user_screen.hpp"
#include "states_screens/dialogs/init_android_dialog.hpp"
#include "states_screens/dialogs/message_dialog.hpp"
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

// ============================================================================
/** This function sets up all data structure for an immediate race start.
 *  It is used when the -N or -R command line options are used.
 */
void setupRaceStart()
{
    // Skip the start screen. This esp. means that no login screen is
    // displayed (if necessary), so we have to make sure there is
    // a current player
    PlayerManager::get()->enforceCurrentPlayer();

    InputDevice *device;

    // Use keyboard 0 by default in --no-start-screen
    device = input_manager->getDeviceManager()->getKeyboard(0);

    // Create player and associate player with keyboard
    StateManager::get()->createActivePlayer(
        PlayerManager::get()->getPlayer(0), device);

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

    // ASSIGN should make sure that only input from assigned devices
    // is read.
    input_manager->getDeviceManager()->setAssignMode(ASSIGN);
}   // setupRaceStart


struct PySTKConfig {
	int screen_width=600, screen_height=400;
	bool glow = true, bloom = true, light_shaft = true, dynamic_lights = true, dof = true;
	int particles_effects = 2;
	bool animated_characters = true;
	bool motionblur = true;
	bool mlaa = true;
	bool texture_compression = true;
	bool ssao = true;
	bool degraded_IBL = true;
	int high_definition_textures = 2 | 1;
	
	int difficulty = 2;
	RaceManager::MinorRaceModeType mode = RaceManager::MINOR_MODE_NORMAL_RACE;
	std::string kart, track;
	int laps = 3;
};

int setupConfig(const PySTKConfig & config) {
	UserConfigParams::m_fullscreen = false;
	UserConfigParams::m_prev_width  = UserConfigParams::m_width  = config.screen_width;
	UserConfigParams::m_prev_height = UserConfigParams::m_height = config.screen_height;
	UserConfigParams::m_glow = config.glow;
	UserConfigParams::m_bloom = config.bloom;
	UserConfigParams::m_light_shaft = config.light_shaft;
	UserConfigParams::m_dynamic_lights = config.dynamic_lights;
	UserConfigParams::m_dof = config.dof;
	UserConfigParams::m_particles_effects = config.particles_effects;
	UserConfigParams::m_animated_characters = config.animated_characters;
	UserConfigParams::m_motionblur = config.motionblur;
	UserConfigParams::m_animated_characters = config.animated_characters;
	UserConfigParams::m_mlaa = config.mlaa;
	UserConfigParams::m_texture_compression=  config.texture_compression;
	UserConfigParams::m_ssao = config.ssao;
	UserConfigParams::m_degraded_IBL = config.degraded_IBL;
	UserConfigParams::m_high_definition_textures = config.high_definition_textures;
	
	race_manager->setDifficulty(RaceManager::Difficulty(config.difficulty));
	race_manager->setMinorMode(config.mode);
	
	const KartProperties *prop = kart_properties_manager->getKart(config.kart);
	if (prop)
	{
		UserConfigParams::m_default_kart = config.kart;

		// if a player was added with -N, change its kart.
		// Otherwise, nothing to do, kart choice will be picked
		// up upon player creation.
		if (StateManager::get()->activePlayerCount() > 0)
		{
			race_manager->setPlayerKart(0, config.kart);
		}
		Log::verbose("main", "You chose to use kart '%s'.",
						config.kart.c_str());
	}
	else
	{
		Log::warn("main", "Kart '%s' not found, ignored.",
					config.kart.c_str());
	}
	if (config.track.length())
		race_manager->setTrack(config.track);
	
	UserConfigParams::m_no_start_screen = true;
	UserConfigParams::m_race_now = true;
	
	race_manager->setNumLaps(config.laps);
	
	UserConfigParams::m_unlock_everything = 2;
	
// 	race_manager->setDefaultAIKartList(l);
// 	race_manager->setNumKarts( UserConfigParams::m_default_num_karts );
}

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
    if (UserConfigParams::m_language.toString() != "system")
    {
#ifdef WIN32
        std::string s=std::string("LANGUAGE=")
                     +UserConfigParams::m_language.c_str();
        _putenv(s.c_str());
#else
        setenv("LANGUAGE", UserConfigParams::m_language.c_str(), 1);
#endif
    }

    translations            = new Translations();   // needs file_manager
    stk_config              = new STKConfig();      // in case of --stk-config
                                                    // command line parameters
}   // initUserConfig

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
    GUIEngine::init(device, driver, StateManager::get());

    // This only initialises the non-network part of the add-ons manager. The
    // online section of the add-ons manager will be initialised from a
    // separate thread running in network HTTP.
#ifndef SERVER_ONLY
    addons_manager = NULL;
    if (!ProfileWorld::isNoGraphics())
        addons_manager = new AddonsManager();
#endif
    Online::ProfileManager::create();

    // The request manager will start the login process in case of a saved
    // session, so we need to read the main data from the players.xml file.
    // The rest will be read later (since the rest needs the unlock- and
    // achievement managers to be created, which can only be created later).
    PlayerManager::create();
    Online::RequestManager::get()->startNetworkThread();
#ifndef SERVER_ONLY
    if (!ProfileWorld::isNoGraphics())
        NewsManager::get();   // this will create the news manager
#endif

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

    GUIEngine::addLoadingIcon(irr_driver->getTexture(FileManager::GUI_ICON,
                                                     "notes.png"      ) );

    grand_prix_manager      = new GrandPrixManager     ();
    // Consistency check for challenges, and enable all challenges
    // that have all prerequisites fulfilled
    grand_prix_manager->checkConsistency();
    GUIEngine::addLoadingIcon( irr_driver->getTexture(FileManager::GUI_ICON,
                                                      "cup_gold.png"    ) );

    race_manager            = new RaceManager          ();
    // default settings for Quickstart
    race_manager->setNumPlayers(1);
    race_manager->setNumLaps   (3);
    race_manager->setMajorMode (RaceManager::MAJOR_MODE_SINGLE);
    race_manager->setMinorMode (RaceManager::MINOR_MODE_NORMAL_RACE);
    race_manager->setDifficulty(
                 (RaceManager::Difficulty)(int)UserConfigParams::m_difficulty);

    if (!track_manager->getTrack(UserConfigParams::m_last_track))
        UserConfigParams::m_last_track.revertToDefaults();

    race_manager->setTrack(UserConfigParams::m_last_track);

}   // initRest

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
int main(int argc, char *argv[] )
{
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
        // Init the minimum managers so that user config exists, then
        // handle all command line options that do not need (or must
        // not have) other managers initialised:
        initUserConfig();
        stk_config->load(file_manager->getAsset("stk_config.xml"));
        if (!ProfileWorld::isNoGraphics())
            profiler.init();
        initRest();


		PySTKConfig config;
		
		// TODO: Load the config
		
        setupConfig(config);

        input_manager = new InputManager ();

        // Get into menu mode initially.
        input_manager->setMode(InputManager::MENU);
		main_loop = new MainLoop(0/*parent_pid*/);
        material_manager->loadMaterial();

        // Preload the explosion effects (explode.png)
        ParticleKindManager::get()->getParticles("explosion.xml");

        GUIEngine::addLoadingIcon( irr_driver->getTexture(FileManager::GUI_ICON,
                                                          "options_video.png"));
        kart_properties_manager -> loadAllKarts    ();

        // Needs the kart and track directories to load potential challenges
        // in those dirs, so it can only be created after reading tracks
        // and karts.
        unlock_manager = new UnlockManager();
        AchievementsManager::create();

        // Reading the rest of the player data needs the unlock manager to
        // initialise the game slots of all players and the AchievementsManager
        // to initialise the AchievementsStatus, so it is done only now.
        PlayerManager::get()->initRemainingData();

        GUIEngine::addLoadingIcon( irr_driver->getTexture(FileManager::GUI_ICON,
                                                          "gui_lock.png"  ) );
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

        GUIEngine::addLoadingIcon( irr_driver->getTexture(FileManager::GUI_ICON,
                                                          "gift.png")       );

        attachment_manager->loadModels();
        file_manager->popTextureSearchPath();

        GUIEngine::addLoadingIcon( irr_driver->getTexture(FileManager::GUI_ICON,
                                                          "banana.png")    );
/*

#ifndef SERVER_ONLY
        if (!ProfileWorld::isNoGraphics())
        {
            addons_manager->checkInstalledAddons();

            // Load addons.xml to get info about add-ons even when not
            // allowed to access the Internet
            if (UserConfigParams::m_internet_status !=
                Online::RequestManager::IPERM_ALLOWED)
            {
                std::string xml_file = file_manager->getAddonsFile("addonsX.xml");
                if (file_manager->fileExists(xml_file))
                {
                    try
                    {
                        const XMLNode *xml = new XMLNode(xml_file);
                        addons_manager->initAddons(xml);
                    }
                    catch (std::runtime_error& e)
                    {
                        Log::warn("Addons", "Exception thrown when initializing add-ons manager : %s", e.what());
                    }
                }
            }
        }
#endif*/
/*
        if(UserConfigParams::m_unit_testing)
        {
            runUnitTests();
            exit(0);
        }*/

		setupRaceStart();
            // Go straight to the race
		StateManager::get()->enterGameState();
		
		race_manager->setupPlayerKartInfo();
		race_manager->startNew(false);
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

    // If the window was closed in the middle of a race, remove players,
    // so we don't crash later when StateManager tries to access input devices.
    StateManager::get()->resetActivePlayers();
    if (input_manager)
    {
        delete input_manager;
        input_manager = NULL;
    }

    if (STKHost::existHost())
        STKHost::get()->shutdown();

    cleanSuperTuxKart();
    NetworkConfig::destroy();

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
                     LPTSTR lpCmdLine, int nCmdShow)
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

    if(Online::RequestManager::isRunning())
        Online::RequestManager::get()->stopNetworkThread();

    // Stop music (this request will go into the sfx manager queue, so it needs
    // to be done before stopping the thread).
    irr_driver->updateConfigIfRelevant();
    AchievementsManager::destroy();
    Referee::cleanup();
    if(race_manager)            delete race_manager;
    if(grand_prix_manager)      delete grand_prix_manager;
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
    PlayerManager::destroy();
    if(unlock_manager)          delete unlock_manager;
    Online::ProfileManager::destroy();
    GUIEngine::DialogQueue::deallocate();
    GUIEngine::clear();
    GUIEngine::cleanUp();
    GUIEngine::clearScreenCache();
    if(font_manager)            delete font_manager;

    // Now finish shutting down objects which a separate thread. The
    // RequestManager has been signaled to shut down as early as possible,
    // the NewsManager thread should have finished quite early on anyway.
    // But still give them some additional time to finish. It avoids a
    // race condition where a thread might access the file manager after it
    // was deleted (in cleanUserConfig below), but before STK finishes and
    // the OS takes all threads down.

#ifndef SERVER_ONLY
    if (!ProfileWorld::isNoGraphics())
    {
        if (UserConfigParams::m_internet_status == Online::RequestManager::
            IPERM_ALLOWED && !NewsManager::get()->waitForReadyToDeleted(2.0f))
        {
            Log::info("Thread", "News manager not stopping, exiting anyway.");
        }
        NewsManager::deallocate();
    }
#endif

    if (Online::RequestManager::get()->waitForReadyToDeleted(5.0f))
    {
        Online::RequestManager::deallocate();
    }
    else
    {
        Log::warn("Thread", "Request Manager not aborting in time, proceeding without cleanup.");
    }

    // The add-ons manager might still be called from a currenty running request
    // in the request manager, so it can not be deleted earlier.
#ifndef SERVER_ONLY
    if(addons_manager)  delete addons_manager;
#endif

    ServersManager::deallocate();
    cleanUserConfig();

    StateManager::deallocate();
    GUIEngine::EventHandler::deallocate();
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
