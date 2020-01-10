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

#ifndef HEADER_RACEMANAGER_HPP
#define HEADER_RACEMANAGER_HPP

/**
  * \defgroup race
  * Contains the race information that is conceptually above what you can find
  * in group Modes. Handles highscores, grands prix, number of karts, which
  * track was selected, etc.
  */

#include <vector>
#include <algorithm>
#include <string>

#include "network/remote_kart_info.hpp"
#include "utils/vec3.hpp"

class AbstractKart;
class SavedGrandPrix;
class Track;

static const std::string IDENT_STD      ("STANDARD"        );
static const std::string IDENT_TTRIAL   ("STD_TIMETRIAL"   );
static const std::string IDENT_FTL      ("FOLLOW_LEADER"   );
static const std::string IDENT_STRIKES  ("BATTLE_3_STRIKES");
static const std::string IDENT_FFA      ("BATTLE_FFA"      );
static const std::string IDENT_CTF      ("BATTLE_CTF"      );
static const std::string IDENT_EASTER   ("EASTER_EGG_HUNT" );
static const std::string IDENT_SOCCER   ("SOCCER"          );

/**
 * The race manager has two functions:
 *  1) it stores information about the race the user selected (e.g. number
 *     of karts, track, race mode etc.). Most of the values are just stored
 *     from the menus, and just read back, except for GP mode (the race
 *     manager stores the GP information, but World queries only track
 *     and number of laps, so in case of GP this information is taken from
 *     the GrandPrix object), and local player information (number of local
 *     players, and selected karts). 
 *     Information about player karts (which player selected which kart,
 *     player ids) is stored in a RemoteKartInfo structure and used later
 *     to initialise the KartStatus array (startNew()). The KartStatus array
 *     stores information about all karts (player and AI), and is used to
 *     determine the order in which karts are started (see startNextRace()).
 *  2) when a race is started, it creates the world, and keeps track of
 *     score during the race. When a race is finished, it deletes the world,
 *     and (depending on race mode) starts the next race by creating a new
 *     world.
 *  Information in the RaceManager is considered to be 'more static', sometimes
 *  the world has similar functions showing the current state. E.g.: the
 *  race manager keeps track of the number of karts with which the race was
 *  started, while world keeps track of the number of karts currently in the
 *  race (consider a race mode like follow the leader where karts can get
 *  eliminated, but still the RaceManager has to accumulate points for those
 *  karts).
 *  The race manager handles all race types as a kind of grand prix. E.g.:
 *  a quick race is basically a GP with only one track (so the race manager
 *  keeps track of scores even though no scores are used in a quick race).
 *
 * \ingroup race
 */
class RaceManager
{
public:
    // quick method to tell the difference between battle modes and race modes
    // think of it like a bitmask, but done in decimal to avoid endianness
    // issues
#define LINEAR_RACE(ID, COUNT_LAPSES) (1000+ID+100*COUNT_LAPSES)
#define BATTLE_ARENA(ID) (2000+ID)
#define EASTER_EGG(ID)   (3000+ID)
#define MISC(ID)         (4000+ID)

    // ------------------------------------------------------------------------
    /** Minor variants to the major types of race.
     *  Make sure to use the 'LINEAR_RACE/BATTLE_ARENA' macros. */
    enum MinorRaceModeType
    {
        MINOR_MODE_NONE             = -1,

        MINOR_MODE_NORMAL_RACE      = LINEAR_RACE(0, true),
        MINOR_MODE_TIME_TRIAL       = LINEAR_RACE(1, true),
        MINOR_MODE_FOLLOW_LEADER    = LINEAR_RACE(2, false),

        MINOR_MODE_3_STRIKES        = BATTLE_ARENA(0),
        MINOR_MODE_FREE_FOR_ALL     = BATTLE_ARENA(1),
        MINOR_MODE_CAPTURE_THE_FLAG = BATTLE_ARENA(2),
        MINOR_MODE_SOCCER           = BATTLE_ARENA(3),

        MINOR_MODE_EASTER_EGG       = EASTER_EGG(0),
    };

