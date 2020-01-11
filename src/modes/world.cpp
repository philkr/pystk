//
//  SuperTuxKart - a fun racing game with go-kart
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

#include "modes/world.hpp"

#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "graphics/camera.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/material.hpp"
#include "graphics/material_manager.hpp"
#include "graphics/render_info.hpp"
#include "io/file_manager.hpp"
#include "input/input.hpp"
#include "items/projectile_manager.hpp"
#include "karts/controller/battle_ai.hpp"
#include "karts/controller/end_controller.hpp"
#include "karts/controller/local_player_controller.hpp"
#include "karts/controller/skidding_ai.hpp"
#include "karts/controller/soccer_ai.hpp"
#include "karts/controller/spare_tire_ai.hpp"
#include "karts/kart.hpp"
#include "karts/kart_model.hpp"
#include "karts/kart_properties_manager.hpp"
#include "physics/btKart.hpp"
#include "physics/physics.hpp"
#include "physics/triangle_mesh.hpp"
#include "race/race_manager.hpp"
#include "scriptengine/script_engine.hpp"
#include "tracks/check_manager.hpp"
#include "tracks/track.hpp"
#include "tracks/track_manager.hpp"
#include "tracks/track_object.hpp"
#include "tracks/track_object_manager.hpp"
#include "utils/constants.hpp"
#include "utils/profiler.hpp"
#include "utils/string_utils.hpp"

#include <algorithm>
#include <assert.h>
#include <ctime>
#include <sstream>
#include <stdexcept>


World* World::m_world = NULL;

/** The main world class is used to handle the track and the karts.
 *  The end of the race is detected in two phases: first the (abstract)
 *  function isRaceOver, which must be implemented by all game modes,
 *  must return true. In which case enterRaceOverState is called. At
 *  this time a winning (or losing) animation can be played. The WorldStatus
 *  class will in its enterRaceOverState switch to DELAY_FINISH_PHASE,
 *  but the remaining AI kart will keep on racing during that time.
 *  After a time period specified in stk_config.xml WorldStatus will
 *  switch to FINISH_PHASE and call terminateRace. Now the finishing status
 *  of all karts is set (i.e. in a normal race the arrival time for karts
 *  will be estimated), highscore is updated, and the race result gui
 *  is being displayed.
 *  Rescuing is handled via the three functions:
 *  getNumberOfRescuePositions() - which returns the number of rescue
 *           positions defined.
 *  getRescuePositionIndex(AbstractKart *kart) - which determines the
 *           index of the rescue position to be used for the given kart.
 *  getRescueTransform(unsigned int index) - which returns the transform
 *           (i.e. position and rotation) for the specified rescue
 *           position.
 *  This allows the world class to do some tests to make sure all rescue
 *  positions are valid (when started with --track-debug). It tries to
 *  place all karts on all rescue positions. If there are any problems
 *  (e.g. a rescue position not over terrain (perhaps because it is too
 *  low); or the rescue position is on a texture which will immediately
 *  trigger another rescue), a warning message will be printed.
 */

//-----------------------------------------------------------------------------
/** Constructor. Note that in the constructor it is not possible to call any
 *  functions that use World::getWorld(), since this is only defined
 *  after the constructor. Those functions must be called in the init()
 *  function, which is called immediately after the constructor.
 */
World::World() : WorldStatus()
{
#ifdef DEBUG
    m_magic_number = 0xB01D6543;
#endif

    m_schedule_exit_race = false;
    m_schedule_tutorial  = false;
    m_is_network_world   = false;

    m_stop_music_when_dialog_open = true;

    WorldStatus::setClockMode(CLOCK_CHRONO);

}   // World

// ----------------------------------------------------------------------------
/** This function is called after instanciating. The code here can't be moved
 *  to the contructor as child classes must be instanciated, otherwise
 *  polymorphism will fail and the results will be incorrect . Also in init()
 *  functions can be called that use World::getWorld().
 */
