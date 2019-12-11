//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2009-2015 Joerg Henrichs
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

#include "tracks/track_object_manager.hpp"

#include "animations/ipo.hpp"
#include "animations/three_d_animation.hpp"
#include "config/stk_config.hpp"
#include "graphics/lod_node.hpp"
#include "graphics/material_manager.hpp"
#include "io/xml_node.hpp"
#include "physics/physical_object.hpp"
#include "tracks/track_object.hpp"
#include "utils/log.hpp"

#include <IMeshSceneNode.h>
#include <ISceneManager.h>

TrackObjectManager::TrackObjectManager()
{
}   // TrackObjectManager

// ----------------------------------------------------------------------------
TrackObjectManager::~TrackObjectManager()
{
}   // ~TrackObjectManager

// ----------------------------------------------------------------------------
/** Adds an object to the track object manager. The type to add is specified
 *  in the xml_node.
 */
void TrackObjectManager::add(const XMLNode &xml_node, scene::ISceneNode* parent,
                             ModelDefinitionLoader& model_def_loader,
                             TrackObject* parent_library)
{
    try
    {
        TrackObject *obj = new TrackObject(xml_node, parent, model_def_loader, parent_library);
        m_all_objects.push_back(obj);
        if(obj->isDriveable())
            m_driveable_objects.push_back(obj);
    }
    catch (std::exception& e)
    {
        Log::warn("TrackObjectManager", "Could not load track object. Reason : %s",
                  e.what());
    }
}   // add

// ----------------------------------------------------------------------------
/** Initialises all track objects.
 */
void TrackObjectManager::init()
{
    int moveable_objects = 0;
    bool warned = false;
    for (unsigned i = 0; i < m_all_objects.m_contents_vector.size(); i++)
    {
        TrackObject* curr = m_all_objects.m_contents_vector[i];
        curr->onWorldReady();

        if (moveable_objects > stk_config->m_max_moveable_objects)
        {
            if (!warned)
            {
                Log::warn("TrackObjectManager",
                    "Too many moveable objects (>%d) in networking.",
                    stk_config->m_max_moveable_objects);
                warned = true;
            }
            curr->setInitiallyVisible(false);
            curr->setEnabled(false);
            continue;
        }

        // onWorldReady will hide some track objects using scripting
    }
}   // init

// ----------------------------------------------------------------------------
/** Initialises all track objects.
 */
void TrackObjectManager::reset()
{
    for (TrackObject* curr : m_all_objects)
    {
        curr->reset();
        curr->resetEnabled();
    }
}   // reset

// ----------------------------------------------------------------------------
/** returns a reference to the track object
 *  with a particular ID
 *  \param name Name or ID of track object
 */
TrackObject* TrackObjectManager::getTrackObject(const std::string& libraryInstance,
    const std::string& name)
{
    for (TrackObject* curr : m_all_objects)
    {
        //if (curr->getParentLibrary() != NULL)
        //    Log::info("TrackObjectManager", "Found %s::%s", curr->getParentLibrary()->getID().c_str(), curr->getID().c_str());
        //else
        //    Log::info("TrackObjectManager", "Found ::%s", curr->getID().c_str());

        if (curr->getParentLibrary() == NULL)
        {
            if (libraryInstance.size() > 0)
                continue;
        }
        else
        {
            if (libraryInstance != curr->getParentLibrary()->getID())
                continue;
        }

        if (curr->getID() == name)
        {
            return curr;
        }
    }
    //object not found
    Log::warn("TrackObjectManager", "Object not found : %s::%s", libraryInstance.c_str(), name.c_str());
    return NULL;
}
/** Handles an explosion, i.e. it makes sure that all physical objects are
 *  affected accordingly.
 *  \param pos  Position of the explosion.
 *  \param obj  If the hit was a physical object, this object will be affected
 *              more. Otherwise this is NULL.
 *  \param secondary_hits True if items that are not directly hit should
 *         also be affected.
 */

void TrackObjectManager::handleExplosion(const Vec3 &pos, const PhysicalObject *mp,
                                         bool secondary_hits)
{
    TrackObject* curr;
    for_in (curr, m_all_objects)
    {
        if(secondary_hits || mp == curr->getPhysicalObject())
            curr->handleExplosion(pos, mp == curr->getPhysicalObject());
    }
}   // handleExplosion

// ----------------------------------------------------------------------------
/** Updates all track objects.
 *  \param dt Time step size.
 */
void TrackObjectManager::updateGraphics(float dt)
{
    TrackObject* curr;
    for_in(curr, m_all_objects)
    {
        curr->updateGraphics(dt);
    }
}   // updateGraphics

// ----------------------------------------------------------------------------
/** Updates all track objects.
 *  \param dt Time step size.
 */
void TrackObjectManager::update(float dt)
{
    TrackObject* curr;
    for_in (curr, m_all_objects)
    {
        curr->update(dt);
    }
}   // update

// ----------------------------------------------------------------------------
/** Does a raycast against all driveable objects. This way part of the track
 *  can be a physical object, and can e.g. be animated. A separate list of all
 *  driveable objects is maintained (in one case there were over 2000 bodies,
 *  but only one is driveable). The result of the raycast against the track
 *  mesh are the input parameter. It is then tested if the raycast against 
 *  a track object gives a 'closer' result. If so, the parameters hit_point,
 *  normal, and material will be updated.
 *  \param from/to The from and to position for the raycast.
 *  \param xyz The position in world where the ray hit.
 *  \param material The material of the mesh that was hit.
 *  \param normal The intrapolated normal at that position.
 *  \param interpolate_normal If true, the returned normal is the interpolated
 *         based on the three normals of the triangle and the location of the
 *         hit point (which is more compute intensive, but results in much
 *         smoother results).
 *  \return True if a triangle was hit, false otherwise (and no output
 *          variable will be set.
 
 */
bool TrackObjectManager::castRay(const btVector3 &from,
                                 const btVector3 &to, btVector3 *hit_point,
                                 const Material **material,
                                 btVector3 *normal,
                                 bool interpolate_normal) const
{
    bool result = false;
    float distance = 9999.9f;
    // If there was a hit already, compute the current distance
    if(*material)
    {
        distance = hit_point->distance(from);
    }
    for (const TrackObject* curr : m_driveable_objects)
    {
        if (!curr->isEnabled())
        {
            // For example jumping pad in cocoa temple
            continue;
        }
        btVector3 new_hit_point;
        const Material *new_material;
        btVector3 new_normal;
        if(curr->castRay(from, to, &new_hit_point, &new_material, &new_normal,
                      interpolate_normal))
        {
            float new_distance = new_hit_point.distance(from);
            // If the new hit is closer than the current hit, save
            // the data.
            if (new_distance < distance)
            {
                *material  = new_material;
                *hit_point = new_hit_point;
                *normal    = new_normal;
                distance   = new_distance;
                result = true;
            }   // if new_distance < distance
        }   // if hit
    }   // for all track objects.
    return result;
}   // castRay

// ----------------------------------------------------------------------------
void TrackObjectManager::insertObject(TrackObject* object)
{
    m_all_objects.push_back(object);
}

// ----------------------------------------------------------------------------
/** Removes the object from the scene graph, bullet, and the list of
 *  track objects, and then frees the object.
 *  \param obj The physical object to remove.
 */
void TrackObjectManager::removeObject(TrackObject* obj)
{
    m_all_objects.remove(obj);
    delete obj;
}   // removeObject
