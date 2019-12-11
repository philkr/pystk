//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2014-2015  SuperTuxKart Team
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

#include "script_track.hpp"

#include "animations/three_d_animation.hpp"
#include "input/input.hpp"
#include "modes/world.hpp"
#include "scriptengine/aswrappedcall.hpp"
#include "tracks/track.hpp"
#include "tracks/track_object.hpp"
#include "tracks/track_object_manager.hpp"
#include "utils/string_utils.hpp"

#include <angelscript.h>
#include "scriptarray.hpp"

#include <assert.h>
#include <iostream> //debug

/** \cond DOXYGEN_IGNORE */
namespace Scripting
{
/** \endcond */

    namespace GUI
    {
        /** \addtogroup Scripting
        * @{
        */
        /** \addtogroup GUI
        * @{
        */

        /** Get the key bound to a player action (enum GUI::PlayerAction)*/
        std::string getKeyBinding(int Enum_value)
        {
            return "";
        }

        /** Show the specified message in a popup */
        void displayModalMessage(std::string* input)
        {
        }

        void clearOverlayMessages()
        {
        }

        /** Display text in the center of the screen for a few seconds */
        void displayOverlayMessage(std::string* input)
        {
        }

        /** Get translated version of string */
        std::string translate(std::string* input)
        {
            return *input;
        }

        /** Translate string and insert values. e.g. GUI::translate("Hello %s !", "John") */
        std::string translate(std::string* formatString, std::string* arg1)
        {
            return StringUtils::insertValues(*formatString, *arg1);
        }

        /** Translate string and insert values. e.g. GUI::translate("Hello %s !", "John") */
        std::string translate(std::string* formatString, std::string* arg1, std::string* arg2)
        {
            return StringUtils::insertValues(*formatString, *arg1, *arg2);
        }

        /** Translate string and insert values. e.g. GUI::translate("Hello %s !", "John") */
        std::string translate(std::string* formatString, std::string* arg1, std::string* arg2,
            std::string* arg3)
        {
            
            return StringUtils::insertValues(*formatString, *arg1, *arg2, *arg3);
        }
        /** @}*/
        /** @}*/

        // UNDOCUMENTED PROXIES : Use proxies to have different signatures, then redirect to the
        // documented function whose name is exposed in angelscript (these proxies exist so that
        // angelscript can properly resolve overloads, but doxygen can still generate the right docs
        /** \cond DOXYGEN_IGNORE */
        std::string proxy_translate(std::string* formatString)
        {
            return translate(formatString);
        }

        std::string proxy_translateAndInsertValues1(std::string* formatString, std::string* arg1)
        {
            return translate(formatString, arg1);
        }

        std::string proxy_translateAndInsertValues2(std::string* formatString, std::string* arg1, std::string* arg2)
        {
            return translate(formatString, arg1, arg2);
        }

        std::string proxy_translateAndInsertValues3(std::string* formatString, std::string* arg1, std::string* arg2,
            std::string* arg3)
        {
            return translate(formatString, arg1, arg2, arg3);
        }
        /** \endcond */
        
        void registerScriptFunctions(asIScriptEngine *engine)
        {
            engine->SetDefaultNamespace("GUI");
            
            bool mp = strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY");
            asDWORD call_conv = mp ? asCALL_GENERIC : asCALL_CDECL;
            int r; // of type asERetCodes
            
            r = engine->RegisterGlobalFunction("void displayModalMessage(const string &in)", 
                                               mp ? WRAP_FN(displayModalMessage) : asFUNCTION(displayModalMessage), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("void displayOverlayMessage(const string &in)", 
                                               mp ? WRAP_FN(displayOverlayMessage) : asFUNCTION(displayOverlayMessage), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("void clearOverlayMessages()", 
                                               mp ? WRAP_FN(clearOverlayMessages) : asFUNCTION(clearOverlayMessages), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("string getKeyBinding(int input)", 
                                               mp ? WRAP_FN(getKeyBinding) : asFUNCTION(getKeyBinding), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("string translate(const string &in)", 
                                               mp ? WRAP_FN(proxy_translate) : asFUNCTION(proxy_translate), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("string translate(const string &in, const string &in)", 
                                               mp ? WRAP_FN(proxy_translateAndInsertValues1) 
                                                  : asFUNCTION(proxy_translateAndInsertValues1), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("string translate(const string &in, const string &in, const string &in)", 
                                               mp ? WRAP_FN(proxy_translateAndInsertValues2) 
                                                  : asFUNCTION(proxy_translateAndInsertValues2), 
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("string translate(const string &in, const string &in, const string &in, const string &in)", 
                                               mp ? WRAP_FN(proxy_translateAndInsertValues3) 
                                                  : asFUNCTION(proxy_translateAndInsertValues3), 
                                               call_conv); assert(r >= 0);

        }

        void registerScriptEnums(asIScriptEngine *engine)
        {
            // TODO: document enum in doxygen-generated scripting docs
            engine->SetDefaultNamespace("GUI");
            engine->RegisterEnum("PlayerAction");
            engine->RegisterEnumValue("PlayerAction", "STEER_LEFT", PA_STEER_LEFT);
            engine->RegisterEnumValue("PlayerAction", "STEER_RIGHT", PA_STEER_RIGHT);
            engine->RegisterEnumValue("PlayerAction", "ACCEL", PA_ACCEL);
            engine->RegisterEnumValue("PlayerAction", "BRAKE", PA_BRAKE);
            engine->RegisterEnumValue("PlayerAction", "NITRO", PA_NITRO);
            engine->RegisterEnumValue("PlayerAction", "DRIFT", PA_DRIFT);
            engine->RegisterEnumValue("PlayerAction", "RESCUE", PA_RESCUE);
            engine->RegisterEnumValue("PlayerAction", "FIRE", PA_FIRE);
            engine->RegisterEnumValue("PlayerAction", "LOOK_BACK", PA_LOOK_BACK);
        }
    }

/** \cond DOXYGEN_IGNORE */
}
/** \endcond */