    // ------------------------------------------------------------------------
    /** Returns a string identifier for each minor race mode.
     *  \param mode Minor race mode.
     */
    static const std::string& getIdentOf(const MinorRaceModeType mode)
    {
        switch (mode)
        {
            case MINOR_MODE_NORMAL_RACE:      return IDENT_STD;
            case MINOR_MODE_TIME_TRIAL:       return IDENT_TTRIAL;
            case MINOR_MODE_FOLLOW_LEADER:    return IDENT_FTL;
            case MINOR_MODE_3_STRIKES:        return IDENT_STRIKES;
            case MINOR_MODE_FREE_FOR_ALL:     return IDENT_FFA;
            case MINOR_MODE_CAPTURE_THE_FLAG: return IDENT_CTF;
            case MINOR_MODE_EASTER_EGG:       return IDENT_EASTER;
            case MINOR_MODE_SOCCER:           return IDENT_SOCCER;
            default: assert(false);
                     return IDENT_STD;  // stop compiler warning
        }
    }   // getIdentOf

    // ------------------------------------------------------------------------
    /** Returns the icon for a minor race mode.
     *  \param mode Minor race mode.
     */
    static const char* getIconOf(const MinorRaceModeType mode)
    {
        switch (mode)
        {
            case MINOR_MODE_NORMAL_RACE:    return "/gui/icons/mode_normal.png";
            case MINOR_MODE_TIME_TRIAL:     return "/gui/icons/mode_tt.png";
            case MINOR_MODE_FOLLOW_LEADER:  return "/gui/icons/mode_ftl.png";
            case MINOR_MODE_3_STRIKES:      return "/gui/icons/mode_3strikes.png";
            case MINOR_MODE_FREE_FOR_ALL:   return "/gui/icons/weapons.png";
            case MINOR_MODE_CAPTURE_THE_FLAG: return "/gui/icons/weapons.png";
            case MINOR_MODE_EASTER_EGG:     return "/gui/icons/mode_easter.png";
            case MINOR_MODE_SOCCER:         return "/gui/icons/mode_soccer.png";
            default: assert(false); return NULL;
        }
    }   // getIconOf

    // ------------------------------------------------------------------------
    static const core::stringw getNameOf(const MinorRaceModeType mode);
    // ------------------------------------------------------------------------
    /** Returns if the currently set minor game mode can be used by the AI. */
    bool hasAI()
    {
        switch (m_minor_mode)
        {
            case MINOR_MODE_NORMAL_RACE:    return true;
            case MINOR_MODE_TIME_TRIAL:     return true;
            case MINOR_MODE_FOLLOW_LEADER:  return true;
            case MINOR_MODE_3_STRIKES:      return true;
            case MINOR_MODE_FREE_FOR_ALL:   return false;
            case MINOR_MODE_CAPTURE_THE_FLAG: return false;
            case MINOR_MODE_EASTER_EGG:     return false;
            case MINOR_MODE_SOCCER:         return true;
            default: assert(false);         return false;
        }
    }   // hasAI


    // ------------------------------------------------------------------------
    /** Returns the minor mode id from a string identifier. This function is
     *  used from challenge_data, which reads the mode from a challenge file.
     *  \param name The name of the minor mode.
     */
    static const MinorRaceModeType getModeIDFromInternalName(
                                                       const std::string &name)
    {
        if      (name==IDENT_STD    ) return MINOR_MODE_NORMAL_RACE;
        else if (name==IDENT_TTRIAL ) return MINOR_MODE_TIME_TRIAL;
        else if (name==IDENT_FTL    ) return MINOR_MODE_FOLLOW_LEADER;
        else if (name==IDENT_STRIKES) return MINOR_MODE_3_STRIKES;
        else if (name==IDENT_FFA)     return MINOR_MODE_FREE_FOR_ALL;
        else if (name==IDENT_CTF)     return MINOR_MODE_CAPTURE_THE_FLAG;
        else if (name==IDENT_EASTER ) return MINOR_MODE_EASTER_EGG;
        else if (name==IDENT_SOCCER)  return MINOR_MODE_SOCCER;

        assert(0);
        return MINOR_MODE_NONE;
    }

#undef LINEAR_RACE
#undef BATTLE_ARENA
#undef MISC

