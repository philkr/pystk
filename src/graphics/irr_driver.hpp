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

#ifndef HEADER_IRR_DRIVER_HPP
#define HEADER_IRR_DRIVER_HPP

/**
 * \defgroup graphics
 * This module contains the core graphics engine, that is mostly a thin layer
 * on top of irrlicht providing some additional features we need for STK
 * (like particles, more scene node types, mesh manipulation tools, material
 * management, etc...)
 */

#include <IVideoDriver.h>
#include <vector2d.h>
#include <dimension2d.h>
#include <SColor.h>
#include "IrrlichtDevice.h"
#include "ISkinnedMesh.h"
#include "graphics/shader_based_renderer.hpp"
#include "graphics/gl_headers.hpp"
#include "graphics/wind.hpp"
#include "io/file_manager.hpp"
#include "utils/aligned_array.hpp"
#include "utils/no_copy.hpp"
#include "utils/ptr_vector.hpp"
#include "utils/vec3.hpp"
#include <memory>
#include <string>
#include <vector>

#ifdef ANDROID
#include "main_android.hpp"
#endif


namespace SP
{
    class SPDynamicDrawCall;
}


namespace irr
{
    namespace scene { class ISceneManager; class IMesh; class IAnimatedMeshSceneNode; class IAnimatedMesh;
        class IMeshSceneNode; class IParticleSystemSceneNode; class ICameraSceneNode; class ILightSceneNode;
        class CLensFlareSceneNode; }
}
using namespace irr;

enum TypeRTT : unsigned int;
class AbstractKart;
class ShaderBasedRenderer;
class Camera;
class FrameBuffer;
class LightNode;
class PerCameraNode;
class RenderInfo;
class RenderTarget;

struct SHCoefficients;

/**
  * \brief class that creates the irrLicht device and offers higher-level
  *  ways to manage the 3D scene
  * \ingroup graphics
  */
class IrrDriver : public NoCopy
{    
private:
    /** The irrlicht device. */
    IrrlichtDevice             *m_device;
    /** Irrlicht scene manager. */
    scene::ISceneManager       *m_scene_manager;
    /** Irrlicht video driver. */
    video::IVideoDriver        *m_video_driver;
#ifndef SERVER_ONLY
    /** Renderer. */
    ShaderBasedRenderer        *m_renderer;
    
    /** Wind. */
    Wind                 *m_wind;
    /** The main MRT setup. */
    core::array<video::IRenderTarget> m_mrt;
#endif

    /** Matrixes used in several places stored here to avoid recomputation. */
    core::matrix4 m_ViewMatrix, m_InvViewMatrix, m_ProjMatrix, m_InvProjMatrix, m_ProjViewMatrix, m_InvProjViewMatrix;

public:
#ifndef SERVER_ONLY
    struct BloomData {
        scene::ISceneNode * node;
        float power;
    };

    video::SColorf getAmbientLight() const;
#endif


private:
    void                  setupViewports();

    /** Store if the scene is complex (based on polycount, etc) */
    int                  m_scene_complexity;

#ifndef SERVER_ONLY
    /** Internal method that applies the resolution in user settings. */
    bool                 m_ssaoviz;
    bool                 m_shadowviz;
    bool                 m_lightviz;
    bool                 m_boundingboxesviz;
    bool                 m_render_nw_debug;

    /** Background colour to reset a buffer. Can be changed by each track. */
    irr::video::SColor m_clear_color;


    unsigned             m_skinning_joint;

    SP::SPDynamicDrawCall* m_sun_interposer;
    core::vector3df m_sun_direction;
    video::SColorf m_suncolor;


    std::vector<LightNode *> m_lights;

    std::vector<BloomData> m_forcedbloom;

    std::vector<scene::ISceneNode *> m_background;

    float m_ssao_radius;
    float m_ssao_k;
    float m_ssao_sigma;
#endif
    
#ifdef DEBUG
    /** Used to visualise skeletons. */
    std::vector<irr::scene::IAnimatedMeshSceneNode*> m_debug_meshes;
#endif

public:
         IrrDriver();
        ~IrrDriver();
    void initDevice();
    void reset();

#ifndef SERVER_ONLY
    void setMaxTextureSize();
    void unsetMaxTextureSize();
    void getOpenGLData(std::string *vendor, std::string *renderer,
                       std::string *version);

