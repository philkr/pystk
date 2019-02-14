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

class PlayerProfile;
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

#ifndef PARAM_PREFIX
#define PARAM_PREFIX extern
#endif

#ifndef PARAM_DEFAULT
#define PARAM_DEFAULT(X)
#endif

// ============================================================================
/** \brief Contains all parameters that are stored in the user's config file
 *  \ingroup config
 */
namespace UserConfigParams
{

    // ---- Race setup
    PARAM_PREFIX GroupUserConfigParam        m_race_setup_group
        PARAM_DEFAULT( GroupUserConfigParam("RaceSetup",
                                            "Race Setup Settings") );

    PARAM_PREFIX IntUserConfigParam          m_default_num_karts
            PARAM_DEFAULT(  IntUserConfigParam(4, "numkarts",
                            &m_race_setup_group,
                            "Default number of karts. -1 means use all") );
    PARAM_PREFIX IntUserConfigParam          m_num_laps
            PARAM_DEFAULT(  IntUserConfigParam(4, "numlaps",
            &m_race_setup_group, "Default number of laps.") );
    PARAM_PREFIX IntUserConfigParam          m_ffa_time_limit
        PARAM_DEFAULT(IntUserConfigParam(3, "ffa-time-limit",
            &m_race_setup_group, "Time limit in ffa mode."));
    PARAM_PREFIX BoolUserConfigParam         m_use_ffa_mode
        PARAM_DEFAULT(BoolUserConfigParam(false, "use-ffa-mode",
            &m_race_setup_group, "Use ffa mode instead of 3 strikes battle."));
    PARAM_PREFIX IntUserConfigParam          m_num_goals
            PARAM_DEFAULT(  IntUserConfigParam(3, "numgoals",
            &m_race_setup_group, "Default number of goals in soccer mode.") );
    PARAM_PREFIX IntUserConfigParam          m_soccer_default_team
            PARAM_DEFAULT(  IntUserConfigParam(0, "soccer-default-team",
            &m_race_setup_group, "Default team in soccer mode for single player.") );
    PARAM_PREFIX IntUserConfigParam          m_soccer_time_limit
            PARAM_DEFAULT(  IntUserConfigParam(3, "soccer-time-limit",
            &m_race_setup_group, "Time limit in soccer mode.") );
    PARAM_PREFIX BoolUserConfigParam         m_soccer_use_time_limit
            PARAM_DEFAULT(  BoolUserConfigParam(false, "soccer-use-time-limit",
            &m_race_setup_group, "Enable time limit in soccer mode.") );
    PARAM_PREFIX BoolUserConfigParam         m_random_arena_item
            PARAM_DEFAULT(  BoolUserConfigParam(false, "random-arena-item",
            &m_race_setup_group, "Enable random location of items in an arena.") );
    PARAM_PREFIX IntUserConfigParam          m_difficulty
            PARAM_DEFAULT(  IntUserConfigParam(0, "difficulty",
                            &m_race_setup_group,
                        "Default race difficulty. 0=easy, 1=medium, 2=hard") );
    PARAM_PREFIX IntUserConfigParam          m_game_mode
            PARAM_DEFAULT(  IntUserConfigParam(0, "game_mode",
                            &m_race_setup_group,
                            "Game mode. 0=standard, 1=time trial, 2=follow "
                            "the leader, 3=3 strikes") );
    PARAM_PREFIX StringUserConfigParam m_default_kart
            PARAM_DEFAULT( StringUserConfigParam("tux", "kart",
                           "Kart to select by default (the last used kart)") );
    PARAM_PREFIX StringUserConfigParam m_last_used_kart_group
            PARAM_DEFAULT( StringUserConfigParam("all", "last_kart_group",
                                                 "Last selected kart group") );

    // ---- Video
    PARAM_PREFIX GroupUserConfigParam        m_video_group
        PARAM_DEFAULT( GroupUserConfigParam("Video", "Video Settings") );

    PARAM_PREFIX IntUserConfigParam         m_width
            PARAM_DEFAULT(  IntUserConfigParam(1024, "width", &m_video_group,
                                            "Screen/window width in pixels") );
    PARAM_PREFIX IntUserConfigParam         m_height
            PARAM_DEFAULT(  IntUserConfigParam(768, "height", &m_video_group,
                                           "Screen/window height in pixels") );
    PARAM_PREFIX BoolUserConfigParam        m_fullscreen
            PARAM_DEFAULT(  BoolUserConfigParam(false, "fullscreen",
                                                &m_video_group) );
    PARAM_PREFIX IntUserConfigParam         m_prev_width
            PARAM_DEFAULT(  IntUserConfigParam(1024, "prev_width",
                            &m_video_group, "Previous screen/window width") );
    PARAM_PREFIX IntUserConfigParam         m_prev_height
            PARAM_DEFAULT(  IntUserConfigParam(768, "prev_height",
                            &m_video_group,"Previous screen/window height") );
    PARAM_PREFIX BoolUserConfigParam        m_prev_fullscreen
            PARAM_DEFAULT(  BoolUserConfigParam(false, "prev_fullscreen",
                            &m_video_group) );