void World::init()
{
    m_faster_music_active = false;
    m_fastest_kart        = 0;
    m_eliminated_karts    = 0;
    m_eliminated_players  = 0;
    m_num_players         = 0;
    m_red_ai = m_blue_ai = 0;

    // Create the race gui before anything else is attached to the scene node
    // (which happens when the track is loaded). This allows the race gui to
    // do any rendering on texture. Note that this function can NOT be called
    // in the World constuctor, since it might be overwritten by a the game
    // mode class, which would not have been constructed at the time that this
    // constructor is called, so the wrong race gui would be created.
    // Grab the track file
    Track *track = track_manager->getTrack(race_manager->getTrackName());
    Scripting::ScriptEngine::getInstance<Scripting::ScriptEngine>();
    if(!track)
    {
        std::ostringstream msg;
        msg << "Track '" << race_manager->getTrackName()
            << "' not found.\n";
        throw std::runtime_error(msg.str());
    }

    std::string script_path = track->getTrackFile("scripting.as");
    Scripting::ScriptEngine::getInstance()->loadScript(script_path, true);
    // Create the physics
    Physics::getInstance<Physics>();
    unsigned int num_karts = race_manager->getNumberOfKarts();
    //assert(num_karts > 0);

    // Load the track models - this must be done before the karts so that the
    // karts can be positioned properly on (and not in) the tracks.
    // This also defines the static Track::getCurrentTrack function.
    track->loadTrackModel(race_manager->getReverseTrack());

    // Assign team of AIs for team mode before createKart
    if (hasTeam())
        setAITeam();

    for(unsigned int i=0; i<num_karts; i++)
    {
        std::string kart_ident = race_manager->getKartIdent(i);
        int local_player_id  = race_manager->getKartLocalPlayerId(i);
        int global_player_id = race_manager->getKartGlobalPlayerId(i);
        std::shared_ptr<AbstractKart> new_kart;
        if (hasTeam())
        {
            new_kart = createKartWithTeam(kart_ident, i, local_player_id,
                global_player_id, race_manager->getKartType(i),
                race_manager->getPlayerDifficulty(i));
        }
        else
        {
            new_kart = createKart(kart_ident, i, local_player_id,
                global_player_id, race_manager->getKartType(i),
                race_manager->getPlayerDifficulty(i));
        }
        new_kart->setBoostAI(race_manager->hasBoostedAI(i));
        m_karts.push_back(new_kart);
    }  // for i

    // Load other custom models if needed
    loadCustomModels();

    powerup_manager->computeWeightsForRace(race_manager->getNumberOfKarts());
    if (UserConfigParams::m_particles_effects > 1)
    {
        Weather::getInstance<Weather>();   // create Weather instance
    }

    const unsigned int kart_amount = (unsigned int)m_karts.size();
    for (unsigned int i = 0; i < kart_amount; i++)
        initTeamArrows(m_karts[i].get());

}   // init

//-----------------------------------------------------------------------------
void World::initTeamArrows(AbstractKart* k)
{
    if (!hasTeam())
        return;
#ifndef SERVER_ONLY
    //Loading the indicator textures
    std::string red_path =
            file_manager->getAsset(FileManager::GUI_ICON, "red_arrow.png");
    std::string blue_path =
            file_manager->getAsset(FileManager::GUI_ICON, "blue_arrow.png");

    // Assigning indicators
    scene::ISceneNode *arrow_node = NULL;

    KartModel* km = k->getKartModel();
    // Color of karts can be changed using shaders if the model supports
    if (km->supportColorization() && CVS->isGLSL())
        return;

    float arrow_pos_height = km->getHeight() + 0.5f;
    KartTeam team = getKartTeam(k->getWorldKartId());

    arrow_node = irr_driver->addBillboard(
        core::dimension2d<irr::f32>(0.3f,0.3f),
        team == KART_TEAM_BLUE ? blue_path : red_path,
        k->getNode());

    arrow_node->setPosition(core::vector3df(0, arrow_pos_height, 0));
#endif
}   // initTeamArrows

//-----------------------------------------------------------------------------
/** This function is called before a race is started (i.e. either after
 *  calling init() when starting a race for the first time, or after
 *  restarting a race, in which case no init() is called.
 */
