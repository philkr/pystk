//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2015 SuperTuxKart-Team
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

#ifndef HEADER_PLAYER_PROFILE_HPP
#define HEADER_PLAYER_PROFILE_HPP

#include "network/remote_kart_info.hpp"
#include "utils/leak_check.hpp"
#include "utils/no_copy.hpp"
#include "utils/types.hpp"

#include <irrString.h>
using namespace irr;

#include <string>

class UTFWriter;
class XMLNode;

/** Class for managing player profiles (name, usage frequency,
 *  etc.). All PlayerProfiles are managed by the PlayerManager.
 *  A PlayerProfile keeps track of the story mode progress using an instance
 *  of StoryModeStatus, and achievements with AchievementsStatus. All data
 *  is saved in the players.xml file.
 *  This class also defines the interface for handling online data. All of
 *  the online handling is done in the derived class OnlinePlayerProfile,
 *  where the interface is fully implemented.
 * \ingroup config
 */
class PlayerProfile : public NoCopy
{
public:
//     /** The online state a player can be in. */
//     enum OnlineState
//     {
//         OS_SIGNED_OUT = 0,
//         OS_SIGNED_IN,
//         OS_GUEST,
//         OS_SIGNING_IN,
//         OS_SIGNING_OUT
//     };
// 

private:
    LEAK_CHECK()

#ifdef DEBUG
    unsigned int m_magic_number;
#endif

    /** The name of the player (wide string, so it can be in native
     *  language). */
    core::stringw m_local_name;

    /** Default kart color (in hue) used in game, 0.0f to use the original. */
    float m_default_kart_color;

public:

    PlayerProfile(const XMLNode* node);
    PlayerProfile(const core::stringw &name);
    virtual ~PlayerProfile();
    void save(UTFWriter &out);
    void initRemainingData();
    void incrementUseFrequency();
    bool operator<(const PlayerProfile &other);

    /** Sets the name of this player. */
    void setName(const core::stringw& name)
    {
        #ifdef DEBUG
        assert(m_magic_number == 0xABCD1234);
        #endif
        m_local_name = name;
    }   // setName

    // ------------------------------------------------------------------------
    /** Returns the name of this player. */
    const core::stringw& getName() const
    {
        #ifdef DEBUG
        assert(m_magic_number == 0xABCD1234);
        #endif
        return m_local_name;
    }   // getName

    // ------------------------------------------------------------------------
    void setDefaultKartColor(float c) { m_default_kart_color = c; }
    // ------------------------------------------------------------------------
    float getDefaultKartColor() const { return m_default_kart_color; }

};   // class PlayerProfile

#endif

/*EOF*/