    /** Game difficulty. */
    enum Difficulty     { DIFFICULTY_EASY = 0,
                          DIFFICULTY_FIRST = DIFFICULTY_EASY,
                          DIFFICULTY_MEDIUM,
                          DIFFICULTY_HARD,
                          DIFFICULTY_BEST,
                          DIFFICULTY_LAST = DIFFICULTY_BEST,
                          DIFFICULTY_COUNT,
                          DIFFICULTY_NONE};

    /** Different kart types: A local player, a player connected via network,
     *  an AI kart, the leader kart (currently not used), a ghost kart and
     *  spare tire karts which allow gain life in battle mode */
    enum KartType       { KT_PLAYER, KT_AI, KT_LEADER,
                          KT_SPARE_TIRE };
public:

    /** This data structure accumulates kart data and race result data from
     *  each race. */
    struct KartStatus
    {
        /** The kart identifier. */
        std::string m_ident;
        /** For networked karts. */
        std::string m_player_name;
        // Score for this kart. */
        int         m_score;
        /** Needed for restart race, and for race results GUI. */
        int         m_last_score;
        /** Sum of times of all races. */
        float       m_overall_time;
        /** Needed for restart. */
        float       m_last_time;
        /** Kart type: AI, player, network player etc. */
        KartType    m_kart_type;
        /** Player controling the kart, for AI: -1 */
        int         m_local_player_id;
        /** Global ID of player. */
        int         m_global_player_id;
        /** In GPs, at the end, will hold the overall rank of this kart
         *  (0<=m_gp_rank < num_karts-1). */
        int         m_gp_rank;
        /** Boosted status (AI only). */
        bool        m_boosted_ai;
        /** The difficulty for this player. */
        PerPlayerDifficulty m_difficulty;
        /** Kart color of player (used in gp win / lose screen). */
        float       m_color;
        KartStatus(const std::string& ident, const int& prev_finish_pos,
                   int local_player_id, int global_player_id,
                   int init_gp_rank, KartType kt,
                   PerPlayerDifficulty difficulty) :
                   m_ident(ident), m_score(0), m_last_score(0),
                   m_overall_time(0.0f), m_last_time(0.0f),
                   m_kart_type(kt),
                   m_local_player_id(local_player_id),
                   m_global_player_id(global_player_id),
                   m_gp_rank(init_gp_rank), m_difficulty(difficulty)
                { m_boosted_ai = false; m_color = 0.0f; }

    };   // KartStatus
private:

    /** The kart status data for each kart. */
    std::vector<KartStatus>          m_kart_status;

    /** The selected difficulty. */
    Difficulty                       m_difficulty;

    /** The minor mode (race, time trial, ftl, battle mode). */
    MinorRaceModeType                m_minor_mode;
    /** Stores remote kart information about all player karts. */
    std::vector<RemoteKartInfo>      m_player_karts;
    std::string                      m_track;

    /** Number of local players. */
    unsigned int m_num_local_players;

    /** The number of laps for each track of a GP (only one element
     *  is used if only a single track is used. */
   int                               m_num_laps;

    /** Whether a track should be reversed */
    bool                             m_reverse_track;

    /** The list of default AI karts to use. This is from the command line. */
    std::vector<std::string>         m_default_ai_list;

    /** If set, specifies which kart to use for AI(s) */
    std::string                      m_ai_kart_override;

    /** The list of AI karts to use. This is stored here so that the
     *  same list of AIs is used for all tracks of a GP. */
    std::vector<std::string>         m_ai_kart_list;
    int                              m_num_karts;
    unsigned int                     m_num_spare_tire_karts;
    unsigned int                     m_num_finished_karts;
    unsigned int                     m_num_finished_players;
    unsigned                         m_flag_return_ticks;
    unsigned                         m_flag_deactivated_ticks;
    int                              m_coin_target;
    float                            m_time_target;
    int                              m_goal_target;
    int                              m_hit_capture_limit;
    void startNextRace();    // start a next race

