//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013-2015 Lionel Fuentes
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

#include "debug.hpp"

#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "font/bold_face.hpp"
#include "font/digit_face.hpp"
#include "font/font_manager.hpp"
#include "font/regular_face.hpp"
#include "graphics/camera_debug.hpp"
#include "graphics/camera_fps.hpp"
#include "karts/explosion_animation.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/light.hpp"
#include "graphics/shader.hpp"
#include "graphics/sp/sp_base.hpp"
#include "graphics/sp/sp_shader_manager.hpp"
#include "graphics/sp/sp_shader.hpp"
#include "graphics/sp/sp_texture_manager.hpp"
#include "graphics/sp/sp_uniform_assigner.hpp"
#include "items/powerup_manager.hpp"
#include "items/attachment.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/kart_properties.hpp"
#include "karts/controller/controller.hpp"
#include "modes/world.hpp"
#include "physics/irr_debug_drawer.hpp"
#include "physics/physics.hpp"
#include "race/history.hpp"
#include "replay/replay_recorder.hpp"
#include "scriptengine/script_engine.hpp"
#include "tracks/track_manager.hpp"
#include "utils/constants.hpp"
#include "utils/log.hpp"
#include "utils/profiler.hpp"
#include "utils/string_utils.hpp"

#include <IGUIEnvironment.h>
#include <IGUIContextMenu.h>

#include <cmath>

using namespace irr;
using namespace gui;

