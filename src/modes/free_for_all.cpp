//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2018 SuperTuxKart-Team
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

#include "modes/free_for_all.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"

#include "tracks/track.hpp"
#include "utils/string_utils.hpp"

#include <algorithm>
#include <utility>

// ----------------------------------------------------------------------------
/** Constructor. Sets up the clock mode etc.
 */
FreeForAll::FreeForAll() : WorldWithRank()
{
}   // FreeForAll

// ----------------------------------------------------------------------------
FreeForAll::~FreeForAll()
{
}   // ~FreeForAll

// ----------------------------------------------------------------------------
void FreeForAll::init()
{
    WorldWithRank::init();
    m_display_rank = false;
    m_count_down_reached_zero = false;
}   // init

// ----------------------------------------------------------------------------
/** Called when a battle is restarted.
 */
void FreeForAll::reset(bool restart)
{
    WorldWithRank::reset(restart);
    m_count_down_reached_zero = false;
    m_scores.clear();
    m_scores.resize(m_karts.size(), 0);
}   // reset

// ----------------------------------------------------------------------------
/** Called when the match time ends.
 */
void FreeForAll::countdownReachedZero()
{
    // Prevent negative time in network soccer when finishing
    m_time_ticks = 0;
    m_time = 0.0f;
    m_count_down_reached_zero = true;
}   // countdownReachedZero

// ----------------------------------------------------------------------------
/** Called when a kart is hit.
 *  \param kart_id The world kart id of the kart that was hit.
 *  \param hitter The world kart id of the kart who hit(-1 if none).
 */
bool FreeForAll::kartHit(int kart_id, int hitter)
{
    if (isRaceOver())
        return false;

    handleScoreInServer(kart_id, hitter);
    return true;
}   // kartHit

// ----------------------------------------------------------------------------
/** Called when the score of kart needs updated.
 *  \param kart_id The world kart id of the kart that was hit.
 *  \param hitter The world kart id of the kart who hit(-1 if none).
 */
void FreeForAll::handleScoreInServer(int kart_id, int hitter)
{
    int new_score = 0;
    if (kart_id == hitter || hitter == -1)
        new_score = --m_scores[kart_id];
    else
        new_score = ++m_scores[hitter];

}   // handleScoreInServer

// ----------------------------------------------------------------------------
/** Returns the internal identifier for this race.
 */
const std::string& FreeForAll::getIdent() const
{
    return IDENT_FFA;
}   // getIdent

// ------------------------------------------------------------------------
void FreeForAll::update(int ticks)
{
    WorldWithRank::update(ticks);
    WorldWithRank::updateTrack(ticks);
    if (Track::getCurrentTrack()->hasNavMesh())
        updateSectorForKarts();

    std::vector<std::pair<int, int> > ranks;
    for (unsigned i = 0; i < m_scores.size(); i++)
    {
        // For eliminated (disconnected or reserved player) make his score
        // int min so always last in rank
        int cur_score = getKart(i)->isEliminated() ?
            std::numeric_limits<int>::min() : m_scores[i];
        ranks.emplace_back(i, cur_score);
    }
    std::sort(ranks.begin(), ranks.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b)
        {
            return a.second > b.second;
        });
    beginSetKartPositions();
    for (unsigned i = 0; i < ranks.size(); i++)
        setKartPosition(ranks[i].first, i + 1);
    endSetKartPositions();
}   // update

// ----------------------------------------------------------------------------
/** The battle is over if only one kart is left, or no player kart.
 */
bool FreeForAll::isRaceOver()
{
    if (!getKartAtPosition(1))
        return false;

    const int top_id = getKartAtPosition(1)->getWorldKartId();
    const int hit_capture_limit = race_manager->getHitCaptureLimit();

    return (m_count_down_reached_zero && race_manager->hasTimeTarget()) ||
        (hit_capture_limit != 0 && m_scores[top_id] >= hit_capture_limit);
}   // isRaceOver

// ----------------------------------------------------------------------------
void FreeForAll::terminateRace()
{
    const unsigned int kart_amount = getNumKarts();
    for (unsigned int i = 0; i < kart_amount ; i++)
    {
        getKart(i)->finishedRace(0.0f, true/*from_server*/);
    }   // i<kart_amount
    WorldWithRank::terminateRace();
}   // terminateRace

// ----------------------------------------------------------------------------
video::SColor FreeForAll::getColor(unsigned int kart_id) const
{
    return video::SColor(255,255,128,0);
}   // getColor

// ----------------------------------------------------------------------------
bool FreeForAll::getKartFFAResult(int kart_id) const
{
    // the kart(s) which has the top score wins
    AbstractKart* k = getKartAtPosition(1);
    if (!k)
        return false;
    int top_score = getKartScore(k->getWorldKartId());
    return getKartScore(kart_id) == top_score;
}   // getKartFFAResult

// ----------------------------------------------------------------------------
std::pair<uint32_t, uint32_t> FreeForAll::getGameStartedProgress() const
{
    std::pair<uint32_t, uint32_t> progress(
        std::numeric_limits<uint32_t>::max(),
        std::numeric_limits<uint32_t>::max());
    if (race_manager->hasTimeTarget())
    {
        progress.first = (uint32_t)m_time;
    }
    AbstractKart* k = getKartAtPosition(1);
    float score = -1.0f;
    if (k)
        score = (float)getKartScore(k->getWorldKartId());

    if (score >= 0.0f)
    {
        progress.second = (uint32_t)(score /
            (float)race_manager->getHitCaptureLimit() * 100.0f);
    }
    return progress;
}   // getGameStartedProgress