    friend bool operator< (const KartStatus& left, const KartStatus& right)
    {
        return (left.m_score < right.m_score) ||
            (left.m_score == right.m_score &&
             left.m_overall_time > right.m_overall_time);
    }

    bool m_is_recording_race;
public:
         RaceManager();
        ~RaceManager();

    void reset();
    void setPlayerKart(unsigned int player_id, const std::string &kart_name);
    void setPlayerKart(unsigned int player_id,
                       const RemoteKartInfo& ki);

    /** Sets additional information for a player to indicate which team it belong to
    */
    void setKartTeam(unsigned int player_id, KartTeam team);

    /** Sets the per-player difficulty for a player.
     */
    void setPlayerDifficulty(unsigned int player_id, PerPlayerDifficulty difficulty);

    /** In case of non GP mode set the track to use.
     *  \param track Pointer to the track to use.
     */
    void setTrack(const std::string& track);

    /** \brief Sets the difficulty.
      * \param diff Difficulty.
      */
    void setDifficulty(Difficulty diff);
    static Difficulty convertDifficulty(const std::string &difficulty);
    void startNew();
    void next();
    void rerunRace();
    void exitRace(bool delete_world=true);
    void startSingleRace(const std::string &track_ident, const int num_laps);
    void setupPlayerKartInfo();
    void kartFinishedRace(const AbstractKart* kart, float time);
    void setNumPlayers(int players, int local_players=-1);
    void setDefaultAIKartList(const std::vector<std::string> &ai_list);
    void computeRandomKartList();

    // ------------------------------------------------------------------------
    bool hasTimeTarget() const { return m_time_target > 0.0f; }
    // ------------------------------------------------------------------------
    void setMaxGoal(int max_goal)
    {
        m_time_target = 0.0f;
        m_goal_target = max_goal;
    }   // setMaxGoal
    // ------------------------------------------------------------------------
    int getMaxGoal(){ return m_goal_target; }
    // ------------------------------------------------------------------------
    void setCoinTarget(int num)   { m_coin_target = num; }
    // ------------------------------------------------------------------------
    void setAIKartOverride(const std::string& kart)
    {
        m_ai_kart_override = kart;
    }   // setAIKartOverride
    // ------------------------------------------------------------------------
    void setNumLaps(int num)
    {
        m_num_laps = num;
    }   // setNumLaps
    // ------------------------------------------------------------------------
    void setReverseTrack(bool r_t)
    {
        m_reverse_track = r_t;
    }   // setReverseTrack
    // ------------------------------------------------------------------------
    void setMinorMode(MinorRaceModeType mode)
    {
        m_minor_mode = mode;
    }   // setMinorMode
    // ------------------------------------------------------------------------
    void setNumKarts(int num)
    {
        m_num_karts = num;
        m_ai_kart_override = "";
    }   // setNumKarts
    // ------------------------------------------------------------------------
    void setTimeTarget(float time)
    {
        m_goal_target = 0;
        m_time_target = time;
    }   // setTimeTarget
    // ------------------------------------------------------------------------
    RemoteKartInfo& getKartInfo(unsigned int n)
    {
        return m_player_karts[n];
    }   // getKartInfo
    // ------------------------------------------------------------------------
    unsigned int getNumLocalPlayers() const
    {
        return m_num_local_players;
    }   // getNumLocalPlayers
    