    PARAM_PREFIX BoolUserConfigParam        m_remember_window_location
            PARAM_DEFAULT(  BoolUserConfigParam(false, "remember_window_location",
                            &m_video_group) );
    PARAM_PREFIX IntUserConfigParam         m_window_x
            PARAM_DEFAULT(  IntUserConfigParam(-1, "window_x",
                            &m_video_group,"If remember_window_location is true") );
    PARAM_PREFIX IntUserConfigParam         m_window_y
            PARAM_DEFAULT(  IntUserConfigParam(-1, "window_y",
                            &m_video_group,"If remember_window_location is true") );

    PARAM_PREFIX BoolUserConfigParam        m_display_fps
            PARAM_DEFAULT(  BoolUserConfigParam(false, "show_fps",
                            &m_video_group, "Display frame per seconds") );
    PARAM_PREFIX IntUserConfigParam         m_max_fps
            PARAM_DEFAULT(  IntUserConfigParam(120, "max_fps",
                       &m_video_group, "Maximum fps, should be at least 60") );
    PARAM_PREFIX BoolUserConfigParam        split_screen_horizontally
        PARAM_DEFAULT(BoolUserConfigParam(true, "split_screen_horizontally",
            &m_video_group, "When playing a non-square amount of players (e.g. 2),"
            " should it split horizontally (top/bottom)"));
    PARAM_PREFIX BoolUserConfigParam        m_texture_compression
        PARAM_DEFAULT(BoolUserConfigParam(true, "enable_texture_compression",
        &m_video_group, "Enable Texture Compression"));
    /** This is a bit flag: bit 0: enabled (1) or disabled(0).
     *  Bit 1: setting done by default(0), or by user choice (2). This allows
     *  to e.g. disable h.d. textures on hd3000 as default, but still allow the
     *  user to enable it. */
    PARAM_PREFIX IntUserConfigParam        m_high_definition_textures
        PARAM_DEFAULT(IntUserConfigParam(1, "enable_high_definition_textures",
        &m_video_group, "Enable high definition textures. Bit flag: "
                        "bit 0 = enabled/disabled; bit 1 = set by user/set as default"));
    PARAM_PREFIX BoolUserConfigParam        m_glow
        PARAM_DEFAULT(BoolUserConfigParam(false, "enable_glow",
        &m_video_group, "Enable Glow"));
    PARAM_PREFIX BoolUserConfigParam        m_bloom
        PARAM_DEFAULT(BoolUserConfigParam(false, "enable_bloom",
        &m_video_group, "Enable Bloom"));
    PARAM_PREFIX BoolUserConfigParam        m_light_shaft
        PARAM_DEFAULT(BoolUserConfigParam(false, "enable_light_shaft",
        &m_video_group, "Enable Light Shafts"));
    PARAM_PREFIX BoolUserConfigParam        m_dynamic_lights
        PARAM_DEFAULT(BoolUserConfigParam(true, "enable_dynamic_lights",
        &m_video_group, "Enable Dynamic Lights"));
    PARAM_PREFIX BoolUserConfigParam        m_dof
        PARAM_DEFAULT(BoolUserConfigParam(false, "enable_dof",
        &m_video_group, "Enable Depth of Field"));
    PARAM_PREFIX BoolUserConfigParam        m_old_driver_popup
        PARAM_DEFAULT(BoolUserConfigParam(true, "old_driver_popup",
        &m_video_group, "Determines if popup message about too old drivers should be displayed."));
    PARAM_PREFIX FloatUserConfigParam       m_scale_rtts_factor
        PARAM_DEFAULT(FloatUserConfigParam(1.0f, "scale_rtts_factor",
        &m_video_group, "Allows one to increase performance by setting lower RTTs "
                        "resolution. Value should be smaller or equal to 1.0"));
    PARAM_PREFIX IntUserConfigParam         m_max_texture_size
        PARAM_DEFAULT(IntUserConfigParam(512, "max_texture_size",
        &m_video_group, "Max texture size when high definition textures are "
                        "disabled"));

    PARAM_PREFIX BoolUserConfigParam        m_hq_mipmap
        PARAM_DEFAULT(BoolUserConfigParam(false, "hq_mipmap",
        &m_video_group, "Generate mipmap for textures using "
                        "high quality method with SSE"));