void World::reset(bool restart)
{
    WorldStatus::reset(restart);
    m_faster_music_active = false;
    m_eliminated_karts    = 0;
    m_eliminated_players  = 0;
    m_is_network_world = false;

    for ( KartList::iterator i = m_karts.begin(); i != m_karts.end() ; ++i )
    {
        (*i)->reset();
    }

    Camera::resetAllCameras();

    // Remove all (if any) previous game flyables before reset karts, so no
    // explosion animation will be created
    projectile_manager->cleanup();
    resetAllKarts();
    // Note: track reset must be called after all karts exist, since check
    // objects need to allocate data structures depending on the number
    // of karts.
    Track::getCurrentTrack()->reset();

    race_manager->reset();

    // Reset all data structures that depend on number of karts.
    irr_driver->reset();
    m_unfair_team = false;
}   // reset


//-----------------------------------------------------------------------------
/** Creates a kart, having a certain position, starting location, and local
 *  and global player id (if applicable).
 *  \param kart_ident Identifier of the kart to create.
 *  \param index Index of the kart.
 *  \param local_player_id If the kart is a player kart this is the index of
 *         this player on the local machine.
 *  \param global_player_id If the kart is a player kart this is the index of
 *         this player globally (i.e. including network players).
 */
std::shared_ptr<AbstractKart> World::createKart
    (const std::string &kart_ident, int index, int local_player_id,
    int global_player_id, RaceManager::KartType kart_type,
    PerPlayerDifficulty difficulty)
{
    std::shared_ptr<RenderInfo> ri = std::make_shared<RenderInfo>();
    core::stringw online_name;
    if (global_player_id > -1)
    {
        ri->setHue(race_manager->getKartInfo(global_player_id)
            .getDefaultKartColor());
        online_name = race_manager->getKartInfo(global_player_id)
            .getPlayerName();
    }

    int position           = index+1;
    btTransform init_pos   = getStartTransform(index);
    std::shared_ptr<AbstractKart> new_kart = std::make_shared<Kart>(kart_ident, index, position, init_pos, difficulty, ri);

    new_kart->init(race_manager->getKartType(index));
    Controller *controller = NULL;
    switch(kart_type)
    {
    case RaceManager::KT_PLAYER:
    {
        controller = new LocalPlayerController(new_kart.get(),
            local_player_id, difficulty);
        m_num_players ++;
        break;
    }
    case RaceManager::KT_AI:
    {
        controller = loadAIController(new_kart.get());
        break;
    }
    case RaceManager::KT_LEADER:
    case RaceManager::KT_SPARE_TIRE:
        break;
    }

    new_kart->setController(controller);
    race_manager->setKartColor(index, ri->getHue());
    return new_kart;
}   // createKart

//-----------------------------------------------------------------------------
/** Returns the start coordinates for a kart with a given index.
 *  \param index Index of kart ranging from 0 to kart_num-1. */
const btTransform &World::getStartTransform(int index)
{
    return Track::getCurrentTrack()->getStartTransform(index);
}   // getStartTransform

//-----------------------------------------------------------------------------
/** Creates an AI controller for the kart.
 *  \param kart The kart to be controlled by an AI.
 */
Controller* World::loadAIController(AbstractKart* kart)
{
    Controller *controller;
    int turn=0;

    if(race_manager->getMinorMode()==RaceManager::MINOR_MODE_3_STRIKES
        || race_manager->getMinorMode()==RaceManager::MINOR_MODE_FREE_FOR_ALL)
        turn=1;
    else if(race_manager->getMinorMode()==RaceManager::MINOR_MODE_SOCCER)
        turn=2;
    // If different AIs should be used, adjust turn (or switch randomly
    // or dependent on difficulty)
    switch(turn)
    {
        case 0:
            controller = new SkiddingAI(kart);
            break;
        case 1:
            controller = new BattleAI(kart);
            break;
        case 2:
            controller = new SoccerAI(kart);
            break;
        default:
            Log::warn("[World]", "Unknown AI, using default.");
            controller = new SkiddingAI(kart);
            break;
    }

    return controller;
}   // loadAIController

