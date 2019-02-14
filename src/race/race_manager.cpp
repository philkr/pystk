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

#include "race/race_manager.hpp"

#include <iostream>
#include <algorithm>

#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "graphics/irr_driver.hpp"
#include "input/input.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"
#include "karts/kart_properties_manager.hpp"
#include "modes/capture_the_flag.hpp"
#include "modes/easter_egg_hunt.hpp"
#include "modes/follow_the_leader.hpp"
#include "modes/free_for_all.hpp"
#include "modes/standard_race.hpp"
#include "modes/world.hpp"
#include "modes/three_strikes_battle.hpp"
#include "modes/soccer_world.hpp"
#include "network/network_string.hpp"
#include "replay/replay_play.hpp"
#include "scriptengine/property_animator.hpp"
#include "tracks/track_manager.hpp"
#include "utils/ptr_vector.hpp"
#include "utils/string_utils.hpp"
#include "utils/translation.hpp"

RaceManager* race_manager= NULL;

/** Constructs the race manager.
 */
RaceManager::RaceManager()
{
    // Several code depends on this, e.g. kart_properties
    assert(DIFFICULTY_FIRST == 0);
    m_num_karts          = UserConfigParams::m_default_num_karts;
    m_num_ghost_karts    = 0;
    m_difficulty         = DIFFICULTY_HARD;
    m_minor_mode         = MINOR_MODE_NORMAL_RACE;
    m_ai_superpower      = SUPERPOWER_NONE;
    m_coin_target        = 0;
    m_num_local_players = 0;
    m_hit_capture_limit = 0;
    m_flag_return_ticks = stk_config->time2Ticks(20.0f);
    m_flag_deactivated_ticks = stk_config->time2Ticks(3.0f);
    setMaxGoal(0);
    setTimeTarget(0.0f);
    setReverseTrack(false);
    setRecordRace(false);
    setRaceGhostKarts(false);
    setWatchingReplay(false);
    setTrack("jungle");
    m_default_ai_list.clear();
    setNumPlayers(0);
    setSpareTireKartNum(0);
}   // RaceManager

//-----------------------------------------------------------------------------
/** Destructor for the race manager.
 */
RaceManager::~RaceManager()
{
}   // ~RaceManager

//-----------------------------------------------------------------------------
/** Resets the race manager in preparation for a new race. It sets the
 *  counter of finished karts to zero. It is called by world when 
 *  restarting a race.
 */
void RaceManager::reset()
{
    m_num_finished_karts   = 0;
    m_num_finished_players = 0;
}  // reset

// ----------------------------------------------------------------------------
/** Sets the default list of AI karts to use.
 *  \param ai_kart_list List of the identifier of the karts to use.
 */
void RaceManager::setDefaultAIKartList(const std::vector<std::string>& ai_list)
{
    for(unsigned int i=0; i<ai_list.size(); i++)
    {
        const std::string &name=ai_list[i];
        const KartProperties *kp = kart_properties_manager->getKart(name);
        if(!kp)
        {
            Log::warn("RaceManager", "Kart '%s' is unknown and therefore ignored.",
                      name.c_str());
            continue;
        }
        // This doesn't work anymore, since this is called when
        // handling the command line options, at which time the
        // player (and therefore the current slot) is not defined yet.
        //if(unlock_manager->getCurrentSlot()->isLocked(name))
        //{
        //   Log::info("RaceManager", "Kart '%s' is locked and therefore ignored.",
        //           name.c_str());
        //    continue;
        //}
        m_default_ai_list.push_back(name);
    }
}   // setDefaultAIKartList

//-----------------------------------------------------------------------------
/** \brief Sets a player kart (local and non-local).
 *  \param player_id  Id of the player.
 *  \param ki         Kart info structure for this player.
 */
void RaceManager::setPlayerKart(unsigned int player_id, const RemoteKartInfo& ki)
{
    m_player_karts[player_id] = ki;
}   // setPlayerKart

// ----------------------------------------------------------------------------
void RaceManager::setPlayerKart(unsigned int player_id,
                                 const std::string &kart_name)
{
    RemoteKartInfo rki(player_id, kart_name, "", 0, false);
    m_player_karts[player_id] = rki;
}   // setPlayerKart