    // ------------------------------------------------------------------------
    /** Returns true if the split screen display leaves an empty space that
     *  can be used to display the minimap.
     */
    bool getIfEmptyScreenSpaceExists() const
    {
        const float sqrt_num_players = sqrtf((float)getNumLocalPlayers());
        const int rows = (int)ceil(sqrt_num_players);
        const int cols = (int)round(sqrt_num_players);
        const int total_spaces = rows * cols;
        return (total_spaces - getNumLocalPlayers() > 0);
    }   // getIfEmptyScreenSpaceExists
    // ------------------------------------------------------------------------
    /** Returns the selected number of karts (selected number of players and
     *  AI karts. */
    unsigned int getNumberOfKarts() const {return m_num_karts; }
    // ------------------------------------------------------------------------
    unsigned int getNumberOfAIKarts() const
    {
        return (unsigned int)m_ai_kart_list.size(); 
    }   // getNumberOfAIKarts
    // ------------------------------------------------------------------------
    MinorRaceModeType getMinorMode() const { return m_minor_mode; }
    // ------------------------------------------------------------------------
    std::string getMinorModeName() const
    {
        switch (m_minor_mode)
        {
            case MINOR_MODE_NORMAL_RACE:    return "normal";
            case MINOR_MODE_TIME_TRIAL:     return "time-trial";
            case MINOR_MODE_FOLLOW_LEADER:  return "follow-the-leader";
            case MINOR_MODE_3_STRIKES:      return "battle";
            case MINOR_MODE_FREE_FOR_ALL:   return "ffa";
            case MINOR_MODE_CAPTURE_THE_FLAG: return "ctf";
            case MINOR_MODE_EASTER_EGG:     return "egg-hunt";
            case MINOR_MODE_SOCCER:         return "soccer";
            default: assert(false);         return "";
        }
    }
    // ------------------------------------------------------------------------
    unsigned int getNumPlayers() const 
    {
        return (unsigned int) m_player_karts.size(); 
    }   // getNumPlayers
    // ------------------------------------------------------------------------
    /** \brief Returns the number lf laps.
     *  In case of FTL or battle mode always return 9999, since they don't
     *  have laps. This avoids problems in FTL GP, since in this case no laps
     *  would be set (otherwise we would need many more tests in calls to
     *  getNumLaps).
     */
    int getNumLaps() const
    {
        if(modeHasLaps())
            return m_num_laps;
        // else
        return 9999;
    }   // getNumLaps
    // ------------------------------------------------------------------------
    /** \return whether the track should be reversed */
    bool getReverseTrack() const { return m_reverse_track; }
    // ------------------------------------------------------------------------
    /** Returns the difficulty. */
    Difficulty getDifficulty() const { return m_difficulty; }
    // ------------------------------------------------------------------------
    /** Returns the specified difficulty as a string. */
    std::string getDifficultyAsString(Difficulty diff) const
    {
        switch(diff)
        {
        case RaceManager::DIFFICULTY_EASY:   return "easy";   break;
        case RaceManager::DIFFICULTY_MEDIUM: return "medium"; break;
        case RaceManager::DIFFICULTY_HARD:   return "hard";   break;
        case RaceManager::DIFFICULTY_BEST:   return "best";   break;
        default:  assert(false);
        }
        return "";
    }   // getDifficultyAsString