//-----------------------------------------------------------------------------
World::~World()
{
    material_manager->unloadAllTextures();

    irr_driver->onUnloadWorld();

    projectile_manager->cleanup();

    // In case that a race is aborted (e.g. track not found) track is 0.
    if(Track::getCurrentTrack())
        Track::getCurrentTrack()->cleanup();

    Weather::kill();

    m_karts.clear();
    race_manager->setTimeTarget(0.0f);
    race_manager->setSpareTireKartNum(0);

    Camera::removeAllCameras();

    // In case that the track is not found, Physics was not instantiated,
    // but kill handles this correctly.
    Physics::kill();

    Scripting::ScriptEngine::kill();

    m_world = NULL;

    irr_driver->getSceneManager()->clear();

#ifdef DEBUG
    m_magic_number = 0xDEADBEEF;
#endif

}   // ~World

//-----------------------------------------------------------------------------
/** Called when 'go' is being displayed for the first time. Here the brakes
 *  of the karts are released.
 */
void World::onGo()
{
    // Reset the brakes now that the prestart
    // phase is over (braking prevents the karts
    // from sliding downhill)
    for(unsigned int i=0; i<m_karts.size(); i++)
    {
        m_karts[i]->getVehicle()->setAllBrakes(0);
    }
}   // onGo

//-----------------------------------------------------------------------------
/** Called at the end of a race. Updates highscores, pauses the game, and
 *  informs the unlock manager about the finished race. This function must
 *  be called after all other stats were updated from the different game
 *  modes.
 */
void World::terminateRace()
{
    // Update the estimated finishing time for all karts that haven't
    // finished yet.
    const unsigned int kart_amount = getNumKarts();
    for(unsigned int i = 0; i < kart_amount ; i++)
    {
        if(!m_karts[i]->hasFinishedRace() && !m_karts[i]->isEliminated())
        {
            m_karts[i]->finishedRace(
                estimateFinishTimeForKart(m_karts[i].get()));

        }
    }   // i<kart_amount

    WorldStatus::terminateRace();
}   // terminateRace

//-----------------------------------------------------------------------------
/** Waits till each kart is resting on the ground
 *
 * Does simulation steps still all karts reach the ground, i.e. are not
 * moving anymore
 */
void World::resetAllKarts()
{
    // Reset the physics 'remaining' time to 0 so that the number
    // of timesteps is reproducible if doing a physics-based history run
    Physics::getInstance()->getPhysicsWorld()->resetLocalTime();

    //Project karts onto track from above. This will lower each kart so
    //that at least one of its wheel will be on the surface of the track
    for ( KartList::iterator i=m_karts.begin(); i!=m_karts.end(); i++)
    {
        Vec3 xyz = (*i)->getXYZ();
        //start projection from top of kart
        Vec3 up_offset = (*i)->getNormal() * (0.5f * ((*i)->getKartHeight()));
        (*i)->setXYZ(xyz+up_offset);

        bool kart_over_ground = Track::getCurrentTrack()->findGround(i->get());

        if (!kart_over_ground)
        {
            Log::error("World",
                       "No valid starting position for kart %d on track %s.",
                       (int)(i - m_karts.begin()),
                       Track::getCurrentTrack()->getIdent().c_str());
            {
                Log::warn("World", "Activating fly mode.");
                (*i)->flyUp();
                continue;
            }
        }
    }

    // Do a longer initial simulation, which should be long enough for all
    // karts to be firmly on ground.
    float g = Track::getCurrentTrack()->getGravity();
    for (KartList::iterator i = m_karts.begin(); i != m_karts.end(); i++)
    {
        (*i)->getBody()->setGravity(
            (*i)->getMaterial() && (*i)->getMaterial()->hasGravity() ?
            (*i)->getNormal() * -g : Vec3(0, -g, 0));
    }
    for(int i=0; i<stk_config->getPhysicsFPS(); i++) 
        Physics::getInstance()->update(1);

    for ( KartList::iterator i=m_karts.begin(); i!=m_karts.end(); i++)
    {
        (*i)->kartIsInRestNow();
    }

    // Initialise the cameras, now that the correct kart positions are set
    for(unsigned int i=0; i<Camera::getNumCameras(); i++)
    {
        Camera::getCamera(i)->setInitialTransform();
    }
}   // resetAllKarts