    core::array<video::IRenderTarget> &getMainSetup();
#endif
    void setAllMaterialFlags(scene::IMesh *mesh) const;
    scene::IAnimatedMesh *getAnimatedMesh(const std::string &name);
    scene::IMesh         *getMesh(const std::string &name);
#ifndef SERVER_ONLY
    void                  setAmbientLight(const video::SColorf &light,
                                          bool force_SH_computation = true);
    video::ITexture      *getTexture(FileManager::AssetType type,
                                     const std::string &filename,
                                     bool is_premul=false,
                                     bool is_prediv=false,
                                     bool complain_if_not_found=true);
    video::ITexture      *getTexture(const std::string &filename,
                                     bool is_premul=false,
                                     bool is_prediv=false,
                                     bool complain_if_not_found=true);
    void                  grabAllTextures(const scene::IMesh *mesh);
    void                  dropAllTextures(const scene::IMesh *mesh);
    scene::IMesh         *createQuadMesh(const video::SMaterial *material=NULL,
                                         bool create_one_quad=false);
    scene::ISceneNode* addSphere(float radius,
                 const video::SColor &color=video::SColor(128, 255, 255, 255));
#endif
    scene::ISceneNode* addMesh(scene::IMesh *mesh,
                               const std::string& debug_name,
                               scene::ISceneNode *parent = NULL,
                               std::shared_ptr<RenderInfo> render_info = nullptr);
    scene::ISceneNode    *addBillboard(const core::dimension2d< f32 > size,
                                       const std::string& tex_name,
                                       scene::ISceneNode* parent=NULL);
#ifndef SERVER_ONLY
    scene::IParticleSystemSceneNode
                         *addParticleNode(bool default_emitter=true);
    scene::ISceneNode    *addSkyDome(video::ITexture *texture, int hori_res,
                                     int vert_res, float texture_percent,
                                     float sphere_percent);
    scene::ISceneNode    *addSkyBox(const std::vector<video::ITexture*> &texture_names,
                                    const std::vector<video::ITexture*> &spherical_harmonics_textures);
    void suppressSkyBox();
#endif
    void                  removeNode(scene::ISceneNode *node);
    void                  removeMeshFromCache(scene::IMesh *mesh);
    void                  removeTexture(video::ITexture *t);
    scene::IAnimatedMeshSceneNode
        *addAnimatedMesh(scene::IAnimatedMesh *mesh,
                         const std::string& debug_name,
                         scene::ISceneNode* parent = NULL,
                         std::shared_ptr<RenderInfo> render_info = nullptr);
    scene::ICameraSceneNode
                         *addCameraSceneNode();
    void                  removeCameraSceneNode(scene::ICameraSceneNode *camera);
    void                  minimalUpdate(float dt);

#ifndef SERVER_ONLY
    void                  setSkinningJoint(unsigned d) { m_skinning_joint = d; }
#endif

    class GPUTimer        &getGPUTimer(unsigned);

#ifndef SERVER_ONLY
    std::unique_ptr<RenderTarget> createRenderTarget(const irr::core::dimension2du &dimension,
                                                     const std::string &name);
    // ------------------------------------------------------------------------
    /** Returns the color to clear the back buffer. */
    const irr::video::SColor& getClearColor() const { return m_clear_color; }
    // ------------------------------------------------------------------------
    /** Sets the color to use when clearing the back buffer. */
    void setClearbackBufferColor(irr::video::SColor color)
    {
        m_clear_color = color;
    }   // setClearbackBufferColor
#endif

    // ------------------------------------------------------------------------
    /** Returns the irrlicht device. */
    IrrlichtDevice       *getDevice()       const { return m_device;        }
    // ------------------------------------------------------------------------
    /** Returns the irrlicht video driver. */
    video::IVideoDriver  *getVideoDriver()  const { return m_video_driver;  }
    // ------------------------------------------------------------------------
    /** Returns the irrlicht scene manager. */
    scene::ISceneManager *getSceneManager() const { return m_scene_manager; }
    // ------------------------------------------------------------------------
    /** Returns the current real time, which might not be 0 at start of the
     *  application. Value in msec. */
    unsigned int getRealTime() { return m_device->getTimer()->getRealTime(); }
    // ------------------------------------------------------------------------
    /** Use motion blur for a short time */
    void giveBoost(unsigned int cam_index) {
#ifndef SERVER_ONLY
        m_renderer->giveBoost(cam_index);
#endif
    }
#ifndef SERVER_ONLY
    // ------------------------------------------------------------------------
    inline core::vector3df getWind()  {return m_wind->getWind();}