    PARAM_PREFIX int  m_verbosity         PARAM_DEFAULT( 0 );
    PARAM_PREFIX bool m_race_now          PARAM_DEFAULT( false );
    // ---- Gamemode setup
    PARAM_PREFIX UIntToUIntUserConfigParam m_num_karts_per_gamemode
        PARAM_DEFAULT(UIntToUIntUserConfigParam("num-karts-per-gamemode",
            "The Number of karts per gamemode.",
            {{ "gamemode-list", "gamemode", "num-karts" }},
            {
                { 0u, 4u },
                { 1002u, 5u },
                { 1100u, 4u },
                { 1101u, 4u },
                { 2000u, 4u },
                { 2001u, 4u }
            }
        ));

    // ---- Graphic Quality
    PARAM_PREFIX GroupUserConfigParam        m_graphics_quality
            PARAM_DEFAULT( GroupUserConfigParam("GFX",
                                                "Graphics Quality Settings") );

    PARAM_PREFIX IntUserConfigParam        m_particles_effects
            PARAM_DEFAULT(  IntUserConfigParam(2, "particles-effecs",
                            &m_graphics_quality, "Particles effects: 0 disabled, 1 only important, 2 enabled") );

    // This saves the actual user preference.
    PARAM_PREFIX IntUserConfigParam        m_xmas_mode
            PARAM_DEFAULT(  IntUserConfigParam(0, "christmas-mode",
                            &m_graphics_quality, "Christmas hats: 0 use current date, 1 always on, 2 always off") );

    // This saves the actual user preference.
    PARAM_PREFIX IntUserConfigParam        m_easter_ear_mode
        PARAM_DEFAULT(IntUserConfigParam(0, "easter-ear-mode",
        &m_graphics_quality, "Easter Bunny Ears: 0 use current date, 1 always on, 2 always off"));

    PARAM_PREFIX BoolUserConfigParam       m_animated_characters
            PARAM_DEFAULT(  BoolUserConfigParam(true,
                            "animated-characters", &m_graphics_quality,
                "Whether to display animated characters") );

    PARAM_PREFIX IntUserConfigParam        m_geometry_level
            PARAM_DEFAULT(  IntUserConfigParam(GEOLEVEL_0,
                            "geometry_level", &m_graphics_quality,
                "Geometry quality 0=everything is displayed; "
                "1=a few details are displayed; 2=lowest level, no details") );

    PARAM_PREFIX IntUserConfigParam         m_anisotropic
            PARAM_DEFAULT( IntUserConfigParam(4, "anisotropic",
                           &m_graphics_quality,
                           "Quality of anisotropic filtering (usual values include 2-4-8-16; 0 to disable)") );

    PARAM_PREFIX BoolUserConfigParam         m_vsync
            PARAM_DEFAULT( BoolUserConfigParam(false, "vsync",
                           &m_graphics_quality,
                           "Whether vertical sync is enabled") );
    PARAM_PREFIX BoolUserConfigParam         m_motionblur
            PARAM_DEFAULT( BoolUserConfigParam(false,
                           "motionblur_enabled", &m_graphics_quality,
                           "Whether motion blur should be enabled") );
    PARAM_PREFIX BoolUserConfigParam         m_mlaa
            PARAM_DEFAULT( BoolUserConfigParam(false,
                           "mlaa", &m_graphics_quality,
                           "Whether MLAA anti-aliasing should be enabled") );
    PARAM_PREFIX BoolUserConfigParam          m_ssao
            PARAM_DEFAULT(BoolUserConfigParam(false,
                           "ssao", &m_graphics_quality,
                           "Enable Screen Space Ambient Occlusion") );
    PARAM_PREFIX BoolUserConfigParam         m_light_scatter
            PARAM_DEFAULT(BoolUserConfigParam(true,
                           "light_scatter", &m_graphics_quality,
                           "Enable light scattering shaders") );
    PARAM_PREFIX IntUserConfigParam          m_shadows_resolution
            PARAM_DEFAULT( IntUserConfigParam(0,
                           "shadows_resolution", &m_graphics_quality,
                           "Shadow resolution (0 = disabled") );
    PARAM_PREFIX BoolUserConfigParam          m_degraded_IBL
        PARAM_DEFAULT(BoolUserConfigParam(true,
        "Degraded_IBL", &m_graphics_quality,
        "Disable specular IBL"));

    // ---- Misc
    // TODO : is this used with new code? does it still work?
    PARAM_PREFIX BoolUserConfigParam        m_crashed
            PARAM_DEFAULT(  BoolUserConfigParam(false, "crashed") );

    // ---- Camera
    PARAM_PREFIX GroupUserConfigParam        m_camera
            PARAM_DEFAULT( GroupUserConfigParam("camera",
                                                "(Debug) camera settings.") );