namespace Debug {

/** This is to let mouse input events go through when the debug menu is
 *  visible, otherwise GUI events would be blocked while in a race...
 */
static bool g_debug_menu_visible = false;

// -----------------------------------------------------------------------------
// Commands for the debug menu
enum DebugMenuCommand
{
    //! graphics commands
    DEBUG_GRAPHICS_RELOAD_SHADERS,
    DEBUG_GRAPHICS_RESET,
    DEBUG_GRAPHICS_SSAO_VIZ,
    DEBUG_GRAPHICS_SHADOW_VIZ,
    DEBUG_GRAPHICS_BOUNDING_BOXES_VIZ,
    DEBUG_GRAPHICS_BULLET_1,
    DEBUG_GRAPHICS_BULLET_2,
    DEBUG_PROFILER,
    DEBUG_PROFILER_WRITE_REPORT,
    DEBUG_FONT_DUMP_GLYPH_PAGE,
    DEBUG_FONT_RELOAD,
    DEBUG_SP_RESET,
    DEBUG_SP_TOGGLE_CULLING,
    DEBUG_SP_WN_VIZ,
    DEBUG_SP_NORMALS_VIZ,
    DEBUG_SP_TANGENTS_VIZ,
    DEBUG_SP_BITANGENTS_VIZ,
    DEBUG_SP_WIREFRAME_VIZ,
    DEBUG_SP_TN_VIZ,
    DEBUG_FPS,
    DEBUG_SAVE_REPLAY,
    DEBUG_SAVE_HISTORY,
    DEBUG_POWERUP_BOWLING,
    DEBUG_POWERUP_BUBBLEGUM,
    DEBUG_POWERUP_CAKE,
    DEBUG_POWERUP_PARACHUTE,
    DEBUG_POWERUP_PLUNGER,
    DEBUG_POWERUP_RUBBERBALL,
    DEBUG_POWERUP_SWATTER,
    DEBUG_POWERUP_SWITCH,
    DEBUG_POWERUP_ZIPPER,
    DEBUG_POWERUP_NITRO,
    DEBUG_ATTACHMENT_PARACHUTE,
    DEBUG_ATTACHMENT_BOMB,
    DEBUG_ATTACHMENT_ANVIL,
    DEBUG_ATTACHMENT_EXPLOSION,
    DEBUG_GUI_TOGGLE,
    DEBUG_GUI_HIDE_KARTS,
    DEBUG_GUI_CAM_FREE,
    DEBUG_GUI_CAM_TOP,
    DEBUG_GUI_CAM_WHEEL,
    DEBUG_GUI_CAM_BEHIND_KART,
    DEBUG_GUI_CAM_SIDE_OF_KART,
    DEBUG_GUI_CAM_NORMAL,
    DEBUG_GUI_CAM_SMOOTH,
    DEBUG_GUI_CAM_ATTACH,
    DEBUG_VIEW_KART_PREVIOUS,
    DEBUG_VIEW_KART_ONE,
    DEBUG_VIEW_KART_TWO,
    DEBUG_VIEW_KART_THREE,
    DEBUG_VIEW_KART_FOUR,
    DEBUG_VIEW_KART_FIVE,
    DEBUG_VIEW_KART_SIX,
    DEBUG_VIEW_KART_SEVEN,
    DEBUG_VIEW_KART_EIGHT,
    DEBUG_VIEW_KART_NEXT,
    DEBUG_HIDE_KARTS,
    DEBUG_THROTTLE_FPS,
    DEBUG_VISUAL_VALUES,
    DEBUG_PRINT_START_POS,
    DEBUG_ADJUST_LIGHTS,
    DEBUG_SCRIPT_CONSOLE,
    DEBUG_RUN_CUTSCENE,
    DEBUG_TEXTURE_CONSOLE,
    DEBUG_RENDER_NW_DEBUG,
    DEBUG_START_RECORDING,
    DEBUG_STOP_RECORDING
};   // DebugMenuCommand

// -----------------------------------------------------------------------------
/** Add powerup selected from debug menu for all player karts */
void addPowerup(PowerupManager::PowerupType powerup)
{
    World* world = World::getWorld();
    if (!world) return;
    for(unsigned int i = 0; i < race_manager->getNumLocalPlayers(); i++)
    {
        AbstractKart* kart = world->getLocalPlayerKart(i);
        kart->setPowerup(powerup, 10000);
    }
}   // addPowerup

// ----------------------------------------------------------------------------
void addAttachment(Attachment::AttachmentType type)
{
    World* world = World::getWorld();
    if (world == NULL) return;
    for (unsigned int i = 0; i < world->getNumKarts(); i++)
    {
        AbstractKart *kart = world->getKart(i);
        if (!kart->getController()->isLocalPlayerController())
            continue;
        if (type == Attachment::ATTACH_ANVIL)
        {
            kart->getAttachment()
                ->set(type, 
                      stk_config->time2Ticks(kart->getKartProperties()
                                                 ->getAnvilDuration()) );
            kart->adjustSpeed(kart->getKartProperties()->getAnvilSpeedFactor());
        }
        else if (type == Attachment::ATTACH_PARACHUTE)
        {
            kart->getAttachment()
                ->set(type, kart->getKartProperties()->getParachuteDuration() );
        }
        else if (type == Attachment::ATTACH_BOMB)
        {
            kart->getAttachment()
                ->set(type, stk_config->time2Ticks(stk_config->m_bomb_time) );
        }
    }

}   // addAttachment

// ----------------------------------------------------------------------------
void changeCameraTarget(u32 num)
{
    World* world = World::getWorld();
    Camera *cam = Camera::getActiveCamera();
    if (world == NULL || cam == NULL) return;

    if (num < (world->getNumKarts() + 1))
    {
        AbstractKart* kart = world->getKart(num - 1);
        if (kart == NULL) return;
        cam->setMode(Camera::CM_NORMAL);
        cam->setKart(kart);
    }

}   // changeCameraTarget

// -----------------------------------------------------------------------------

/** returns the light node with the lowest distance to the player kart (excluding
 * nitro emitters) */
LightNode* findNearestLight()
{

    Camera* camera = Camera::getActiveCamera();
    if (camera == NULL) {
        Log::error("[Debug Menu]", "No camera found.");
        return NULL;
    }

    core::vector3df cam_pos = camera->getCameraSceneNode()->getAbsolutePosition();
    LightNode* nearest = 0;
    float nearest_dist = 1000000.0; // big enough
    for (unsigned int i = 0; i < irr_driver->getLights().size(); i++)
    {
        LightNode* light = irr_driver->getLights()[i];

        // Avoid modifying the nitro emitter or another invisible light
        if (std::string(light->getName()).find("nitro emitter") == 0 || !light->isVisible())
            continue;

        core::vector3df light_pos = light->getAbsolutePosition();
        if ( cam_pos.getDistanceFrom(light_pos) < nearest_dist)
        {
            nearest      = irr_driver->getLights()[i];
            nearest_dist = cam_pos.getDistanceFrom(light_pos);
        }
    }

    return nearest;
}

// ----------------------------------------------------------------------------

bool handleContextMenuAction(s32 cmd_id)
{
    if (cmd_id == -1)
        return false;

    Camera* camera = Camera::getActiveCamera();
    unsigned int kart_num = 0;
    if (camera != NULL && camera->getKart() != NULL)
    {
        kart_num = camera->getKart()->getWorldKartId();
    }

    World *world = World::getWorld();
    Physics *physics = Physics::getInstance();
    SP::SPShader* nv = NULL;
#ifndef SERVER_ONLY
    if (SP::getNormalVisualizer())
    {
        nv = SP::getNormalVisualizer();
    }
#endif

    switch(cmd_id)
    {
    case DEBUG_GRAPHICS_RELOAD_SHADERS:
#ifndef SERVER_ONLY
        Log::info("Debug", "Reloading shaders...");
        SP::SPShaderManager::get()->unloadAll();
        ShaderBase::killShaders();
        ShaderFilesManager::getInstance()->removeAllShaderFiles();
        SP::SPShaderManager::get()->initAll();
#endif
        break;
    case DEBUG_GRAPHICS_RESET:
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);

        irr_driver->resetDebugModes();
        break;
    case DEBUG_GRAPHICS_SSAO_VIZ:
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);

