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
#include "config/user_config.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/irr_driver.hpp"
#include "modes/world.hpp"
#include "tracks/track.hpp"
#include "tracks/track_object.hpp"
#include "tracks/track_object_manager.hpp"
#include "scriptengine/aswrappedcall.hpp"

#include <angelscript.h>
#include <assert.h>
#include <ISceneManager.h>
#include <IBillboardTextSceneNode.h>

/** \cond DOXYGEN_IGNORE */
namespace Scripting
{
    /** \endcond */
    namespace Challenges
    {
        /** \addtogroup Scripting
        * @{
        */
        /** \addtogroup Scripting_Challenges Challenges
        * @{
        */

        // --------------------------------------------------------------------
        /** Get total number of challenges */
        int getChallengeCount()
        {
            return (int)::Track::getCurrentTrack()->getChallengeList().size();
        }   // getChallengeCount

        // --------------------------------------------------------------------
        /** Get number of challenges that were completed at any difficulty */
        int getCompletedChallengesCount()
        {
            return getChallengeCount();
        }   // getCompletedChallengesCount

        // --------------------------------------------------------------------
        int getChallengeRequiredPoints(std::string* challenge_name)
        {
			return 0;
        }   // getChallengeRequiredPoints

        // --------------------------------------------------------------------
        bool isChallengeUnlocked(std::string* challenge_name)
        {
            return true;
        }   // isChallengeUnlocked

        // --------------------------------------------------------------------
        /** @}*/
        /** @}*/
        
        void registerScriptFunctions(asIScriptEngine *engine)
        {
            engine->SetDefaultNamespace("Challenges");
            
            bool mp = strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY");
            asDWORD call_conv = mp ? asCALL_GENERIC : asCALL_CDECL;
            int r; // of type asERetCodes
            
            r = engine->RegisterGlobalFunction("int getCompletedChallengesCount()", 
                                               mp ? WRAP_FN(getCompletedChallengesCount) 
                                                  : asFUNCTION(getCompletedChallengesCount),
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("int getChallengeCount()", 
                                               mp ? WRAP_FN(getChallengeCount) 
                                                  : asFUNCTION(getChallengeCount),
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("bool isChallengeUnlocked(string &in)",
                                               mp ? WRAP_FN(isChallengeUnlocked) 
                                                  : asFUNCTION(isChallengeUnlocked),
                                               call_conv); assert(r >= 0);
                                               
            r = engine->RegisterGlobalFunction("int getChallengeRequiredPoints(string &in)",
                                               mp ? WRAP_FN(getChallengeRequiredPoints) 
                                                  : asFUNCTION(getChallengeRequiredPoints),
                                               call_conv); assert(r >= 0);
        } // registerScriptFunctions

    }   // namespace Challenges

    /** \cond DOXYGEN_IGNORE */
}   // namespace Scripting
/** \endcond */