    // -----------------------------------------------------------------------
    const core::vector3df& getSunDirection() const { return m_sun_direction; };
    // -----------------------------------------------------------------------
    void setSunDirection(const core::vector3df &SunPos)
    {
        m_sun_direction = SunPos;
    }
    // -----------------------------------------------------------------------
    video::SColorf getSunColor() const { return m_suncolor; }
    // -----------------------------------------------------------------------
    void setSunColor(const video::SColorf &col)
    {
        m_suncolor = col;
    }
    // ------------------------------------------------------------------------
    bool getBoundingBoxesViz()    { return m_boundingboxesviz;      }
#endif
    // ------------------------------------------------------------------------
    int getSceneComplexity() { return m_scene_complexity;           }
    void resetSceneComplexity() { m_scene_complexity = 0;           }
    void addSceneComplexity(int complexity)
    {
        if (complexity > 1) m_scene_complexity += (complexity - 1);
    }
#ifndef SERVER_ONLY
    // ------------------------------------------------------------------------
    std::vector<LightNode *> getLights() { return m_lights; }
    // ------------------------------------------------------------------------
    void addForcedBloomNode(scene::ISceneNode *n, float power = 1)
    {
        BloomData dat;
        dat.node = n;
        dat.power = power;

        m_forcedbloom.push_back(dat);
    }
    // ------------------------------------------------------------------------
    void clearForcedBloom() { m_forcedbloom.clear(); }
    // ------------------------------------------------------------------------
    const std::vector<BloomData> &getForcedBloom() const
    { 
        return m_forcedbloom;
    }
    // ------------------------------------------------------------------------
    void clearBackgroundNodes() { m_background.clear(); }
    // ------------------------------------------------------------------------
    void addBackgroundNode(scene::ISceneNode * const n) 
    {
        m_background.push_back(n);
    }
    // ------------------------------------------------------------------------
    scene::ISceneNode *addLight(const core::vector3df &pos, float energy,
                                float radius, float r, float g, float b,
                                bool sun = false, 
                                scene::ISceneNode* parent = NULL);
    // ------------------------------------------------------------------------
    void clearLights();
    // ------------------------------------------------------------------------
    SP::SPDynamicDrawCall* getSunInterposer() { return m_sun_interposer; }
    // ------------------------------------------------------------------------
    
    void cleanSunInterposer();
    void createSunInterposer();
#endif
    // ------------------------------------------------------------------------
    void setViewMatrix(core::matrix4 matrix)
    {
        m_ViewMatrix = matrix; matrix.getInverse(m_InvViewMatrix);
    }
    // ------------------------------------------------------------------------
    const core::matrix4 &getViewMatrix() const { return m_ViewMatrix; }
    // ------------------------------------------------------------------------
    const core::matrix4 &getInvViewMatrix() const { return m_InvViewMatrix; }
    // ------------------------------------------------------------------------
    void setProjMatrix(core::matrix4 matrix)
    {
        m_ProjMatrix = matrix; matrix.getInverse(m_InvProjMatrix);
    }
    // ------------------------------------------------------------------------
    const core::matrix4 &getProjMatrix() const { return m_ProjMatrix; }
    // ------------------------------------------------------------------------
    const core::matrix4 &getInvProjMatrix() const { return m_InvProjMatrix; }
    // ------------------------------------------------------------------------
    void genProjViewMatrix() 
    {
        m_ProjViewMatrix = m_ProjMatrix * m_ViewMatrix; 
        m_InvProjViewMatrix = m_ProjViewMatrix; 
        m_InvProjViewMatrix.makeInverse(); 
    }
    // ------------------------------------------------------------------------
    const core::matrix4 &getProjViewMatrix() const { return m_ProjViewMatrix; }
    // ------------------------------------------------------------------------
    const core::matrix4 &getInvProjViewMatrix() const 
    {
        return m_InvProjViewMatrix;
    }

#ifndef SERVER_ONLY
    // ------------------------------------------------------------------------
    const core::dimension2du &getCurrentScreenSize() const
    {
        return m_renderer->getCurrentScreenSize();
    }
    // ------------------------------------------------------------------------
    const core::dimension2du getActualScreenSize() const
    {
        return getCurrentScreenSize();
    }
    // ------------------------------------------------------------------------
    float getSSAORadius() const
    {
        return m_ssao_radius;
    }

    // ------------------------------------------------------------------------
    void setSSAORadius(float v)
    {
        m_ssao_radius = v;
    }

    // ------------------------------------------------------------------------
    float getSSAOK() const
    {
        return m_ssao_k;
    }

    // ------------------------------------------------------------------------
    void setSSAOK(float v)
    {
        m_ssao_k = v;
    }

    // ------------------------------------------------------------------------
    float getSSAOSigma() const
    {
        return m_ssao_sigma;
    }

    // ------------------------------------------------------------------------
    void setSSAOSigma(float v)
    {
        m_ssao_sigma = v;
    }
#endif  // SERVER_ONLY
    void onLoadWorld();
    void onUnloadWorld();
    void sameRestart()             {}

#ifndef SERVER_ONLY
    void uploadLightingData();
    u32 getDefaultFramebuffer() const
                            { return m_video_driver->getDefaultFramebuffer(); }
#endif  // SERVER_ONLY
};   // IrrDriver

extern IrrDriver *irr_driver;

#endif   // HEADER_IRR_DRIVER_HPP