// ----------------------------------------------------------------------------
/** Places a kart that is rescued. It calls getRescuePositionIndex to find
 *  to which rescue position the kart should be moved, then getRescueTransform
 *  to get the position and rotation of this rescue position, and then moves
 *  the kart.
 *  \param kart The kart that is rescued.
 */
void World::moveKartAfterRescue(AbstractKart* kart)
{
    unsigned int index = getRescuePositionIndex(kart);
    btTransform t      = getRescueTransform(index);
    moveKartTo(kart, t);
}  // moveKartAfterRescue

// ----------------------------------------------------------------------------
/** Places the kart at a given position and rotation.
 *  \param kart The kart to be moved.
 *  \param transform
 */
void World::moveKartTo(AbstractKart* kart, const btTransform &transform)
{
    btTransform pos(transform);

    // Move the kart
    Vec3 xyz = pos.getOrigin() +
        pos.getBasis() * Vec3(0, 0.5f*kart->getKartHeight(), 0);
    pos.setOrigin(xyz);
    kart->setXYZ(xyz);
    kart->setRotation(pos.getRotation());

    kart->getBody()->setCenterOfMassTransform(pos);
    // The raycast to determine the terrain underneath the kart is done from
    // the centre point of the 4 wheel positions. After a rescue, the wheel
    // positions need to be updated (otherwise the raycast will be done from
    // the previous position, which might be the position that triggered
    // the rescue in the first place).
    kart->getVehicle()->updateAllWheelPositions();

    // Project kart to surface of track
    // This will set the physics transform
    Track::getCurrentTrack()->findGround(kart);
    CheckManager::get()->resetAfterKartMove(kart);

}   // moveKartTo

//-----------------------------------------------------------------------------
/** This is the main interface to update the world. This function calls
 *  update(), and checks then for the end of the race. Note that race over
 *  handling can not necessarily be done in update(), since not all
 *  data structures might have been updated (e.g.LinearWorld must
 *  call World::update() first, to get updated kart positions. If race
 *  over would be handled in World::update, LinearWorld had no opportunity
 *  to update its data structures before the race is finished).
 *  \param ticks Number of physics time steps - should be 1.
 */
void World::updateWorld(int ticks)
{
#ifdef DEBUG
    assert(m_magic_number == 0xB01D6543);
#endif
    // Don't update world if a menu is shown or the race is over.
    if (isFinishPhase())
        return;

    try
    {
        update(ticks);
    }
    catch (AbortWorldUpdateException& e)
    {
        (void)e;   // avoid compiler warning
        return;
    }

#ifdef DEBUG
    assert(m_magic_number == 0xB01D6543);
#endif

    if( (!isFinishPhase()) && isRaceOver())
    {
        enterRaceOverState();
    }
    else
    {
        if (m_schedule_exit_race)
        {
            m_schedule_exit_race = false;
            race_manager->exitRace(false);
            race_manager->setAIKartOverride("");
            delete this;
        }
    }
}   // updateWorld

#define MEASURE_FPS 0

//-----------------------------------------------------------------------------

void World::scheduleTutorial()
{
    m_schedule_exit_race = true;
    m_schedule_tutorial = true;
}   // scheduleTutorial

//-----------------------------------------------------------------------------
/** This updates all only graphical elements. It is only called once per
 *  rendered frame, not once per time step.
 *  float dt Time since last frame.
 */
