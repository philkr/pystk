//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2012-2015 SuperTuxKart-Team
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

#include "config/player_profile.hpp"

#include "io/file_manager.hpp"
#include "io/utf_writer.hpp"
#include "io/xml_node.hpp"
#include "karts/kart_properties.hpp"
#include "karts/kart_properties_manager.hpp"
#include "utils/string_utils.hpp"

//------------------------------------------------------------------------------
/** Constructor to create a new player that didn't exist before.
 *  \param name Name of the player.
 *  \param is_guest True if this is a guest account.
*/
PlayerProfile::PlayerProfile(const core::stringw& name)
{
#ifdef DEBUG
    m_magic_number = 0xABCD1234;
#endif
    m_local_name          = name;
    m_default_kart_color  = 0.0f;
    initRemainingData();
}   // PlayerProfile

//------------------------------------------------------------------------------
/** Constructor to deserialize player data that was saved to a XML file. The
 *  constructor will only load the main player data (like name, id, saved
 *  online data), but not the achievements and story mode data. Reason is
 *  that the achievement and story mode data depends on other data to be
 *  read first (challenges and achievement files), which in turn can only be
 *  created later in the startup process (they depend on e.g. all tracks to
 *  be known). On the other hand, automatic login needs to happen asap (i.e.
 *  as soon as the network thread is started) to avoid the player having to
 *  wait for the login to finish , which needs the main player data (i.e.
 *  the default player, and saved session data). So the constructor only
 *  reads this data, the rest of the player data is handled in
 *  loadRemainingData later in the initialisation process.
 *  \param node The XML node representing this player.
*/
PlayerProfile::PlayerProfile(const XMLNode* node)
{
#ifdef DEBUG
    m_magic_number = 0xABCD1234;
#endif
    node->getAndDecode("name",      &m_local_name);
    node->get("default-kart-color", &m_default_kart_color);
    initRemainingData();
}   // PlayerProfile

//------------------------------------------------------------------------------
PlayerProfile::~PlayerProfile()
{
#ifdef DEBUG
    m_magic_number = 0xDEADBEEF;
#endif
}   // ~PlayerProfile


//------------------------------------------------------------------------------
/** Initialises the story- and achievement data structure in case of the first
 *  start of STK.
 */
void PlayerProfile::initRemainingData()
{
}   // initRemainingData

bool PlayerProfile::operator<(const PlayerProfile &other) {
	return getName() < other.getName();
}

// //------------------------------------------------------------------------------
// /** Returns the name of the icon file for this player. If the player icon
//  *  file is undefined, it returns a "?" mark texture. Note, getAsset does
//  *  not return a reference, but only a temporary string. So we must return a
//  *  copy of the string (not a reference to).
//  */
// const std::string PlayerProfile::getIconFilename() const
// {
//     // If the icon file is undefined or does not exist, return the "?" icon
//     if(m_icon_filename.size()==0 ||
//        !file_manager->fileExists(file_manager->getUserConfigFile(m_icon_filename)))
//     {
//         return file_manager->getAsset(FileManager::GUI_ICON, "main_help.png");
//     }
// 
//     return file_manager->getUserConfigFile(m_icon_filename);
// }   // getIconFilename

//------------------------------------------------------------------------------
/** Writes the data for this player to the specified UTFWriter.
 *  \param out The utf writer to write the data to.
 */
void PlayerProfile::save(UTFWriter &out)
{
    out << "    <player name=\"" << StringUtils::xmlEncode(m_local_name)
        << "            default-kart-color=\""        << m_default_kart_color << "\">\n"
        << "    </player>\n";
}   // save

// -----------------------------------------------------------------------------