//-----------------------------------------------------------------------------
/** Sets additional information for a player to indicate which soccer team it
 *  belongs to.
*/
void RaceManager::setKartTeam(unsigned int player_id, KartTeam team)
{
    assert(player_id < m_player_karts.size());

    m_player_karts[player_id].setKartTeam(team);
}   // setKartTeam

//-----------------------------------------------------------------------------
/** Sets the per-player difficulty for a player.
 */
void RaceManager::setPlayerDifficulty(unsigned int player_id,
                                      PerPlayerDifficulty difficulty)
{
    assert(player_id < m_player_karts.size());

    m_player_karts[player_id].setPerPlayerDifficulty(difficulty);
}   // setPlayerDifficulty

//-----------------------------------------------------------------------------
/** Sets the number of players and optional the number of local players.
 *  \param num Number of players.
 *  \param local_players Number of local players, only used from networking.
 */
void RaceManager::setNumPlayers(int players, int local_players)
{
    // Clear all previous game info from network (like country code atm)
    // The rest info need to be store for overworld, see #3980
    m_player_karts.resize(players);
    if(local_players>-1)
        m_num_local_players = local_players;
    else
        m_num_local_players = players;
}   // setNumPlayers

// ----------------------------------------------------------------------------
/** Converst the difficulty given as a string into a Difficult enum. Defaults
 *  to HARD.
 *  \param difficulty The difficulty as string.
 */
RaceManager::Difficulty 
                  RaceManager::convertDifficulty(const std::string &difficulty)
{
    if (difficulty == "novice")
        return DIFFICULTY_EASY;
    else if (difficulty == "intermediate")
        return DIFFICULTY_MEDIUM;
    else if (difficulty == "expert")
        return DIFFICULTY_HARD;
    else if (difficulty == "best")
        return DIFFICULTY_BEST;
    else
        return DIFFICULTY_HARD;
}   // convertDifficulty

//-----------------------------------------------------------------------------
/** Sets the difficulty to use.
 *  \param diff The difficulty to use.
 */
void RaceManager::setDifficulty(Difficulty diff)
{
    m_difficulty = diff;
}   // setDifficulty

//-----------------------------------------------------------------------------
/** Sets a single track to be used in the next race.
 *  \param track The identifier of the track to use.
 */
void RaceManager::setTrack(const std::string& track)
{
    m_track = track;
    m_coin_target = 0;
}   // setTrack

//-----------------------------------------------------------------------------
/** \brief Computes the list of random karts to be used for the AI.
 *  If a command line option specifies karts, they will be used first
 */
void RaceManager::computeRandomKartList()
{
    int n = m_num_karts - (int)m_player_karts.size();
    if(UserConfigParams::logMisc())
        Log::info("RaceManager", "AI karts count = %d for m_num_karts = %d and "
            "m_player_karts.size() = %d", n, m_num_karts, m_player_karts.size());

    // If less kart selected than there are player karts, adjust the number of
    // karts to the minimum
    if(n<0)
    {
        m_num_karts -= n;
        n = 0;
    }

    m_ai_kart_list.clear();

    //Use the command line options AI list.
    unsigned int m = std::min( (unsigned) m_num_karts,  (unsigned)m_default_ai_list.size());

    for(unsigned int i=0; i<m; i++)
    {
        m_ai_kart_list.push_back(m_default_ai_list[i]);
        n--;
    }

    if(n>0)
        kart_properties_manager->getRandomKartList(n, &m_player_karts,
                                                   &m_ai_kart_list   );

    if (m_ai_kart_override != "")
    {
        for (unsigned int n = 0; n < m_ai_kart_list.size(); n++)
        {
            m_ai_kart_list[n] = m_ai_kart_override;
        }
    }

}   // computeRandomKartList

//-----------------------------------------------------------------------------
/** \brief Starts a new race or GP (or other mode).
 *  It sets up the list of player karts, AI karts, GP tracks if relevant
 *  etc.
 *  \pre The list of AI karts to use must be set up first. This is
 *       usually being done by a call to computeRandomKartList() from
 *       NetworkManager::setupPlayerKartInfo, but could be done differently
 *       (e.g. depending on user command line options to test certain AIs)
 *  \param from_overworld True if the race/GP is started from overworld
 *         (used to return to overworld at end of race/GP).
 */