void World::updateGraphics(float dt)
{
    PROFILER_PUSH_CPU_MARKER("World::update (weather)", 0x80, 0x7F, 0x00);
    if (UserConfigParams::m_particles_effects > 1 && Weather::getInstance())
    {
        Weather::getInstance()->update(dt);
    }
    PROFILER_POP_CPU_MARKER();

    // Update graphics of karts, e.g. visual suspension, skid marks
    const int kart_amount = (int)m_karts.size();
    for (int i = 0; i < kart_amount; ++i)
    {
        // Update all karts that are visible
        if (m_karts[i]->isVisible())
        {
            m_karts[i]->updateGraphics(dt);
        }
    }

    PROFILER_PUSH_CPU_MARKER("World::updateGraphics (camera)", 0x60, 0x7F, 0);
    for (unsigned int i = 0; i < Camera::getNumCameras(); i++)
        Camera::getCamera(i)->update(dt);
    PROFILER_POP_CPU_MARKER();

    Scripting::ScriptEngine *script_engine =
        Scripting::ScriptEngine::getInstance();
    if (script_engine)
        script_engine->update(dt);

    projectile_manager->updateGraphics(dt);
    Track::getCurrentTrack()->updateGraphics(dt);
}   // updateGraphics

void World::updateGraphicsMinimal(float dt)
{
    PROFILER_PUSH_CPU_MARKER("World::updateGraphics (camera)", 0x60, 0x7F, 0);
    for (unsigned int i = 0; i < Camera::getNumCameras(); i++)
        Camera::getCamera(i)->update(dt);
    PROFILER_POP_CPU_MARKER();

    Scripting::ScriptEngine *script_engine =
        Scripting::ScriptEngine::getInstance();
    if (script_engine)
        script_engine->update(dt);
}   // updateGraphicsMinimal

//-----------------------------------------------------------------------------
/** Updates the physics, all karts, the track, and projectile manager.
 *  \param ticks Number of physics time steps - should be 1.
 */
void World::update(int ticks)
{
#ifdef DEBUG
    assert(m_magic_number == 0xB01D6543);
#endif

    PROFILER_PUSH_CPU_MARKER("World::update()", 0x00, 0x7F, 0x00);

    PROFILER_PUSH_CPU_MARKER("World::update (sub-updates)", 0x20, 0x7F, 0x00);
    WorldStatus::update(ticks);
    PROFILER_POP_CPU_MARKER();

    PROFILER_PUSH_CPU_MARKER("World::update (Track object manager)", 0x20, 0x7F, 0x40);
    Track::getCurrentTrack()->getTrackObjectManager()->update(stk_config->ticks2Time(ticks));
    PROFILER_POP_CPU_MARKER();

    PROFILER_PUSH_CPU_MARKER("World::update (Kart::upate)", 0x40, 0x7F, 0x00);

    // Update all the karts. This in turn will also update the controller,
    // which causes all AI steering commands set. So in the following 
    // physics update the new steering is taken into account.
    const int kart_amount = (int)m_karts.size();
    for (int i = 0 ; i < kart_amount; ++i)
    {
        SpareTireAI* sta =
            dynamic_cast<SpareTireAI*>(m_karts[i]->getController());
        // Update all karts that are not eliminated
        if(!m_karts[i]->isEliminated() || (sta && sta->isMoving()))
            m_karts[i]->update(ticks);
        if (getPhase() == SETUP_PHASE)
            m_karts[i]->makeKartRest();
    }
    PROFILER_POP_CPU_MARKER();

    PROFILER_PUSH_CPU_MARKER("World::update (projectiles)", 0xa0, 0x7F, 0x00);
    projectile_manager->update(ticks);
    PROFILER_POP_CPU_MARKER();

    PROFILER_PUSH_CPU_MARKER("World::update (physics)", 0xa0, 0x7F, 0x00);
    Physics::getInstance()->update(ticks);
    PROFILER_POP_CPU_MARKER();

    PROFILER_POP_CPU_MARKER();

#ifdef DEBUG
    assert(m_magic_number == 0xB01D6543);
#endif
}   // update

// ----------------------------------------------------------------------------
/** Only updates the track. The order in which the various parts of STK are
 *  updated is quite important (i.e. the track can't be updated as part of
 *  the standard update call):
 *  the track must be updated after updating the karts (otherwise the
 *  checklines would be using the previous kart positions to determine
 *  new laps, but linear world which determines distance along track would
 *  be using the new kart positions --> the lap counting line will be
 *  triggered one frame too late, potentially causing strange behaviour of
 *  the icons.
 *  Similarly linear world must update the position of all karts after all
 *  karts have been updated (i.e. World::update() must be called before
 *  updating the position of the karts). The check manager (which is called
 *  from Track::update()) needs the updated distance along track, so track
 *  update has to be called after updating the race position in linear world.
 *  That's why there is a separate call for trackUpdate here.
 */
