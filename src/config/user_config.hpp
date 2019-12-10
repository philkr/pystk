//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006-2015 SuperTuxKart-Team
//  Modelled after Supertux's configfile.h
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

#ifndef HEADER_USER_CONFIG_HPP
#define HEADER_USER_CONFIG_HPP

/* The following config versions are currently used:
   0: the 0.2 release config file, without config-version number
      (so that defaults to 0)
   1: Removed singleWindowMenu, newKeyboardStyle, oldStatusDisplay,
      added config-version number
      Version 1 can read version 0 without any problems, so
      SUPPORTED_CONFIG_VERSION is 0.
   2: Changed to SDL keyboard bindings
   3: Added username (userid was used for ALL players)
   4: Added username per player
   5: Enabled jumping, which might cause a problem with old
      config files (which have an unused entry for jump defined
      --> if a kart control for (say) player 2 uses the same key as
      jump for player 1, this problem is not noticed in 0.3, but will
      cause an undefined game action now
   6: Added stick configurations.
*/
#include <array>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#include <irrString.h>
using irr::core::stringc;
using irr::core::stringw;

#include "utils/constants.hpp"
#include "utils/no_copy.hpp"
#include "utils/ptr_vector.hpp"
#include "utils/time.hpp"

class SavedGrandPrix;
class XMLNode;
class UTFWriter;

/**
 *  The base of a set of small utilities to enable quickly adding/removing
 *  stuff to/from config painlessly.
 */
class UserConfigParam
{
    friend class GroupUserConfigParam;
protected:
    bool m_can_be_deleted = true;
    std::string m_param_name;
    std::string m_comment;
public:
    virtual     ~UserConfigParam();
    virtual void write(std::stringstream & stream) const = 0;
    virtual void writeInner(std::stringstream & stream, int level = 0) const;
    virtual void findYourDataInAChildOf(const XMLNode* node) = 0;
    virtual void findYourDataInAnAttributeOf(const XMLNode* node) = 0;
    virtual irr::core::stringc toString() const = 0;
};   // UserConfigParam

// ============================================================================
class GroupUserConfigParam : public UserConfigParam
{
    std::vector<UserConfigParam*> m_attributes;
    std::vector<GroupUserConfigParam*> m_children;
public:
    GroupUserConfigParam(const char* name, const char* comment=NULL);
    GroupUserConfigParam(const char* param_name,
                       GroupUserConfigParam* group,
                       const char* comment = NULL);
    void write(std::stringstream& stream) const;
    void writeInner(std::stringstream& stream, int level = 0) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    void addChild(UserConfigParam* child);
    void addChild(GroupUserConfigParam* child);
    void clearChildren();

    irr::core::stringc toString() const;
};   // GroupUserConfigParam

// ============================================================================
/** ATM only map with 1 key and 1 value is supported
 */
template<typename T, typename U>
class MapUserConfigParam : public UserConfigParam
{
protected:
    std::array<std::string, 3> m_key_names;
    std::map<T, U> m_elements;
    MapUserConfigParam(const char* param_name,
                       const char* comment)
    {
        m_param_name = param_name;
        if (comment != NULL)
            m_comment = comment;
    }

public:
    MapUserConfigParam(const char* param_name,
        const char* comment,
        std::array<std::string, 3> key_names,
        std::map<T, U> default_value);
    MapUserConfigParam(const char* param_name,
        GroupUserConfigParam* group,
        const char* comment = NULL);
    MapUserConfigParam(const char* param_name,
        GroupUserConfigParam* group,
        const char* comment, std::array<std::string, 3> key_names,
        std::map<T, U> default_value);

    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    void addElement(T element, U value);

    irr::core::stringc toString() const;