void RaceManager::startNew()
{
    m_num_ghost_karts = 0;
    if (m_has_ghost_karts)
        m_num_ghost_karts = ReplayPlay::get()->getNumGhostKart();

    // command line parameters: negative numbers=all karts
    if(m_num_karts < 0 ) m_num_karts = stk_config->m_max_karts;
    if((size_t)m_num_karts < m_player_karts.size())
        m_num_karts = (int)m_player_karts.size();

    // Create the kart status data structure to keep track of scores, times, ...
    // ==========================================================================
    m_kart_status.clear();
    if (m_num_ghost_karts > 0)
        m_num_karts += m_num_ghost_karts;

    Log::verbose("RaceManager", "Nb of karts=%u, ghost karts:%u ai:%lu players:%lu\n",
        (unsigned int) m_num_karts, m_num_ghost_karts, m_ai_kart_list.size(), m_player_karts.size());

    assert((unsigned int)m_num_karts == m_num_ghost_karts+m_ai_kart_list.size()+m_player_karts.size());

    // First add the ghost karts (if any)
    // ----------------------------------------
    // GP ranks start with -1 for the leader.
    int init_gp_rank = getMinorMode()==MINOR_MODE_FOLLOW_LEADER ? -1 : 0;
    if (m_num_ghost_karts > 0)
    {
        for(unsigned int i = 0; i < m_num_ghost_karts; i++)
        {
            m_kart_status.push_back(KartStatus(ReplayPlay::get()->getGhostKartName(i),
                i, -1, -1, init_gp_rank, KT_GHOST, PLAYER_DIFFICULTY_NORMAL));
            init_gp_rank ++;
        }
    }

    // Then add the AI karts (randomly chosen)
    // ----------------------------------------
    const unsigned int ai_kart_count = (unsigned int)m_ai_kart_list.size();
    for(unsigned int i = 0; i < ai_kart_count; i++)
    {
        m_kart_status.push_back(KartStatus(m_ai_kart_list[i], i, -1, -1,
            init_gp_rank, KT_AI, PLAYER_DIFFICULTY_NORMAL));
        init_gp_rank ++;
    }

    // Finally add the players, which start behind the AI karts
    // -----------------------------------------------------
    for(unsigned int i = 0; i < m_player_karts.size(); i++)
    {
        m_kart_status.push_back(KartStatus(m_player_karts[i].getKartName(), i,
                                           m_player_karts[i].getLocalPlayerId(),
                                           m_player_karts[i].getGlobalPlayerId(),
                                           init_gp_rank, KT_PLAYER,
                                           m_player_karts[i].getDifficulty()));
        init_gp_rank ++;
    }

    startNextRace();
}   // startNew

//-----------------------------------------------------------------------------
/** \brief Starts the next (or first) race.
 *  It sorts the kart status data structure
 *  according to the number of points, and then creates the world().
 */
