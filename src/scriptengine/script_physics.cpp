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

#include <assert.h>
#include <angelscript.h>
#include "script_physics.hpp"
#include "graphics/explosion.hpp"
#include "graphics/hit_effect.hpp"
#include "items/projectile_manager.hpp"

namespace Scripting
{
    
    namespace Physics
    {
        //Creates an explosion animation at specified Vec3 location
        // TODO: does this even belong in Physics?
        void createExplosion(asIScriptGeneric *gen)
        {
            //TODO: allow different types? sand etc
            Vec3 *explosion_loc = (Vec3*)gen->GetArgAddress(0);
            HitEffect *he = new Explosion(*explosion_loc, "explosion_bomb.xml");
            projectile_manager->addHitEffect(he);
        }
        void registerScriptFunctions(asIScriptEngine *engine)
        {
            engine->SetDefaultNamespace("Physics");
            
            int r;
            r = engine->RegisterGlobalFunction("string createExplosion(Vec3 &in)", 
                                               asFUNCTION(createExplosion), 
                                               asCALL_GENERIC); assert(r >= 0);
        }
    }
}