        irr_driver->resetDebugModes();
        irr_driver->toggleSSAOViz();
        break;
    case DEBUG_GRAPHICS_SHADOW_VIZ:
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);

        irr_driver->resetDebugModes();
        irr_driver->toggleShadowViz();
        break;
    case DEBUG_GRAPHICS_BOUNDING_BOXES_VIZ:
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);

        irr_driver->resetDebugModes();
        irr_driver->toggleBoundingBoxesViz();
        break;
    case DEBUG_GRAPHICS_BULLET_1:
        irr_driver->resetDebugModes();

        if (!world) return false;
        physics->setDebugMode(IrrDebugDrawer::DM_KARTS_PHYSICS);
        break;
    case DEBUG_GRAPHICS_BULLET_2:
    {
        irr_driver->resetDebugModes();

        Physics *physics = Physics::getInstance();
        if (!physics) return false;
        physics->setDebugMode(IrrDebugDrawer::DM_NO_KARTS_GRAPHICS);
        break;
    }
    case DEBUG_SP_RESET:
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_culling = true;
#endif
        break;
    case DEBUG_SP_TOGGLE_CULLING:
#ifndef SERVER_ONLY
        SP::sp_culling = !SP::sp_culling;
#endif
        break;
    case DEBUG_SP_WN_VIZ:
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
#endif
        break;
    case DEBUG_SP_NORMALS_VIZ:
    {
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
        int normal = 0;
        if (nv)
        {
            SP::SPUniformAssigner* ua = nv->getUniformAssigner("enable_normals");
            if (ua)
            {
                ua->getValue(nv->getShaderProgram(SP::RP_1ST), normal);
                normal = normal == 0 ? 1 : 0;
                nv->use();
                ua->setValue(normal);
                glUseProgram(0);
            }
        }
#endif
        break;
    }
    case DEBUG_SP_TANGENTS_VIZ:
    {
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
        int tangents = 0;
        if (nv)
        {
            SP::SPUniformAssigner* ua = nv->getUniformAssigner("enable_tangents");
            if (ua)
            {
                ua->getValue(nv->getShaderProgram(SP::RP_1ST), tangents);
                tangents = tangents == 0 ? 1 : 0;
                nv->use();
                ua->setValue(tangents);
                glUseProgram(0);
            }
        }
#endif
        break;
    }
    case DEBUG_SP_BITANGENTS_VIZ:
    {
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
        int bitangents = 0;
        if (nv)
        {
            SP::SPUniformAssigner* ua = nv->getUniformAssigner("enable_bitangents");
            if (ua)
            {
                ua->getValue(nv->getShaderProgram(SP::RP_1ST), bitangents);
                bitangents = bitangents == 0 ? 1 : 0;
                nv->use();
                ua->setValue(bitangents);
                glUseProgram(0);
            }
        }
#endif
        break;
    }
    case DEBUG_SP_WIREFRAME_VIZ:
    {
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
        int wireframe = 0;
        if (nv)
        {
            SP::SPUniformAssigner* ua = nv->getUniformAssigner("enable_wireframe");
            if (ua)
            {
                ua->getValue(nv->getShaderProgram(SP::RP_1ST), wireframe);
                wireframe = wireframe == 0 ? 1 : 0;
                nv->use();
                ua->setValue(wireframe);
                glUseProgram(0);
            }
        }
#endif
        break;
    }
    case DEBUG_SP_TN_VIZ:
    {
        irr_driver->resetDebugModes();
        if (physics)
            physics->setDebugMode(IrrDebugDrawer::DM_NONE);
#ifndef SERVER_ONLY
        SP::sp_debug_view = true;
        int triangle_normals = 0;
        if (nv)
        {
            SP::SPUniformAssigner* ua = nv->getUniformAssigner("enable_triangle_normals");
            if (ua)
            {
                ua->getValue(nv->getShaderProgram(SP::RP_1ST), triangle_normals);
                triangle_normals = triangle_normals == 0 ? 1 : 0;
                nv->use();
                ua->setValue(triangle_normals);
                glUseProgram(0);
            }
        }
#endif
        break;
    }
    case DEBUG_PROFILER:
        profiler.toggleStatus();
        break;
    case DEBUG_PROFILER_WRITE_REPORT:
        profiler.writeToFile();
        break;
    case DEBUG_FONT_DUMP_GLYPH_PAGE:
        font_manager->getFont<BoldFace>()->dumpGlyphPage("bold");
        font_manager->getFont<DigitFace>()->dumpGlyphPage("digit");
        font_manager->getFont<RegularFace>()->dumpGlyphPage("regular");
        break;
    case DEBUG_FONT_RELOAD:
        font_manager->getFont<BoldFace>()->reset();
        font_manager->getFont<DigitFace>()->reset();
        font_manager->getFont<RegularFace>()->reset();
        break;
    case DEBUG_SAVE_REPLAY:
        ReplayRecorder::get()->save();
        break;
    case DEBUG_SAVE_HISTORY:
        history->Save();
        break;
    case DEBUG_POWERUP_BOWLING:
        addPowerup(PowerupManager::POWERUP_BOWLING);
        break;
    case DEBUG_POWERUP_BUBBLEGUM:
        addPowerup(PowerupManager::POWERUP_BUBBLEGUM);
        break;
    case DEBUG_POWERUP_CAKE:
        addPowerup(PowerupManager::POWERUP_CAKE);
        break;
    case DEBUG_POWERUP_PARACHUTE:
        addPowerup(PowerupManager::POWERUP_PARACHUTE);
        break;
    case DEBUG_POWERUP_PLUNGER:
        addPowerup(PowerupManager::POWERUP_PLUNGER);
        break;
    case DEBUG_POWERUP_RUBBERBALL:
        addPowerup(PowerupManager::POWERUP_RUBBERBALL);
        break;
    case DEBUG_POWERUP_SWATTER:
        addPowerup(PowerupManager::POWERUP_SWATTER);
        break;
    case DEBUG_POWERUP_SWITCH:
        addPowerup(PowerupManager::POWERUP_SWITCH);
        break;
    case DEBUG_POWERUP_ZIPPER:
        addPowerup(PowerupManager::POWERUP_ZIPPER);
        break;
    case DEBUG_POWERUP_NITRO:
    {
        if (!world) return false;
        const unsigned int num_local_players =
            race_manager->getNumLocalPlayers();
        for (unsigned int i = 0; i < num_local_players; i++)
        {
            AbstractKart* kart = world->getLocalPlayerKart(i);
            kart->setEnergy(100.0f);
        }
        break;
    }
    case DEBUG_ATTACHMENT_ANVIL:
        addAttachment(Attachment::ATTACH_ANVIL);
        break;
    case DEBUG_ATTACHMENT_BOMB:
        addAttachment(Attachment::ATTACH_BOMB);
        break;
    case DEBUG_ATTACHMENT_PARACHUTE:
        addAttachment(Attachment::ATTACH_PARACHUTE);
        break;
    case DEBUG_ATTACHMENT_EXPLOSION:
        for (unsigned int i = 0; i < race_manager->getNumLocalPlayers(); i++)
        {
            AbstractKart* kart = world->getLocalPlayerKart(i);
            ExplosionAnimation::create(kart, kart->getXYZ(), true);
        }
        break;
    case DEBUG_GUI_TOGGLE:
    {
        if (!world) return false;
        break;
    }
    case DEBUG_GUI_HIDE_KARTS:
        if (!world) return false;
        for (unsigned int n = 0; n<world->getNumKarts(); n++)
        {
            AbstractKart* kart = world->getKart(n);
            if (kart->getController()->isPlayerController())
                kart->getNode()->setVisible(false);
        }
        break;
    case DEBUG_GUI_CAM_TOP:
        CameraDebug::setDebugType(CameraDebug::CM_DEBUG_TOP_OF_KART);
        Camera::changeCamera(0, Camera::CM_TYPE_DEBUG);
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        irr_driver->getDevice()->getCursorControl()->setVisible(true);
        break;
    case DEBUG_GUI_CAM_WHEEL:
        CameraDebug::setDebugType(CameraDebug::CM_DEBUG_GROUND);
        Camera::changeCamera(0, Camera::CM_TYPE_DEBUG);
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        irr_driver->getDevice()->getCursorControl()->setVisible(true);
        break;
    case DEBUG_GUI_CAM_BEHIND_KART:
        CameraDebug::setDebugType(CameraDebug::CM_DEBUG_BEHIND_KART);
        Camera::changeCamera(0, Camera::CM_TYPE_DEBUG);
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        irr_driver->getDevice()->getCursorControl()->setVisible(true);
        break;
    case DEBUG_GUI_CAM_SIDE_OF_KART:
        CameraDebug::setDebugType(CameraDebug::CM_DEBUG_SIDE_OF_KART);
        Camera::changeCamera(0, Camera::CM_TYPE_DEBUG);
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        irr_driver->getDevice()->getCursorControl()->setVisible(true);
        break;
    case DEBUG_GUI_CAM_FREE:
    {
        Camera *camera = Camera::getActiveCamera();
        Camera::changeCamera(camera->getIndex(), Camera::CM_TYPE_FPS);
        irr_driver->getDevice()->getCursorControl()->setVisible(false);
        // Reset camera rotation
        CameraFPS *cam = dynamic_cast<CameraFPS*>(Camera::getActiveCamera());
        if(cam)
        {
            cam->setDirection(vector3df(0, 0, 1));
            cam->setUpVector(vector3df(0, 1, 0));
        }
        break;
    }
    case DEBUG_GUI_CAM_NORMAL:
    {
        Camera *camera = Camera::getActiveCamera();
        Camera::changeCamera(camera->getIndex(), Camera::CM_TYPE_NORMAL);
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        irr_driver->getDevice()->getCursorControl()->setVisible(true);
        break;
    }
    case DEBUG_GUI_CAM_SMOOTH:
    {
        CameraFPS *cam = dynamic_cast<CameraFPS*>(Camera::getActiveCamera());
        if(cam)
        {
            cam->setSmoothMovement(!cam->getSmoothMovement());
        }
        break;
    }
    case DEBUG_GUI_CAM_ATTACH:
    {
        CameraFPS *cam = dynamic_cast<CameraFPS*>(Camera::getActiveCamera());
        if(cam)
        {
            cam->setAttachedFpsCam(!cam->getAttachedFpsCam());
        }
        break;
    }
    case DEBUG_VIEW_KART_PREVIOUS:
    {
        if (kart_num == 0)
        {
            kart_num += World::getWorld()->getNumKarts() - 1;
        }
        else
        {
            kart_num--;
        }
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        break;
    }
    case DEBUG_VIEW_KART_ONE:
        changeCameraTarget(1);
        break;
    case DEBUG_VIEW_KART_TWO:
        changeCameraTarget(2);
        break;
    case DEBUG_VIEW_KART_THREE:
        changeCameraTarget(3);
        break;
    case DEBUG_VIEW_KART_FOUR:
        changeCameraTarget(4);
        break;
    case DEBUG_VIEW_KART_FIVE:
        changeCameraTarget(5);
        break;
    case DEBUG_VIEW_KART_SIX:
        changeCameraTarget(6);
        break;
    case DEBUG_VIEW_KART_SEVEN:
        changeCameraTarget(7);
        break;
    case DEBUG_VIEW_KART_EIGHT:
        changeCameraTarget(8);
        break;
    case DEBUG_VIEW_KART_NEXT:
    {
        if (kart_num == World::getWorld()->getNumKarts() - 1)
        {
            kart_num = 0;
        }
        else
        {
             kart_num++;
        }
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        break;
    }

    case DEBUG_PRINT_START_POS:
        if (!world) return false;
        for (unsigned int i = 0; i<world->getNumKarts(); i++)
        {
            AbstractKart *kart = world->getKart(i);
            Log::warn(kart->getIdent().c_str(),
                "<start position=\"%d\" x=\"%f\" y=\"%f\" z=\"%f\" h=\"%f\"/>",
                i, kart->getXYZ().getX(), kart->getXYZ().getY(),
                kart->getXYZ().getZ(), kart->getHeading()*RAD_TO_DEGREE
                );
        }
        break;
    case DEBUG_VISUAL_VALUES:
        break;
    case DEBUG_ADJUST_LIGHTS:
    {
        if (!world) return false;
        break;
    }
    case DEBUG_SCRIPT_CONSOLE:
        break;
    case DEBUG_RUN_CUTSCENE:
        break;
    case DEBUG_TEXTURE_CONSOLE:
        break;
    case DEBUG_RENDER_NW_DEBUG:
        irr_driver->toggleRenderNetworkDebug();
        break;
    case DEBUG_START_RECORDING:
        irr_driver->setRecording(true);
        break;
    case DEBUG_STOP_RECORDING:
        irr_driver->setRecording(false);
        break;
    }   // switch
    return false;
}