    operator std::map<T, U>() const
    {
        return m_elements;
    }
    typename std::map<T, U>::iterator begin()
    {
        return m_elements.begin();
    }
    typename std::map<T, U>::iterator end()
    {
        return m_elements.end();
    }
    std::map<T, U>& operator=(const std::map<T,U>& v)
    {
        m_elements = std::map<T, U>(v);
        return m_elements;
    }
    std::map<T, U>& operator=(const MapUserConfigParam& v)
    {
        m_elements = std::map<T,U>(v);
        return m_elements;
    }
    U& operator[] (const T key)
    {
        return m_elements[key];
    }
    U& at(const T key)
    {
        return m_elements.at(key);
    }
};   // MapUserConfigParam
typedef MapUserConfigParam<uint32_t, uint32_t> UIntToUIntUserConfigParam;
typedef MapUserConfigParam<std::string, uint32_t> StringToUIntUserConfigParam;
// ============================================================================
class IntUserConfigParam : public UserConfigParam
{
protected:
    int m_value;
    int m_default_value;
    IntUserConfigParam(const char* param_name, const char* comment)
    {
        m_param_name = param_name;
        if (comment != NULL)
            m_comment = comment;
    }

public:

    IntUserConfigParam(int default_value, const char* param_name,
                       const char* comment = NULL);
    IntUserConfigParam(int default_value, const char* param_name,
                       GroupUserConfigParam* group,
                       const char* comment = NULL);

    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    irr::core::stringc toString() const;
    void revertToDefaults()      { m_value = m_default_value;        }
    int getDefaultValue()        { return  m_default_value;          }
    operator int() const         { return m_value;                   }
    int& operator++(int dummy)   { m_value++; return m_value;        }
    int& operator=(const int& v) { m_value = v; return m_value;      }
    int& operator=(const IntUserConfigParam& v)
                                 { m_value = (int)v; return m_value; }
};   // IntUserConfigParam

// ============================================================================
class TimeUserConfigParam : public UserConfigParam
{
    StkTime::TimeType m_value;
    StkTime::TimeType m_default_value;

public:

    TimeUserConfigParam(StkTime::TimeType default_value, const char* param_name,
                        const char* comment = NULL);
    TimeUserConfigParam(StkTime::TimeType default_value, const char* param_name,
                        GroupUserConfigParam* group, const char* comment=NULL);

    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    irr::core::stringc toString() const;
    void revertToDefaults()               { m_value = m_default_value;        }
    operator StkTime::TimeType() const       { return m_value;                   }
    StkTime::TimeType& operator=(const StkTime::TimeType& v)
                                          { m_value = v; return m_value;      }
    StkTime::TimeType& operator=(const TimeUserConfigParam& v)
                                          { m_value = (int)v; return m_value; }
};   // TimeUserConfigParam

// ============================================================================
class StringUserConfigParam : public UserConfigParam
{
protected:
    std::string m_value;
    std::string m_default_value;
    StringUserConfigParam(const char* param_name, const char* comment)
    {
        m_param_name = param_name;
        if (comment != NULL)
            m_comment = comment;
    }

public:

    StringUserConfigParam(const char* default_value, const char* param_name,
                          const char* comment);
    StringUserConfigParam(const char* default_value, const char* param_name,
                          GroupUserConfigParam* group,
                          const char* comment = NULL);

    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    void revertToDefaults() { m_value = m_default_value; }

    std::string getDefaultValue() const { return m_default_value; }

    irr::core::stringc toString() const { return m_value.c_str(); }

    operator std::string() const  { return m_value; }
    std::string& operator=(const std::string& v)
                                  { m_value = v; return m_value; }
    std::string& operator=(const StringUserConfigParam& v)
                                  { m_value = (std::string)v; return m_value; }

    const char* c_str() const { return m_value.c_str(); }
};   // StringUserConfigParam

// ============================================================================
class BoolUserConfigParam : public UserConfigParam
{
protected:
    bool m_value;
    bool m_default_value;
    BoolUserConfigParam(const char* param_name, const char* comment)
    {
        m_param_name = param_name;
        if (comment != NULL)
            m_comment = comment;
    }

public:
    BoolUserConfigParam(bool default_value, const char* param_name,
                        const char* comment = NULL);
    BoolUserConfigParam(bool default_value, const char* param_name,
                        GroupUserConfigParam* group,
                        const char* comment = NULL);
    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    irr::core::stringc toString() const;
    void revertToDefaults() { m_value = m_default_value; }

