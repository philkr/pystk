//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006-2016 SuperTuxKart-Team
//  Modeled after Supertux's configfile.cpp
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


#include <vector>

// The order here is important. If all_params is declared later (e.g. after
// the #includes), all elements will be added to all_params, and then
// all_params will be initialised, i.e. cleared!
class UserConfigParam;
static std::vector<UserConfigParam*> all_params;

// X-macros
#define PARAM_PREFIX
#define PARAM_DEFAULT(X) = X
#include "config/user_config.hpp"

#include "config/stk_config.hpp"
#include "io/file_manager.hpp"
#include "io/utf_writer.hpp"
#include "io/xml_node.hpp"
#include "race/race_manager.hpp"
#include "utils/file_utils.hpp"
#include "utils/log.hpp"
#include "utils/string_utils.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

// ----------------------------------------------------------------------------
UserConfigParam::~UserConfigParam()
{
    if (m_can_be_deleted)
    {
        auto it = std::find(all_params.begin(), all_params.end(), this);
        if (it != all_params.end())
            all_params.erase(it);
    }
}   // ~UserConfigParam

// ----------------------------------------------------------------------------
/** Writes an inner node.
 *  \param stream the xml writer.
 *  \param level determines indentation level.
 */
void UserConfigParam::writeInner(std::stringstream& stream, int level) const
{
    std::string tab(level * 4,' ');
    stream << "    " << tab.c_str() << m_param_name.c_str() << "=\""
           << toString().c_str() << "\"\n";
}   // writeInner

// ============================================================================
GroupUserConfigParam::GroupUserConfigParam(const char* group_name,
                                           const char* comment)
{
    m_param_name = group_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // GroupUserConfigParam

// ============================================================================
GroupUserConfigParam::GroupUserConfigParam(const char* group_name,
                                           GroupUserConfigParam* group,
                                           const char* comment)
{
    m_param_name = group_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // GroupUserConfigParam

// ----------------------------------------------------------------------------
void GroupUserConfigParam::write(std::stringstream& stream) const
{
    const int attr_amount = (int)m_attributes.size();

    // comments
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str();
    for(int n=0; n<attr_amount; n++)
    {
        if(m_attributes[n]->m_comment.size() > 0)
            stream << "\n             " << m_attributes[n]->m_param_name.c_str()
                   << " : " << m_attributes[n]->m_comment.c_str();
    }

    stream << " -->\n    <" << m_param_name.c_str() << "\n";

    // actual values
    for (int n=0; n<attr_amount; n++)
    {
        m_attributes[n]->writeInner(stream, 1);
    }
    stream << "    >\n";
    const int children_amount = (int)m_children.size();
    for (int n=0; n<children_amount; n++)
    {
        m_children[n]->writeInner(stream, 1);
    }
    stream << "    </" << m_param_name.c_str() << ">\n\n";
}   // write

// ----------------------------------------------------------------------------
void GroupUserConfigParam::writeInner(std::stringstream& stream, int level) const
{
    std::string tab(level * 4,' ');
    for(int i = 0; i < level; i++) tab =+ "    ";
    const int  children_amount = (int)m_attributes.size();

    stream << "    " << tab.c_str() << "<" << m_param_name.c_str() << "\n";

    // actual values
    for (int n=0; n<children_amount; n++)
    {
        m_attributes[n]->writeInner(stream, level+1);
    }
    stream << "    " << tab.c_str() << "/>\n";
}   // writeInner

// ----------------------------------------------------------------------------
void GroupUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if (child == NULL)
    {
        //Log::error("User Config", "Couldn't find parameter group %s", m_param_name.c_str());
        return;
    }

    const int attributes_amount = (int)m_attributes.size();
    for (int n=0; n<attributes_amount; n++)
    {
        m_attributes[n]->findYourDataInAnAttributeOf(child);
    }

}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void GroupUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
}   // findYourDataInAnAttributeOf

// ----------------------------------------------------------------------------
irr::core::stringc GroupUserConfigParam::toString() const
{
    return "";
}   // toString

// ----------------------------------------------------------------------------
void GroupUserConfigParam::clearChildren()
{
    m_children.clear();
}   // clearChildren

// ----------------------------------------------------------------------------
void GroupUserConfigParam::addChild(GroupUserConfigParam* child)
{
    m_children.push_back(child);
}   // addChild