void RaceManager::startNextRace()
{
    // Uncomment to debug audio leaks

    IrrlichtDevice* device = irr_driver->getDevice();
    device->getVideoDriver()->endScene();
    device->getVideoDriver()->beginScene(true, true,
                                         video::SColor(255,100,101,140));

    m_num_finished_karts   = 0;
    m_num_finished_players = 0;

    // set boosted AI status for AI karts
    int boosted_ai_count = std::min<int>((int)m_ai_kart_list.size(),
                                         ((int)(m_kart_status.size())-2)/4 + 1);
    if (boosted_ai_count > 4) boosted_ai_count = 4;
    int ai_count = (int)m_ai_kart_list.size();

    for (unsigned int i=0;i<m_kart_status.size();i++)
    {
        if (m_kart_status[i].m_kart_type == KT_AI)
        {
            if (boosted_ai_count > 0)
            {
                m_kart_status[i].m_boosted_ai = true;
                boosted_ai_count--;
            }
            else
            {
                m_kart_status[i].m_boosted_ai = false;
            }
            ai_count--;
        }
    }

    // the constructor assigns this object to the global
    // variable world. Admittedly a bit ugly, but simplifies
    // handling of objects which get created in the constructor
    // and need world to be defined.
    if(m_minor_mode==MINOR_MODE_FOLLOW_LEADER)
        World::setWorld(new FollowTheLeaderRace());
    else if(m_minor_mode==MINOR_MODE_NORMAL_RACE ||
            m_minor_mode==MINOR_MODE_TIME_TRIAL)
        World::setWorld(new StandardRace());
    else if (isBattleMode())
    {
        if (m_minor_mode == MINOR_MODE_3_STRIKES)
            World::setWorld(new ThreeStrikesBattle());
        else if (m_minor_mode == MINOR_MODE_FREE_FOR_ALL)
            World::setWorld(new FreeForAll());
        else if (m_minor_mode == MINOR_MODE_CAPTURE_THE_FLAG)
            World::setWorld(new CaptureTheFlag());
    }
    else if(m_minor_mode==MINOR_MODE_SOCCER)
        World::setWorld(new SoccerWorld());
    else if(m_minor_mode==MINOR_MODE_EASTER_EGG)
        World::setWorld(new EasterEggHunt());
    else
    {
        Log::error("RaceManager", "Could not create given race mode.");
        assert(0);
    }
    
    // A second constructor phase is necessary in order to be able to
    // call functions which are overwritten (otherwise polymorphism
    // will fail and the results will be incorrect). Also in init() functions
    // can be called that use World::getWorld().
    World::getWorld()->init();
    // Now initialise all values that need to be reset from race to race
    // Calling this here reduces code duplication in init and restartRace()
    // functions.
    World::getWorld()->reset();

    irr_driver->onLoadWorld();
    
    // Save the current score and set last time to zero. This is necessary
    // if someone presses esc after finishing a gp, and selects restart:
    // The race is rerun, and the points and scores get reset ... but if
    // a kart hasn't finished the race at this stage, last_score and time
    // would be undefined.
    for(int i=0; i<m_num_karts; i++)
    {
        m_kart_status[i].m_last_score = m_kart_status[i].m_score;
        m_kart_status[i].m_last_time  = 0;
    }
}   // startNextRace

//-----------------------------------------------------------------------------
/** \brief Start the next race or go back to the start screen
 * If there are more races to do, starts the next race, otherwise
 * calls exitRace to finish the race.
 */
void RaceManager::next()
{
    PropertyAnimator::get()->clear();
    World::deleteWorld();
    m_num_finished_karts   = 0;
    m_num_finished_players = 0;
    exitRace();
}   // next

//-----------------------------------------------------------------------------

/** This class is only used in computeGPRanks, but the C++ standard
 *  forbids the usage of local data type in templates, so we have to
 *  declare it outside of the function. This class is used to store
 *  and compare data for determining the GP rank.
 */
namespace computeGPRanksData
{
    class SortData
    {
    public:
        int m_score;
        int m_position;
        float m_race_time;
        bool operator<(const SortData &a)
        {
            return ( (m_score > a.m_score) ||
                (m_score == a.m_score && m_race_time < a.m_race_time) );
        }

    };   // SortData
}   // namespace

//-----------------------------------------------------------------------------
/** \brief Exit a race (and don't start the next one)
 * \note In GP, displays the GP result screen first
 * \param delete_world If set deletes the world.
 */
void RaceManager::exitRace(bool delete_world)
{
    if (delete_world)
    {
        PropertyAnimator::get()->clear();
        World::deleteWorld();
    }
}   // exitRace

//-----------------------------------------------------------------------------
/** A kart has finished the race at the specified time (which can be
 *  different from World::getWorld()->getClock() in case of setting
 *  extrapolated arrival times). This function is only called from
 *  kart::finishedRace()
 *  \param kart The kart that finished the race.
 *  \param time Time at which the kart finished the race.
 */