void World::updateTrack(int ticks)
{
    Track::getCurrentTrack()->update(ticks);
}   // update Track

//-----------------------------------------------------------------------------
/** Returns the n-th player kart. Note that this function is O(N), not O(1),
 *  so it shouldn't be called inside of loops.
 *  \param n Index of player kart to return.
 */
AbstractKart *World::getPlayerKart(unsigned int n) const
{
    unsigned int count = -1;

    for(unsigned int i = 0; i < m_karts.size(); i++)
    {
        if (m_karts[i]->getController()->isPlayerController())
        {
            count++;
            if (count == n)
                return m_karts[i].get();
        }
    }
    return NULL;
}   // getPlayerKart

//-----------------------------------------------------------------------------
/** Returns the nth local player kart, i.e. a kart that has a camera.
 *  Note that in profile mode this means a non player kart could be returned
 *  (since an AI kart will have the camera).
 *  \param n Index of player kart to return.
 */
AbstractKart *World::getLocalPlayerKart(unsigned int n) const
{
    if(n>=Camera::getNumCameras()) return NULL;
    return Camera::getCamera(n)->getKart();
}   // getLocalPlayerKart

//-----------------------------------------------------------------------------
/** Remove (eliminate) a kart from the race */
void World::eliminateKart(int kart_id, bool notify_of_elimination)
{
    assert(kart_id < (int)m_karts.size());
    AbstractKart *kart = m_karts[kart_id].get();

    if(kart->getController()->isLocalPlayerController())
    {
        for(unsigned int i=0; i<Camera::getNumCameras(); i++)
        {
            // Change the camera so that it will be attached to the leader
            // and facing backwards.
            Camera *camera = Camera::getCamera(i);
            if(camera->getKart()==kart)
                camera->setMode(Camera::CM_LEADER_MODE);
        }
        m_eliminated_players++;
    }

    // The kart can't be really removed from the m_kart array, since otherwise
    // a race can't be restarted. So it's only marked to be eliminated (and
    // ignored in all loops). Important:world->getCurrentNumKarts() returns
    // the number of karts still racing. This value can not be used for loops
    // over all karts, use race_manager->getNumKarts() instead!
    kart->eliminate();
    m_eliminated_karts++;

}   // eliminateKart

//-----------------------------------------------------------------------------
/** Called to determine the default collectibles to give each player at the
 *  start for this kind of race. Both parameters are of 'out' type.
 *  \param collectible_type The type of collectible each kart.
 *  \param amount The number of collectibles.
 */
void World::getDefaultCollectibles(int *collectible_type, int *amount )
{
    *collectible_type = PowerupManager::POWERUP_NOTHING;
    *amount = 0;
}   // getDefaultCollectibles

//-----------------------------------------------------------------------------
void World::escapePressed()
{
}   // escapePressed

// ----------------------------------------------------------------------------
/** Returns the start transform with the give index.
 *  \param rescue_pos Index of the start position to be returned.
 *  \returns The transform of the corresponding start position.
 */
btTransform World::getRescueTransform(unsigned int rescue_pos) const
{
    return Track::getCurrentTrack()->getStartTransform(rescue_pos);
}   // getRescueTransform

//-----------------------------------------------------------------------------
/** Uses the start position as rescue positions, override if necessary
 */
unsigned int World::getNumberOfRescuePositions() const
{
    return Track::getCurrentTrack()->getNumberOfStartPositions();
}   // getNumberOfRescuePositions