// -----------------------------------------------------------------------------
/** Debug menu handling */
bool onEvent(const SEvent &event)
{
    return true;
}   // onEvent

// ----------------------------------------------------------------------------

bool handleStaticAction(int key)
{
    Camera* camera = Camera::getActiveCamera();
    unsigned int kart_num = 0;
    if (camera != NULL && camera->getKart() != NULL)
    {
        kart_num = camera->getKart()->getWorldKartId();
    }

    if (key == IRR_KEY_F1)
    {
        handleContextMenuAction(DEBUG_GUI_CAM_FREE);
    }
    else if (key == IRR_KEY_F2)
    {
        handleContextMenuAction(DEBUG_GUI_CAM_NORMAL);
    }
    else if (key == IRR_KEY_F3)
    {
#ifndef SERVER_ONLY
        SP::SPTextureManager::get()->reloadTexture("");
#endif
        return true;
    }
    else if (key == IRR_KEY_F5)
    {
        if (kart_num == 0)
        {
            kart_num += World::getWorld()->getNumKarts() - 1;
        }
        else
        {
            kart_num--;
        }
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        return true;
    }
    else if (key == IRR_KEY_F6)
    {
        if (kart_num == World::getWorld()->getNumKarts() - 1)
        {
            kart_num = 0;
        }
        else
        {
             kart_num++;
        }
        Camera::getActiveCamera()->setKart(World::getWorld()->getKart(kart_num));
        return true;
    }
    // TODO: create more keyboard shortcuts

    return false;
}

// ----------------------------------------------------------------------------
/** Returns if the debug menu is visible.
 */
bool isOpen()
{
    return g_debug_menu_visible;
}   // isOpen

// ----------------------------------------------------------------------------
/** Close the debug menu.
 */
void closeDebugMenu()
{
    g_debug_menu_visible = false;
}   // closeDebugMenu

}  // namespace Debug