    // ------------------------------------------------------------------------
    core::stringw getDifficultyName(Difficulty diff) const;
    // ------------------------------------------------------------------------
    unsigned int getFinishedKarts() const { return m_num_finished_karts; }
    // ------------------------------------------------------------------------
    unsigned int getFinishedPlayers() const { return m_num_finished_players; }
    // ------------------------------------------------------------------------
    const std::string& getKartIdent(int kart) const
    {
        return m_kart_status[kart].m_ident;
    }   // getKartIdent
    // ------------------------------------------------------------------------
    int getKartScore(int krt) const { return m_kart_status[krt].m_score; }
    // ------------------------------------------------------------------------
    int getKartPrevScore(int krt) const
    {
        return m_kart_status[krt].m_last_score;
    }   // getKartPrevScore
    // ------------------------------------------------------------------------
    int getKartLocalPlayerId(int k) const
    {
        return m_kart_status[k].m_local_player_id;
    }   // getKartLocalPlayerId
    // ------------------------------------------------------------------------
    int getKartGlobalPlayerId(int k) const
    {
        return m_kart_status[k].m_global_player_id;
    }   // getKartGlobalPlayerId
    // ------------------------------------------------------------------------
    float getOverallTime(int kart) const
    {
        return m_kart_status[kart].m_overall_time;
    }   // getOverallTime
    // ------------------------------------------------------------------------
    float getKartRaceTime(int kart) const
    {
        return m_kart_status[kart].m_last_time;
    }   // getKartRaceTime
    // ------------------------------------------------------------------------
    KartType getKartType(int kart) const
    {
        return m_kart_status[kart].m_kart_type;
    }   // getKartType
    // ------------------------------------------------------------------------
    PerPlayerDifficulty getPlayerDifficulty(int kart) const
    {
        return m_kart_status[kart].m_difficulty;
    }   // getPlayerDifficulty
    // ------------------------------------------------------------------------
    bool hasBoostedAI(int kart) const
    {
        return m_kart_status[kart].m_boosted_ai;
    }   // getKartRaceTime
    // ------------------------------------------------------------------------
    void setKartColor(int kart, float color)
    {
        m_kart_status[kart].m_color = color;
    }   // setKartColor
    // ------------------------------------------------------------------------
    float getKartColor(int kart) const
    {
        return m_kart_status[kart].m_color;
    }   // getKartColor
    // ------------------------------------------------------------------------
    int getCoinTarget() const { return m_coin_target; }
    // ------------------------------------------------------------------------
    float getTimeTarget() const { return m_time_target; }
    // ------------------------------------------------------------------------
    int getNumOfTracks() const { return 1; }
    const std::string & getTrackName() const { return m_track; }
    // ------------------------------------------------------------------------
    /** Returns the list of AI karts to use. Used for networking, and for
    *  the --ai= command line option. */
    const std::vector<std::string>& getAIKartList() const
    {
        return m_ai_kart_list;
    }   // getAIKartList
    // ------------------------------------------------------------------------
    /** \brief get information about current mode (returns true if 'mode' is of
    *  linear races type) */
    bool isLinearRaceMode() const
    {
        const int id = (int)m_minor_mode;
        // info is stored in its ID for conveniance, see the macros LINEAR_RACE
        // and BATTLE_ARENA above for exact meaning.
        if(id > 999 && id < 2000) return true;
        else return false;
    }   // isLinearRaceMode

    // ------------------------------------------------------------------------
    /** \brief get information about given mode (returns true if 'mode' is of
    *  linear races type) */
    bool isLinearRaceMode(const MinorRaceModeType mode) const
    {
        const int id = (int)mode;
        // info is stored in its ID for conveniance, see the macros LINEAR_RACE
        // and BATTLE_ARENA above for exact meaning.
        if(id > 999 && id < 2000) return true;
        else return false;
    }   // isLinearRaceMode

    // ------------------------------------------------------------------------
    /** \brief Returns true if the current mode is a battle mode. */
    bool isBattleMode() const
    {
        const int id = (int)m_minor_mode;
        // This uses the  numerical id of the mode, see the macros
        // LINEAR_RACE and BATTLE_ARENA above for exact meaning.
        if (id >= 2000 && id <= 2002) return true;
        else            return false;
    }   // isBattleMode

    // ------------------------------------------------------------------------
    /** \brief Returns true if the current mode is a soccer mode. */
    bool isSoccerMode() const
    {
        const int id = (int)m_minor_mode;
        // This uses the  numerical id of the mode, see the macros
        // LINEAR_RACE and BATTLE_ARENA above for exact meaning.
        if (id == 2003) return true;
        else            return false;
    }   // isSoccerMode

    // ----------------------------------------------------------------------------------------
    bool isFollowMode() const    { return m_minor_mode == MINOR_MODE_FOLLOW_LEADER; }

    // ----------------------------------------------------------------------------------------
    bool isCTFMode() const       { return m_minor_mode == MINOR_MODE_CAPTURE_THE_FLAG; }
 
    // ----------------------------------------------------------------------------------------
    bool isEggHuntMode() const   { return m_minor_mode == MINOR_MODE_EASTER_EGG; }