    PARAM_PREFIX IntUserConfigParam         m_reverse_look_threshold
            PARAM_DEFAULT(  IntUserConfigParam(0, "reverse_look_threshold",
            &m_camera,
            "If the kart is driving backwards faster than this value,\n"
            "switch automatically to reverse camera (set to 0 to disable).") );

    PARAM_PREFIX FloatUserConfigParam       m_fpscam_direction_speed
            PARAM_DEFAULT(  FloatUserConfigParam(0.003f, "fpscam_rotation_speed",
            &m_camera,
            "How fast the first person camera's direction speed changes when\n"
            "moving the mouse (means acceleration).") );

    PARAM_PREFIX FloatUserConfigParam       m_fpscam_smooth_direction_max_speed
            PARAM_DEFAULT(  FloatUserConfigParam(0.04f, "fpscam_smooth_rotation_max_speed",
            &m_camera,
            "How fast the first person camera's direction can change.") );

    PARAM_PREFIX FloatUserConfigParam       m_fpscam_angular_velocity
            PARAM_DEFAULT(  FloatUserConfigParam(0.02f, "fpscam_angular_velocity",
            &m_camera,
            "How fast the first person camera's rotation speed changes.") );

    PARAM_PREFIX FloatUserConfigParam       m_fpscam_max_angular_velocity
            PARAM_DEFAULT(  FloatUserConfigParam(1.0f, "fpscam_max_angular_velocity",
            &m_camera,
            "How fast the first person camera can rotate.") );

    PARAM_PREFIX StringUserConfigParam      m_item_style
            PARAM_DEFAULT(  StringUserConfigParam("items", "item_style",
                            "Name of the .items file to use.") );

    PARAM_PREFIX StringUserConfigParam      m_last_track
            PARAM_DEFAULT(  StringUserConfigParam("olivermath", "last_track",
                            "Name of the last track used.") );
    PARAM_PREFIX StringUserConfigParam m_last_used_track_group
            PARAM_DEFAULT( StringUserConfigParam("all", "last_track_group",
                           "Last selected track group") );

    PARAM_PREFIX StringUserConfigParam      m_skin_file
            PARAM_DEFAULT(  StringUserConfigParam("Peach.stkskin", "skin_file",
                                                  "Name of the skin to use") );

    PARAM_PREFIX IntUserConfigParam        m_minimap_display
        PARAM_DEFAULT(IntUserConfigParam(0, "minimap_display",
                      "Minimap: 0 bottom-left, 1 middle-right, 2 hidden"));

    // ---- Handicap
    PARAM_PREFIX GroupUserConfigParam       m_handicap
            PARAM_DEFAULT( GroupUserConfigParam("Handicap",
                                          "Everything related to handicaps.") );

    PARAM_PREFIX BoolUserConfigParam        m_per_player_difficulty
            PARAM_DEFAULT(  BoolUserConfigParam(false, "per_player_difficulty",
                            &m_handicap,
                            "If handicapped users can be selected") );

    PARAM_PREFIX StringUserConfigParam      m_commandline
            PARAM_DEFAULT( StringUserConfigParam("", "commandline",
                             "Allows one to set commandline args in config file") );

    // TODO? implement blacklist for new irrlicht device and GUI
    PARAM_PREFIX std::vector<std::string>   m_blacklist_res;

    /** Some constants to bitmask to enable various messages to be printed. */
    enum { LOG_MEMORY  = 0x0001,
           LOG_GUI     = 0x0002,
           LOG_ADDONS  = 0x0004,
           LOG_MISC    = 0x0008,
           LOG_FLYABLE = 0x0010,
           LOG_ALL     = 0xffff };

    /** Returns true if the user want additional messages for memory usage. */
    bool   logMemory();
    /** Returns true if the user want additional messages related to GUI. */
    bool   logGUI   ();
    /** Returns true if the user want additional messages related to addons. */
    bool   logAddons();
    /** Returns true if the user want additional debug info for flyables */
    bool   logFlyable();
    /** Returns true if the user want additional messages for general items. */
    bool   logMisc  ();


}
#undef PARAM_PREFIX
#undef PARAM_SUFFIX

// ============================================================================
/**
  * \brief Class for managing general STK user configuration data.
  * \ingroup config
  */
class UserConfig : public NoCopy
{
private:

    /** Filename of the user config file. */
    std::string        m_filename;
    irr::core::stringw m_warning;

    static const int m_current_config_version;

public:
          /** Create the user config object; does not actually load it,
           *  UserConfig::loadConfig needs to be called. */
          UserConfig();
         ~UserConfig();

    bool  loadConfig();
    void  saveConfig();

    const irr::core::stringw& getWarning()        { return m_warning;  }
    void  resetWarning()                          { m_warning="";      }
    void  setWarning(irr::core::stringw& warning) { m_warning=warning; }

};   // UserConfig


extern UserConfig *user_config;

#endif

/*EOF*/