//-----------------------------------------------------------------------------
std::shared_ptr<AbstractKart> World::createKartWithTeam
    (const std::string &kart_ident, int index, int local_player_id,
    int global_player_id, RaceManager::KartType kart_type,
    PerPlayerDifficulty difficulty)
{
    int cur_red = getTeamNum(KART_TEAM_RED);
    int cur_blue = getTeamNum(KART_TEAM_BLUE);
    int pos_index = 0;
    int position  = index + 1;
    KartTeam team = KART_TEAM_BLUE;

    if (kart_type == RaceManager::KT_AI)
    {
        if (index < m_red_ai)
            team = KART_TEAM_RED;
        else
            team = KART_TEAM_BLUE;
        m_kart_team_map[index] = team;
    }
    else
    {
        int rm_id = index -
            (race_manager->getNumberOfKarts() - race_manager->getNumPlayers());

        assert(rm_id >= 0);
        team = race_manager->getKartInfo(rm_id).getKartTeam();
        m_kart_team_map[index] = team;
    }

    core::stringw online_name;
    if (global_player_id > -1)
    {
        online_name = race_manager->getKartInfo(global_player_id)
            .getPlayerName();
    }

    // Notice: In blender, please set 1,3,5,7... for blue starting position;
    // 2,4,6,8... for red.
    if (team == KART_TEAM_BLUE)
    {
        pos_index = 1 + 2 * cur_blue;
    }
    else
    {
        pos_index = 2 + 2 * cur_red;
    }

    btTransform init_pos = getStartTransform(pos_index - 1);
    m_kart_position_map[index] = (unsigned)(pos_index - 1);

    std::shared_ptr<RenderInfo> ri = std::make_shared<RenderInfo>();
    ri = (team == KART_TEAM_BLUE ? std::make_shared<RenderInfo>(0.66f) :
        std::make_shared<RenderInfo>(1.0f));

    std::shared_ptr<AbstractKart> new_kart = std::make_shared<Kart>(kart_ident, index, position, init_pos, difficulty, ri);

    new_kart->init(race_manager->getKartType(index));
    Controller *controller = NULL;

    switch(kart_type)
    {
    case RaceManager::KT_PLAYER:
        controller = new LocalPlayerController(new_kart.get(), local_player_id,
            difficulty);
        m_num_players ++;
        break;
    case RaceManager::KT_AI:
        controller = loadAIController(new_kart.get());
        break;
    case RaceManager::KT_LEADER:
    case RaceManager::KT_SPARE_TIRE:
        break;
    }

    new_kart->setController(controller);

    return new_kart;
}   // createKartWithTeam

//-----------------------------------------------------------------------------
int World::getTeamNum(KartTeam team) const
{
    int total = 0;
    if (m_kart_team_map.empty()) return total;

    for (unsigned int i = 0; i < (unsigned)m_karts.size(); ++i)
    {
        if (team == getKartTeam(m_karts[i]->getWorldKartId())) total++;
    }

    return total;
}   // getTeamNum

//-----------------------------------------------------------------------------
KartTeam World::getKartTeam(unsigned int kart_id) const
{
    std::map<int, KartTeam>::const_iterator n =
        m_kart_team_map.find(kart_id);

    assert(n != m_kart_team_map.end());
    return n->second;
}   // getKartTeam

//-----------------------------------------------------------------------------
void World::setAITeam()
{
    const int total_players = race_manager->getNumPlayers();
    const int total_karts = race_manager->getNumberOfKarts();

    // No AI
    if ((total_karts - total_players) == 0) return;

    int red_players = 0;
    int blue_players = 0;
    for (int i = 0; i < total_players; i++)
    {
        KartTeam team = race_manager->getKartInfo(i).getKartTeam();

        // Happen in profiling mode
        if (team == KART_TEAM_NONE)
        {
            race_manager->setKartTeam(i, KART_TEAM_BLUE);
            team = KART_TEAM_BLUE;
            continue; //FIXME, this is illogical
        }

        team == KART_TEAM_BLUE ? blue_players++ : red_players++;
    }

    int available_ai = total_karts - red_players - blue_players;
    int additional_blue = red_players - blue_players;

    m_blue_ai = (available_ai - additional_blue) / 2 + additional_blue;
    m_red_ai  = (available_ai - additional_blue) / 2;

    if ((available_ai + additional_blue)%2 == 1)
        (additional_blue < 0) ? m_red_ai++ : m_blue_ai++;

    Log::debug("World", "Blue AI: %d red AI: %d", m_blue_ai, m_red_ai);

}   // setAITeam