    // ----------------------------------------------------------------------------------------
    bool isTimeTrialMode() const { return m_minor_mode == MINOR_MODE_TIME_TRIAL; }
    // ----------------------------------------------------------------------------------------
     /** \brief Returns the number of second's decimals to display */
    int currentModeTimePrecision() const
    {
        if (isEggHuntMode() || isTimeTrialMode())
            return 3;//display milliseconds

        return 2;//display centiseconds
    }   // currentModeTimePrecision
    // ------------------------------------------------------------------------
    /** \brief Returns true if the current mode has laps. */
    bool modeHasLaps() const
    {
        if (!isLinearRaceMode()) return false;
        const int id = (int)m_minor_mode;
        // See meaning of IDs above
        const int answer = (id-1000)/100;
        return answer!=0;
    }   // modeHasLaps
    // ------------------------------------------------------------------------
    /** Returns true if the currently selected minor mode has highscores. */
    bool modeHasHighscores()
    {
        //FIXME: this information is duplicated. RaceManager knows about it,
        //       and each World may set m_use_highscores to true or false.
        //       The reason for this duplication is that we might want to know
        //       whether to display highscores without creating a World.
        return !isBattleMode() &&
               !isSoccerMode() &&
               m_minor_mode != MINOR_MODE_FOLLOW_LEADER;
    }   // modeHasHighscore
    // ------------------------------------------------------------------------
    /** \name Callbacks from the race classes
     * These methods are to be used by the classes that manage the various
     *  races, to let the race manager know about current status
     */
    bool allPlayerFinished() const
    {
        return m_num_finished_players == m_player_karts.size();
    }   // allPlayerFinished
    // ------------------------------------------------------------------------
    /** Sets the AI to use. This is used in networking mode to set the karts
     *  that will be used by the server to the client. It will take precedence
     *  over the random selection. */
    void setAIKartList(const std::vector<std::string>& rkl)
    {
        m_ai_kart_list = rkl;
    }   // setAIKartList
    // ------------------------------------------------------------------------
    void setRecordRace(bool record)
    {
        m_is_recording_race = record;
    }   // setRecordRace
    // ------------------------------------------------------------------------
    bool isRecordingRace() const
    {
        return m_is_recording_race;
    }   // isRecordingRace
    // ------------------------------------------------------------------------
    void addSpareTireKart(const std::string& name)
    {
        m_kart_status.push_back(KartStatus(name, 0, -1, -1,
            -1, KT_SPARE_TIRE, PLAYER_DIFFICULTY_NORMAL));
        m_num_spare_tire_karts++;
        m_num_karts++;
    }   // addSpareTireKart
    // ------------------------------------------------------------------------
    void setSpareTireKartNum(unsigned int i)
    {
        m_num_spare_tire_karts = i;
    }   // setSpareTireKartNum
    // ------------------------------------------------------------------------
    unsigned int getNumSpareTireKarts() const
    {
        return m_num_spare_tire_karts;
    }   // getNumSpareTireKarts
    // ------------------------------------------------------------------------
    void setHitCaptureTime(int hc, float time)
    {
        m_hit_capture_limit = hc;
        m_time_target = time;
    }
    // ------------------------------------------------------------------------
    int getHitCaptureLimit() const              { return m_hit_capture_limit; }
    // ------------------------------------------------------------------------
    bool teamEnabled() const
    {
        return m_minor_mode == MINOR_MODE_SOCCER ||
            m_minor_mode == MINOR_MODE_CAPTURE_THE_FLAG;
    }
    // ------------------------------------------------------------------------
    void setFlagReturnTicks(unsigned ticks)    { m_flag_return_ticks = ticks; }
    // ------------------------------------------------------------------------
    unsigned getFlagReturnTicks() const         { return m_flag_return_ticks; }
    // ------------------------------------------------------------------------
    void setFlagDeactivatedTicks(unsigned ticks)
                                          { m_flag_deactivated_ticks = ticks; }
    // ------------------------------------------------------------------------
    unsigned getFlagDeactivatedTicks() const
                                           { return m_flag_deactivated_ticks; }
    // ------------------------------------------------------------------------
    /** Whether the current game mode allow live joining even the current game
     *. started in network*/
    bool supportsLiveJoining() const
    {
        return m_minor_mode == MINOR_MODE_SOCCER ||
            m_minor_mode == MINOR_MODE_CAPTURE_THE_FLAG ||
            m_minor_mode == MINOR_MODE_FREE_FOR_ALL;
    }
};   // RaceManager

extern RaceManager *race_manager;
#endif

/* EOF */