// ----------------------------------------------------------------------------
void GroupUserConfigParam::addChild(UserConfigParam* child)
{
    m_attributes.push_back(child);
}   // addChild

// ----------------------------------------------------------------------------
template<typename T, typename U>
MapUserConfigParam<T, U>::MapUserConfigParam(const char* param_name,
    const char* comment, std::array<std::string, 3> key_names,
    std::map<T, U> default_value)
{
    m_param_name = param_name;
    all_params.push_back(this);
    if (comment != NULL) m_comment = comment;

    m_key_names = key_names;
    m_elements = default_value;
}   // MapUserConfigParam

// ----------------------------------------------------------------------------
template<typename T, typename U>
MapUserConfigParam<T, U>::MapUserConfigParam(const char* param_name,
    GroupUserConfigParam* group,
    const char* comment)
{
    m_param_name = param_name;
    group->addChild(this);
    if (comment != NULL) m_comment = comment;
}   // MapUserConfigParam

// ----------------------------------------------------------------------------
template<typename T, typename U>
MapUserConfigParam<T, U>::MapUserConfigParam(const char* param_name,
    GroupUserConfigParam* group, const char* comment,
    std::array<std::string, 3> key_names, std::map<T, U> default_value)
{
    m_param_name = param_name;
    group->addChild(this);
    if (comment != NULL) m_comment = comment;

    m_key_names = key_names;
    m_elements = default_value;
}   // MapUserConfigParam