void RaceManager::kartFinishedRace(const AbstractKart *kart, float time)
{
    unsigned int id = kart->getWorldKartId();
    int pos = kart->getPosition();

    assert(pos-1 >= 0);
    assert(pos-1 < (int)m_kart_status.size());

    m_kart_status[id].m_last_score    = m_kart_status[id].m_score;

    // In follow the leader mode, the winner is actually the kart with
    // position 2, so adjust the points (#points for leader do not matter)
    WorldWithRank *wwr = dynamic_cast<WorldWithRank*>(World::getWorld());
    if (wwr)
        m_kart_status[id].m_score += wwr->getScoreForPosition(pos);
    else
    {
        Log::error("RaceManager",
                   "World with scores that is not a WorldWithRank??");
    }

    m_kart_status[id].m_overall_time += time;
    m_kart_status[id].m_last_time     = time;
    m_num_finished_karts ++;
    if(kart->getController()->isPlayerController())
        m_num_finished_players++;
}   // kartFinishedRace

//-----------------------------------------------------------------------------
/** \brief Rerun the same race again
 * This is called after a race is finished, and it will adjust
 * the number of points and the overall time before restarting the race.
 */
void RaceManager::rerunRace()
{
    // Subtract last score from all karts:
    for(int i=0; i<m_num_karts; i++)
    {
        m_kart_status[i].m_score         = m_kart_status[i].m_last_score;
        m_kart_status[i].m_overall_time -= m_kart_status[i].m_last_time;
    }
    World::getWorld()->reset(true /* restart */);
}   // rerunRace

//-----------------------------------------------------------------------------
/** \brief Higher-level method to start a GP without having to care about
 *  the exact startup sequence.
 * \param trackIdent Internal name of the track to race on
 * \param num_laps   Number of laps to race, or -1 if number of laps is
 *        not relevant in current mode
 */
void RaceManager::startSingleRace(const std::string &track_ident,
                                  const int num_laps)
{
    assert(!m_watching_replay);

    // In networking, make sure that the tracks screen is shown. This will
    // allow for a 'randomly pick track' animation to be shown while
    // world is loaded.
    // Disable until render gui during loading is bug free
    /*if (NetworkConfig::get()->isNetworking() &&
        NetworkConfig::get()->isClient()        )
    {
        // TODO: The enterGameState() call above deleted all GUIs, which
        // means even if the tracks screen is shown, it need to be recreated.
        // And we have to make sure that it is recreated as network version.
        TracksScreen *ts = TracksScreen::getInstance();
        if (GUIEngine::getCurrentScreen() != ts)
        {
            ts->setNetworkTracks();
            ts->push();
        }
    }*/


    setTrack(track_ident);

    if (num_laps != -1) setNumLaps( num_laps );

    setCoinTarget( 0 ); // Might still be set from a previous challenge

    // if not in a network world, setup player karts
    race_manager->setupPlayerKartInfo(); // do this setup player kart

    startNew();
}   // startSingleRace

//-----------------------------------------------------------------------------
/** Fills up the remaining kart slots with AI karts.
 */
void RaceManager::setupPlayerKartInfo()
{
    computeRandomKartList();
}   // setupPlayerKartInfo

//-----------------------------------------------------------------------------
/** \brief Function to start the race with only ghost kart(s) and watch.
 * \param trackIdent Internal name of the track to race on
 * \param num_laps   Number of laps to race, or -1 if number of laps is
 *        not relevant in current mode
 */
void RaceManager::startWatchingReplay(const std::string &track_ident,
                                      const int num_laps)
{
    assert(m_watching_replay && m_has_ghost_karts && !m_is_recording_race);
    setTrack(track_ident);
    setNumLaps(num_laps);
    setCoinTarget(0);
    m_num_karts = ReplayPlay::get()->getNumGhostKart();
    m_kart_status.clear();

    Log::verbose("RaceManager", "%u ghost kart(s) for watching replay only\n",
        (unsigned int)m_num_karts);

    int init_gp_rank = 0;

    for(int i = 0; i < m_num_karts; i++)
    {
        m_kart_status.push_back(KartStatus(ReplayPlay::get()->getGhostKartName(i),
            i, -1, -1, init_gp_rank, KT_GHOST, PLAYER_DIFFICULTY_NORMAL));
        init_gp_rank ++;
    }

    startNextRace();
}   // startWatchingReplay