    operator bool() const { return m_value; }
    bool& operator=(const bool& v) { m_value = v; return m_value; }
    bool& operator=(const BoolUserConfigParam& v)
                              { m_value = (bool)v; return m_value; }
};   // BoolUserConfigParam

// ============================================================================
class FloatUserConfigParam : public UserConfigParam
{
protected:
    float m_value;
    float m_default_value;
    FloatUserConfigParam(const char* param_name, const char* comment)
    {
        m_param_name = param_name;
        if (comment != NULL)
            m_comment = comment;
    }

public:
    FloatUserConfigParam(float default_value, const char* param_name,
                         const char* comment = NULL);
    FloatUserConfigParam(float default_value, const char* param_name,
                         GroupUserConfigParam* group,
                         const char* comment = NULL);

    void write(std::stringstream& stream) const;
    void findYourDataInAChildOf(const XMLNode* node);
    void findYourDataInAnAttributeOf(const XMLNode* node);

    irr::core::stringc toString() const;
    void revertToDefaults() { m_value = m_default_value; }

    operator float() const { return m_value; }
    float& operator=(const float& v) { m_value = v; return m_value; }
    float& operator=(const FloatUserConfigParam& v)
                              { m_value = (float)v; return m_value; }
};   // FloatUserConfigParam

// ============================================================================
enum AnimType {ANIMS_NONE         = 0,
               ANIMS_PLAYERS_ONLY = 1,
               ANIMS_ALL          = 2 };

enum GeometryLevel
{
    /** Display everything */
    GEOLEVEL_0    = 0,
    /** a few details are displayed */
    GEOLEVEL_1    = 1,
    /** Lowest level, no details are displayed. */
    GEOLEVEL_2    = 2
};

enum MultitouchControls
{
    MULTITOUCH_CONTROLS_UNDEFINED = 0,
    MULTITOUCH_CONTROLS_STEERING_WHEEL = 1,
    MULTITOUCH_CONTROLS_ACCELEROMETER = 2,
    MULTITOUCH_CONTROLS_GYROSCOPE = 3,
};

/** Using X-macros for setting-possible values is not very pretty, but it's a
 *  no-maintenance case :
 *  when you want to add a new parameter, just add one signle line below and
 *  everything else automagically works (including default value, saving to
 *  file, loading from file)
 */

// ============================================================================
/** \brief Contains all parameters that are stored in the user's config file
 *  \ingroup config
 */
struct UserConfigParams
{
    static int m_default_num_karts;
    static int m_num_laps;
    static int m_ffa_time_limit;
    static bool m_use_ffa_mode;
    static int m_num_goals;
    static int m_soccer_default_team;
    static int m_soccer_time_limit;
    static bool m_soccer_use_time_limit;
    static bool m_random_arena_item;
    static int m_difficulty;
    static int m_game_mode;
    static std::string m_default_kart;
    // ---- Video
    static int m_width;
    static int m_height;

    static bool m_texture_compression;
    static int m_high_definition_textures;
    static bool m_glow;
    static bool m_bloom;
    static bool m_light_shaft;
    static bool m_dynamic_lights;
    static bool m_dof;
    static float m_scale_rtts_factor;
    static int m_max_texture_size;

    // ---- Graphic Quality;
    static int m_particles_effects;
    static bool m_animated_characters;
    static int m_geometry_level;
    static int m_anisotropic;
    static bool m_motionblur;
    static bool m_mlaa;
    static bool m_ssao;
    static bool m_light_scatter;
    static int m_shadows_resolution;
    static bool m_degraded_IBL;

    // ---- Camera
    static int m_reverse_look_threshold;
    static float m_fpscam_direction_speed;
    static float m_fpscam_smooth_direction_max_speed;
    static float m_fpscam_angular_velocity;
    static float m_fpscam_max_angular_velocity;
};

#endif

/*EOF*/