// ----------------------------------------------------------------------------
template<typename T, typename U>
void MapUserConfigParam<T, U>::write(std::stringstream& stream) const
{
    // comment
    if (m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str();
    stream << " -->\n    <" << m_param_name.c_str() << ">\n";

    for (const auto& kv : m_elements)
    {
        stream << "        <" << m_key_names[0] << " " << m_key_names[1] <<
            "=\"" << kv.first << "\" " <<  m_key_names[2] << "=\"" <<
            kv.second << "\"/>\n";
    }
    stream << "    </" << m_param_name.c_str() << ">\n\n";
}   // write

// ----------------------------------------------------------------------------
template<typename T, typename U>
void MapUserConfigParam<T, U>::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode(m_param_name);
    if (child == NULL)
    {
        Log::error("User Config", "Couldn't find parameter group %s",
          m_param_name.c_str());
        return;
    }
    for (unsigned i = 0; i < child->getNumNodes(); i++)
    {
        const std::string& map_name = m_key_names[0];
        const std::string& key_name = m_key_names[1];
        const std::string& value_name = m_key_names[2];
        const XMLNode* map = child->getNode(i);
        if (map->getName() != map_name)
        {
            Log::error("User Config", "Invalid name %s",
                map->getName().c_str());
            continue;
        }

        T key;
        std::string key_string;
        if (!map->get(key_name, &key_string) ||
            !StringUtils::fromString(key_string, key))
        {
            Log::error("User Config", "Invalid key name %s",
                key_name.c_str());
            continue;
        }

        U value;
        std::string value_string;
        if (!map->get(value_name, &value_string) ||
            !StringUtils::fromString(value_string, value))
        {
            Log::error("User Config", "Invalid value name %s",
                value_name.c_str());
            continue;
        }
        m_elements[key] = value;
    }
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
template<typename T, typename U>
void MapUserConfigParam<T, U>::findYourDataInAnAttributeOf(const XMLNode* node)
{
}   // findYourDataInAnAttributeOf

// ----------------------------------------------------------------------------
template<typename T, typename U>
void MapUserConfigParam<T, U>::addElement(T element, U value)
{
    m_elements[element] = value;
}   // findYourDataInAnAttributeOf

// ----------------------------------------------------------------------------
template<typename T, typename U>
core::stringc MapUserConfigParam<T, U>::toString() const
{
    return "";
}   // toString

// ----------------------------------------------------------------------------
IntUserConfigParam::IntUserConfigParam(int default_value,
                                       const char* param_name,
                                       const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name    = param_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // IntUserConfigParam

// ----------------------------------------------------------------------------
IntUserConfigParam::IntUserConfigParam(int default_value,
                                       const char* param_name,
                                       GroupUserConfigParam* group,
                                       const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name    = param_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // IntUserConfigParam

// ----------------------------------------------------------------------------
void IntUserConfigParam::write(std::stringstream& stream) const
{
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str()
                                    << " -->\n";
    stream << "    <" << m_param_name.c_str() << " value=\"" << m_value
           << "\" />\n\n";
}   // write

// ----------------------------------------------------------------------------
irr::core::stringc IntUserConfigParam::toString() const
{
    irr::core::stringc tmp;
    tmp += m_value;

    return tmp;
}   // toString

// ----------------------------------------------------------------------------
void IntUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if(child == NULL)
    {
        //Log::error("UserConfigParam", "Couldn't find int parameter %s", m_param_name.c_str());
        return;
    }

    child->get( "value", &m_value );
    //Log::info("UserConfigParam", "Read int %s ,value = %d", m_param_name.c_str(), value);
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void IntUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
    node->get( m_param_name, &m_value );
}   // findYourDataInAnAttributeOf

// ============================================================================
TimeUserConfigParam::TimeUserConfigParam(StkTime::TimeType default_value,
                                         const char* param_name,
                                         const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name    = param_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // TimeUserConfigParam

// ----------------------------------------------------------------------------
TimeUserConfigParam::TimeUserConfigParam(StkTime::TimeType default_value,
                                         const char* param_name,
                                         GroupUserConfigParam* group,
                                         const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name    = param_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // TimeUserConfigParam

// ----------------------------------------------------------------------------
void TimeUserConfigParam::write(std::stringstream& stream) const
{
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str()
                                    << " -->\n";
    std::stringstream o;
    o<<m_value;
    stream << "    <" << m_param_name.c_str() << " value=\""
           << o.str().c_str() << "\" />\n\n";
}   // write

// ----------------------------------------------------------------------------
irr::core::stringc TimeUserConfigParam::toString() const
{
    // irrString does not have a += with a 64-bit int type, so
    // we can't use an irrlicht's stringw directly. Since it's only a
    // number, we can use std::string, and convert to stringw

    std::stringstream o;
    o<<m_value;
    return o.str().c_str();
}   // toString

// ----------------------------------------------------------------------------
void TimeUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if(child == NULL)
    {
        //Log::error("UserConfigParam", "Couldn't find int parameter %s", m_param_name.c_str());
        return;
    }

    int64_t tmp;
    child->get( "value", &tmp );
    m_value = tmp;
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void TimeUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
    int64_t tmp;
    node->get( m_param_name, &tmp );
    m_value = tmp;
}   // findYourDataInAnAttributeOf

// ============================================================================
StringUserConfigParam::StringUserConfigParam(const char* default_value,
                                             const char* param_name,
                                             const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name    = param_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // StringUserConfigParam

// ----------------------------------------------------------------------------
StringUserConfigParam::StringUserConfigParam(const char* default_value,
                                             const char* param_name,
                                             GroupUserConfigParam* group,
                                             const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;
    m_param_name = param_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // StringUserConfigParam

// ----------------------------------------------------------------------------
void StringUserConfigParam::write(std::stringstream& stream) const
{
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str()
                                    << " -->\n";
    stream << "    <" << m_param_name.c_str() << " value=\""
           << m_value.c_str() << "\" />\n\n";
}   // write

// ----------------------------------------------------------------------------
void StringUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if(child == NULL) return;

    child->get( "value", &m_value );
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void StringUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
    node->get( m_param_name, &m_value );
}   // findYourDataInAnAttributeOf

// ============================================================================
BoolUserConfigParam::BoolUserConfigParam(bool default_value,
                                         const char* param_name,
                                         const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;

    m_param_name = param_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // BoolUserConfigParam

// ----------------------------------------------------------------------------
BoolUserConfigParam::BoolUserConfigParam(bool default_value,
                                         const char* param_name,
                                         GroupUserConfigParam* group,
                                         const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;

    m_param_name = param_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // BoolUserConfigParam


// ----------------------------------------------------------------------------
void BoolUserConfigParam::write(std::stringstream& stream) const
{
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str()
                                    << " -->\n";
    stream << "    <" << m_param_name.c_str() << " value=\""
           << (m_value ? "true" : "false" ) << "\" />\n\n";
}   // write

// ----------------------------------------------------------------------------
void BoolUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if(child == NULL) return;

    std::string text_value = "";
    child->get( "value", &text_value );

    if(text_value == "true")
    {
        m_value = true;
    }
    else if(text_value == "false")
    {
        m_value = false;
    }
    else
    {
        Log::error("User Config", "Unknown value for %s; expected true or false", m_param_name.c_str());
    }
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void BoolUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
    std::string text_value = "";
    node->get( m_param_name, &text_value );

    if (text_value == "true")
    {
        m_value = true;
    }
    else if (text_value == "false")
    {
        m_value = false;
    }
    else
    {
        Log::error("User Config", "Unknown value for %s; expected true or false", m_param_name.c_str());
    }
}   // findYourDataInAnAttributeOf

// ----------------------------------------------------------------------------
irr::core::stringc BoolUserConfigParam::toString() const
{
    return (m_value ? "true" : "false" );
}   // toString

// ============================================================================
FloatUserConfigParam::FloatUserConfigParam(float default_value,
                                           const char* param_name,
                                           const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;

    m_param_name = param_name;
    all_params.push_back(this);
    if(comment != NULL) m_comment = comment;
}   // FloatUserConfigParam

// ----------------------------------------------------------------------------
FloatUserConfigParam::FloatUserConfigParam(float default_value,
                                           const char* param_name,
                                           GroupUserConfigParam* group,
                                           const char* comment)
{
    m_value         = default_value;
    m_default_value = default_value;

    m_param_name = param_name;
    group->addChild(this);
    if(comment != NULL) m_comment = comment;
}   // FloatUserConfigParam

// ----------------------------------------------------------------------------
void FloatUserConfigParam::write(std::stringstream& stream) const
{
    if(m_comment.size() > 0) stream << "    <!-- " << m_comment.c_str()
                                    << " -->\n";
    stream << "    <" << m_param_name.c_str() << " value=\"" << m_value
           << "\" />\n\n";
}   // write

// ----------------------------------------------------------------------------
void FloatUserConfigParam::findYourDataInAChildOf(const XMLNode* node)
{
    const XMLNode* child = node->getNode( m_param_name );
    if(child == NULL) return;

    child->get( "value", &m_value );
}   // findYourDataInAChildOf

// ----------------------------------------------------------------------------
void FloatUserConfigParam::findYourDataInAnAttributeOf(const XMLNode* node)
{
    node->get( m_param_name, &m_value );
}   // findYourDataInAnAttributeOf

// ----------------------------------------------------------------------------
core::stringc FloatUserConfigParam::toString() const
{
    irr::core::stringc tmp;
    tmp += m_value;
    return tmp;
}   // toString

// =====================================================================================


int UserConfigParams::m_default_num_karts = 4;
int UserConfigParams::m_num_laps = 4;
int UserConfigParams::m_ffa_time_limit = 3;
bool UserConfigParams::m_use_ffa_mode = false;
int UserConfigParams::m_num_goals = 3;
int UserConfigParams::m_soccer_default_team = 0;
int UserConfigParams::m_soccer_time_limit = 3;
bool UserConfigParams::m_soccer_use_time_limit = false;
bool UserConfigParams::m_random_arena_item = false;
int UserConfigParams::m_difficulty = 0;
int UserConfigParams::m_game_mode = 0;
std::string UserConfigParams::m_default_kart = "tux";

int UserConfigParams::m_width = 1024;
int UserConfigParams::m_height = 768;

bool UserConfigParams::m_texture_compression = true;
int UserConfigParams::m_high_definition_textures = 1;
bool UserConfigParams::m_glow = false;
bool UserConfigParams::m_bloom = false;
bool UserConfigParams::m_light_shaft = false;
bool UserConfigParams::m_dynamic_lights = true;
bool UserConfigParams::m_dof = false;
float UserConfigParams::m_scale_rtts_factor = 1.0f;
int UserConfigParams::m_max_texture_size = 512;

int UserConfigParams::m_particles_effects = 2;
bool UserConfigParams::m_animated_characters = true;
int UserConfigParams::m_geometry_level = GEOLEVEL_0;

int UserConfigParams::m_anisotropic = 4;
bool UserConfigParams::m_motionblur = false;
bool UserConfigParams::m_mlaa = false;
bool UserConfigParams::m_ssao = false;
bool UserConfigParams::m_light_scatter = true;
int UserConfigParams::m_shadows_resolution = 0;
bool UserConfigParams::m_degraded_IBL = true;

// ---- Misc
int UserConfigParams::m_reverse_look_threshold = 0;
float UserConfigParams::m_fpscam_direction_speed = 0.003f;
float UserConfigParams::m_fpscam_smooth_direction_max_speed = 0.04f;
float UserConfigParams::m_fpscam_angular_velocity = 0.02f;
float UserConfigParams::m_fpscam_max_angular_velocity = 1.0f;

// =====================================================================================
