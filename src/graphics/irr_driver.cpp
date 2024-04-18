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

#include "graphics/irr_driver.hpp"

#include "config/user_config.hpp"
#include "font/font_manager.hpp"
#include "graphics/2dutils.hpp"
#include "graphics/b3d_mesh_loader.hpp"
#include "graphics/camera.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/glwrap.hpp"
#include "graphics/graphics_restrictions.hpp"
#include "graphics/light.hpp"
#include "graphics/material.hpp"
#include "graphics/material_manager.hpp"
#include "graphics/particle_kind_manager.hpp"
#include "graphics/per_camera_node.hpp"
#include "graphics/referee.hpp"
#include "graphics/render_target.hpp"
#include "graphics/shader_based_renderer.hpp"
#include "graphics/shared_gpu_objects.hpp"
#include "graphics/sp_mesh_loader.hpp"
#include "graphics/sp/sp_base.hpp"
#include "graphics/sp/sp_dynamic_draw_call.hpp"
#include "graphics/sp/sp_mesh.hpp"
#include "graphics/sp/sp_mesh_node.hpp"
#include "graphics/sp/sp_texture_manager.hpp"
#include "graphics/stk_tex_manager.hpp"
#include "graphics/stk_texture.hpp"
#include "graphics/sun.hpp"
#include "io/file_manager.hpp"
#include "items/item_manager.hpp"
#include "items/powerup_manager.hpp"
#include "items/attachment_manager.hpp"
#include "items/projectile_manager.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/kart_properties_manager.hpp"
#include "modes/world.hpp"
#include "physics/physics.hpp"
#include "scriptengine/property_animator.hpp"
#include "tracks/track_manager.hpp"
#include "tracks/track.hpp"
#include "utils/constants.hpp"
#include "utils/log.hpp"
#include "utils/profiler.hpp"
#include "utils/string_utils.hpp"
#include "utils/vs.hpp"

#include <irrlicht.h>

using namespace irr;

/** singleton */
IrrDriver *irr_driver = NULL;

#ifndef SERVER_ONLY
GPUTimer* m_perf_query[Q_LAST];
static const char* m_perf_query_phase[Q_LAST] =
{
    "Shadows Cascade 0",
    "Shadows Cascade 1",
    "Shadows Cascade 2",
    "Shadows Cascade 3",
    "Solid Pass",
    "Env Map",
    "SunLight",
    "PointLights",
    "SSAO",
    "Light Scatter",
    "Glow",
    "Combine Diffuse Color",
    "Skybox",
    "Transparent",
    "Particles",
    "Depth of Field",
    "Godrays",
    "Bloom",
    "Tonemap",
    "Motion Blur",
    "Lightning",
    "MLAA",
    "GUI",
};
#endif

const int MIN_SUPPORTED_HEIGHT = 768;
const int MIN_SUPPORTED_WIDTH  = 1024;
const bool ALLOW_1280_X_720    = true;

// ----------------------------------------------------------------------------
/** The constructor creates the irrlicht device. It first creates a NULL
 *  device. This is necessary to handle the Chicken/egg problem with irrlicht:
 *  access to the file system is given from the device, but we can't create the
 *  device before reading the user_config file (for resolution, fullscreen).
 *  So we create a dummy device here to begin with, which is then later (once
 *  the real device exists) changed in initDevice().
 */
IrrDriver::IrrDriver()
{
    SIrrlichtCreationParameters params;
    params.EventReceiver = nullptr;
    params.FileSystem    = file_manager->getFileSystem();
    params.DisplayAdapter= UserConfigParams::m_display_adapter;
    params.LoggingLevel  = ELL_WARNING;
    m_device = createDeviceEx(params);

    if(!m_device)
    {
        Log::fatal("irr_driver", "Couldn't initialise irrlicht device. Quitting.\n");
    }

#ifndef SERVER_ONLY
    m_wind                = new Wind();
#endif
    m_scene_complexity           = 0;

#ifndef SERVER_ONLY
    m_renderer            = NULL;
    for (unsigned i = 0; i < Q_LAST; i++)
    {
        m_perf_query[i] = new GPUTimer(m_perf_query_phase[i]);
    }
#endif
}   // IrrDriver

// ----------------------------------------------------------------------------
/** Destructor - removes the irrlicht device.
 */
IrrDriver::~IrrDriver()
{
    STKTexManager::getInstance()->kill();
#ifndef SERVER_ONLY
    delete m_wind;
    delete m_renderer;
    for (unsigned i = 0; i < Q_LAST; i++)
    {
        delete m_perf_query[i];
    }
#endif
    assert(m_device != NULL);
    m_device->drop();
    m_device = NULL;
}   // ~IrrDriver

// ----------------------------------------------------------------------------
/** Called before a race is started, after all cameras are set up.
 */
void IrrDriver::reset()
{
#ifndef SERVER_ONLY
    m_renderer->resetPostProcessing();
#endif
}   // reset

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
core::array<video::IRenderTarget> &IrrDriver::getMainSetup()
{
  return m_mrt;
}   // getMainSetup
// ----------------------------------------------------------------------------
GPUTimer &IrrDriver::getGPUTimer(unsigned i)
{
    return *m_perf_query[i];
}   // getGPUTimer
// ----------------------------------------------------------------------------
std::unique_ptr<RenderTarget> IrrDriver::createRenderTarget(const irr::core::dimension2du &dimension,
                                                            const std::string &name)
{
    return m_renderer->createRenderTarget(dimension, name);
}   // createRenderTarget
#endif   // ~SERVER_ONLY

// ----------------------------------------------------------------------------
/** This creates the actualy OpenGL device. This is called
 */
void IrrDriver::initDevice()
{
#ifndef SERVER_ONLY 

    // Assume sp is supported
    CentralVideoSettings::m_supports_sp = true;
    CVS->init();
#endif

    m_scene_manager = m_device->getSceneManager();
    m_video_driver  = m_device->getVideoDriver();

    B3DMeshLoader* b3dl = new B3DMeshLoader(m_scene_manager);
    m_scene_manager->addExternalMeshLoader(b3dl);
    b3dl->drop();

    SPMeshLoader* spml = new SPMeshLoader(m_scene_manager);
    m_scene_manager->addExternalMeshLoader(spml);
    spml->drop();

#ifndef SERVER_ONLY
    if (!CVS->isGLSL())
    {
        Log::fatal("irr_driver",
               "GLSL not supported by driver");
    }
	m_renderer = new ShaderBasedRenderer();
	preloadShaders();
#endif

    if (UserConfigParams::m_shadows_resolution != 0 &&
        (UserConfigParams::m_shadows_resolution < 512 ||
         UserConfigParams::m_shadows_resolution > 2048))
    {
        Log::warn("irr_driver",
               "Invalid value for UserConfigParams::m_shadows_resolution : %i",
            (int)UserConfigParams::m_shadows_resolution);
        UserConfigParams::m_shadows_resolution = 0;
    }

    // Immediate clear to black for a nicer user loading experience
    m_video_driver->beginScene(/*backBuffer clear*/true, /* Z */ false);
    m_video_driver->endScene();

#ifndef SERVER_ONLY
    if (CVS->isGLSL())
    {
        Log::info("irr_driver", "GLSL supported.");
    }

    // m_glsl might be reset in rtt if an error occurs.
    if (CVS->isGLSL())
    {
        m_mrt.clear();
        m_mrt.reallocate(2);
    }
    else
    {
        Log::warn("irr_driver", "Using the fixed pipeline (old GPU, or "
                                "shaders disabled in options)");
    }
#endif

    // Only change video driver settings if we are showing graphics
    {
        m_device->getVideoDriver()
            ->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
        m_device->getVideoDriver()
            ->setTextureCreationFlag(video::ETCF_OPTIMIZED_FOR_QUALITY, true);

        // Force creation of mipmaps even if the mipmaps flag in a b3d file
        // does not set the 'enable mipmap' flag.
        m_scene_manager->getParameters()
            ->setAttribute(scene::B3D_LOADER_IGNORE_MIPMAP_FLAG, true);

    } // If showing graphics

    // Initialize material2D
    video::SMaterial& material2D = m_video_driver->getMaterial2D();
    material2D.setFlag(video::EMF_ANTI_ALIASING, true);
    for (unsigned int n=0; n<video::MATERIAL_MAX_TEXTURES; n++)
    {
        material2D.TextureLayer[n].BilinearFilter = false;
        material2D.TextureLayer[n].TrilinearFilter = true;
        material2D.TextureLayer[n].TextureWrapU = video::ETC_CLAMP_TO_EDGE;
        material2D.TextureLayer[n].TextureWrapV = video::ETC_CLAMP_TO_EDGE;

        //material2D.TextureLayer[n].LODBias = 16;
        material2D.UseMipMaps = true;
    }
    material2D.AntiAliasing=video::EAAM_FULL_BASIC;
    //m_video_driver->enableMaterial2D();
}   // initDevice

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
void IrrDriver::setMaxTextureSize()
{
    const unsigned max =
        (UserConfigParams::m_high_definition_textures & 0x01) == 0 ?
        UserConfigParams::m_max_texture_size : 2048;
    io::IAttributes &att = m_video_driver->getNonConstDriverAttributes();
    att.setAttribute("MAX_TEXTURE_SIZE", core::dimension2du(max, max));
}   // setMaxTextureSize

// ----------------------------------------------------------------------------
void IrrDriver::unsetMaxTextureSize()
{
    io::IAttributes &att = m_video_driver->getNonConstDriverAttributes();
    att.setAttribute("MAX_TEXTURE_SIZE", core::dimension2du(2048, 2048));
}   // unsetMaxTextureSize

// ----------------------------------------------------------------------------
void IrrDriver::cleanSunInterposer()
{
    delete m_sun_interposer;
    m_sun_interposer = NULL;
}   // cleanSunInterposer

// ----------------------------------------------------------------------------
void IrrDriver::createSunInterposer()
{
#ifndef SERVER_ONLY
    scene::IMesh * sphere = m_scene_manager->getGeometryCreator()
        ->createSphereMesh(1, 16, 16);
    Material* material = material_manager->getDefaultSPMaterial("solid");
    m_sun_interposer = new SP::SPDynamicDrawCall
        (scene::EPT_TRIANGLES, NULL/*shader*/, material);
    for (unsigned i = 0; i < sphere->getMeshBufferCount(); i++)
    {
        scene::IMeshBuffer* mb = sphere->getMeshBuffer(i);
        if (!mb)
        {
            continue;
        }
        assert(mb->getVertexType() == video::EVT_STANDARD);
        video::S3DVertex* v_ptr = (video::S3DVertex*)mb->getVertices();
        uint16_t* idx_ptr = mb->getIndices();
        for (unsigned j = 0; j < mb->getIndexCount(); j++)
        {
            // For sun interposer we only need position for glow shader
            video::S3DVertexSkinnedMesh sp;
            const unsigned v_idx = idx_ptr[j];
            sp.m_position = v_ptr[v_idx].Pos;
            m_sun_interposer->addSPMVertex(sp);
        }
    }
    m_sun_interposer->recalculateBoundingBox();
    m_sun_interposer->setPosition(Track::getCurrentTrack()
        ->getGodRaysPosition());
    m_sun_interposer->setScale(core::vector3df(20));
    sphere->drop();
#endif
}

//-----------------------------------------------------------------------------
void IrrDriver::getOpenGLData(std::string *vendor, std::string *renderer,
                              std::string *version)
{
#ifndef SERVER_ONLY
    *vendor   = (char*)glGetString(GL_VENDOR  );
    *renderer = (char*)glGetString(GL_RENDERER);
    *version  = (char*)glGetString(GL_VERSION );
#endif
}   // getOpenGLData
#endif  // SERVER_ONLY

// ----------------------------------------------------------------------------
/** Loads an animated mesh and returns a pointer to it.
 *  \param filename File to load.
 */
scene::IAnimatedMesh *IrrDriver::getAnimatedMesh(const std::string &filename)
{
    scene::IAnimatedMesh *m  = NULL;

    if (StringUtils::getExtension(filename) == "b3dz")
    {
        // compressed file
        io::IFileSystem* file_system = getDevice()->getFileSystem();
        if (!file_system->addFileArchive(filename.c_str(),
                                         /*ignoreCase*/false,
                                         /*ignorePath*/true, io::EFAT_ZIP))
        {
            Log::error("irr_driver",
                       "getMesh: Failed to open zip file <%s>\n",
                       filename.c_str());
            return NULL;
        }

        // Get the recently added archive
        io::IFileArchive* zip_archive =
        file_system->getFileArchive(file_system->getFileArchiveCount()-1);
        io::IReadFile* content = zip_archive->createAndOpenFile(0);
        m = m_scene_manager->getMesh(content);
        content->drop();

        file_system->removeFileArchive(file_system->getFileArchiveCount()-1);
    }
    else
    {
        m = m_scene_manager->getMesh(filename.c_str());
    }

    if(!m) return NULL;

    setAllMaterialFlags(m);

    return m;
}   // getAnimatedMesh

// ----------------------------------------------------------------------------

/** Loads a non-animated mesh and returns a pointer to it.
 *  \param filename  File to load.
 */
scene::IMesh *IrrDriver::getMesh(const std::string &filename)
{
    scene::IAnimatedMesh* am = getAnimatedMesh(filename);
    if (am == NULL)
    {
        Log::error("irr_driver", "Cannot load mesh <%s>\n",
                   filename.c_str());
        return NULL;
    }
    return am->getMesh(0);
}   // getMesh

// ----------------------------------------------------------------------------
/** Sets the material flags in this mesh depending on the settings in
 *  material_manager.
 *  \param mesh  The mesh to change the settings in.
 */
void IrrDriver::setAllMaterialFlags(scene::IMesh *mesh) const
{
#ifndef SERVER_ONLY
    if (CVS->isGLSL())
    {
        return;
    }
#endif
    unsigned int n=mesh->getMeshBufferCount();
    for(unsigned int i=0; i<n; i++)
    {
        scene::IMeshBuffer *mb = mesh->getMeshBuffer(i);
        video::SMaterial &irr_material = mb->getMaterial();
        video::ITexture* t = irr_material.getTexture(0);
        if (t)
        {
            material_manager->setAllMaterialFlags(t, mb);
        }
        else
        {
            material_manager->setAllUntexturedMaterialFlags(mb);
        }
    }  // for i<getMeshBufferCount()
}   // setAllMaterialFlags

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
/** Adds a sphere with a given radius and color.
 *  \param radius The radius of the sphere.
 *  \param color The color to use (default (0,0,0,0)
 */
scene::ISceneNode *IrrDriver::addSphere(float radius,
                                        const video::SColor &color)
{
    scene::IMesh *mesh = m_scene_manager->getGeometryCreator()
                       ->createSphereMesh(radius);

    mesh->setMaterialFlag(video::EMF_COLOR_MATERIAL, true);
    video::SMaterial &m = mesh->getMeshBuffer(0)->getMaterial();
    m.AmbientColor    = color;
    m.DiffuseColor    = color;
    m.EmissiveColor   = color;
    m.BackfaceCulling = false;
    m.MaterialType    = video::EMT_SOLID;
    if (CVS->isGLSL())
    {
        SP::SPMesh* spm = SP::convertEVTStandard(mesh, &color);
        SP::SPMeshNode* spmn = new SP::SPMeshNode(spm,
            m_scene_manager->getRootSceneNode(), m_scene_manager, -1,
            "sphere");
        spmn->setMesh(spm);
        spm->drop();
        spmn->drop();
        return spmn;
    }

    scene::IMeshSceneNode *node = m_scene_manager->addMeshSceneNode(mesh);
    mesh->drop();
    return node;
}   // addSphere

// ----------------------------------------------------------------------------
/** Adds a particle scene node.
 */
scene::IParticleSystemSceneNode *IrrDriver::addParticleNode(bool default_emitter)
{
    return m_scene_manager->addParticleSystemSceneNode(default_emitter);
}   // addParticleNode

#endif
// ----------------------------------------------------------------------------
/** Adds a static mesh to scene. This should be used for smaller objects,
 *  since the node is not optimised.
 *  \param mesh The mesh to add.
 */
scene::ISceneNode *IrrDriver::addMesh(scene::IMesh *mesh,
                                      const std::string& debug_name,
                                      scene::ISceneNode *parent,
                                      std::shared_ptr<RenderInfo> render_info)
{
#ifdef SERVER_ONLY
    return m_scene_manager->addMeshSceneNode(mesh, parent);
#else
    if (!CVS->isGLSL())
        return m_scene_manager->addMeshSceneNode(mesh, parent);

    if (!parent)
      parent = m_scene_manager->getRootSceneNode();

    scene::ISceneNode* node = NULL;
    SP::SPMesh* spm = dynamic_cast<SP::SPMesh*>(mesh);
    if (spm || mesh == NULL)
    {
        SP::SPMeshNode* spmn = new SP::SPMeshNode(spm, parent, m_scene_manager,
            -1, debug_name, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0),
            core::vector3df(1.0f, 1.0f, 1.0f), render_info);
        spmn->setMesh(spm);
        spmn->setAnimationState(false);
        node = spmn;
    }
    else
    {
        Log::warn("IrrDriver", "Use only spm in glsl");
        return NULL;
    }
    node->drop();

    return node;
#endif
}   // addMesh

// ----------------------------------------------------------------------------
/** Adds a billboard node to scene.
 */
scene::ISceneNode *IrrDriver::addBillboard(const core::dimension2d< f32 > size,
                                           const std::string& tex_name,
                                           scene::ISceneNode* parent)
{
    scene::IBillboardSceneNode* node;
    node = m_scene_manager->addBillboardSceneNode(parent, size);

    const bool full_path = tex_name.find('/') != std::string::npos;

    Material* m = material_manager->getMaterial(tex_name, full_path,
        /*make_permanent*/false, /*complain_if_not_found*/true,
        /*strip_path*/full_path, /*install*/false);

    video::ITexture* tex = m->getTexture(true/*srgb*/,
        m->getShaderName() == "additive" ||
        m->getShaderName() == "alphablend" ?
        true : false/*premul_alpha*/);

    assert(node->getMaterialCount() > 0);
    node->setMaterialTexture(0, tex);
    if (!(m->getShaderName() == "additive" ||
        m->getShaderName() == "alphablend"))
    {
        // Alpha test for billboard otherwise
        m->setShaderName("alphatest");
    }
    m->setMaterialProperties(&(node->getMaterial(0)), NULL);
    return node;
}   // addBillboard

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
/** Creates a quad mesh with a given material.
 *  \param material The material to use (NULL if no material).
 *  \param create_one_quad If true creates one quad in the mesh.
 */
scene::IMesh *IrrDriver::createQuadMesh(const video::SMaterial *material,
                                        bool create_one_quad)
{
    scene::SMeshBuffer *buffer = new scene::SMeshBuffer();
    if(create_one_quad)
    {
        video::S3DVertex v;
        v.Pos    = core::vector3df(0,0,0);
        v.Normal = core::vector3df(1/sqrt(2.0f), 1/sqrt(2.0f), 0);

        // Add the vertices
        // ----------------
        buffer->Vertices.push_back(v);
        buffer->Vertices.push_back(v);
        buffer->Vertices.push_back(v);
        buffer->Vertices.push_back(v);

        // Define the indices for the triangles
        // ------------------------------------
        buffer->Indices.push_back(0);
        buffer->Indices.push_back(1);
        buffer->Indices.push_back(2);

        buffer->Indices.push_back(0);
        buffer->Indices.push_back(2);
        buffer->Indices.push_back(3);
    }
    if(material)
        buffer->Material = *material;
    scene::SMesh *mesh   = new scene::SMesh();
    mesh->addMeshBuffer(buffer);
    mesh->recalculateBoundingBox();
    buffer->drop();
    return mesh;
}   // createQuadMesh
#endif

// ----------------------------------------------------------------------------
/** Removes a scene node from the scene.
 *  \param node The scene node to remove.
 */
void IrrDriver::removeNode(scene::ISceneNode *node)
{
    node->remove();
}   // removeNode

// ----------------------------------------------------------------------------
/** Removes a mesh from the mesh cache, freeing the memory.
 *  \param mesh The mesh to remove.
 */
void IrrDriver::removeMeshFromCache(scene::IMesh *mesh)
{
    m_scene_manager->getMeshCache()->removeMesh(mesh);
}   // removeMeshFromCache

// ----------------------------------------------------------------------------
/** Removes a texture from irrlicht's texture cache.
 *  \param t The texture to remove.
 */
void IrrDriver::removeTexture(video::ITexture *t)
{
    STKTexture* stkt = dynamic_cast<STKTexture*>(t);
    if (stkt)
    {
        STKTexManager::getInstance()->removeTexture(stkt);
        return;
    }
    m_video_driver->removeTexture(t);
}   // removeTexture

// ----------------------------------------------------------------------------
/** Adds an animated mesh to the scene.
 *  \param mesh The animated mesh to add.
 */
scene::IAnimatedMeshSceneNode *IrrDriver::addAnimatedMesh(scene::IAnimatedMesh *mesh,
    const std::string& debug_name, scene::ISceneNode* parent,
    std::shared_ptr<RenderInfo> render_info)
{
    scene::IAnimatedMeshSceneNode* node;
#ifndef SERVER_ONLY
    SP::SPMesh* spm = dynamic_cast<SP::SPMesh*>(mesh);
    if (CVS->isGLSL() && (spm || mesh == NULL))
    {
        if (!parent)
        {
            parent = m_scene_manager->getRootSceneNode();
        }
        SP::SPMeshNode* spmn = new SP::SPMeshNode(spm, parent, m_scene_manager,
            -1, debug_name, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0),
            core::vector3df(1.0f, 1.0f, 1.0f), render_info);
        spmn->drop();
        spmn->setMesh(mesh);
        node = spmn;
    }
    else
#endif
    {
        node = m_scene_manager->addAnimatedMeshSceneNode(mesh, parent, -1,
            core::vector3df(0, 0, 0),
            core::vector3df(0, 0, 0),
            core::vector3df(1, 1, 1),
            /*addIfMeshIsZero*/true);
    }
    return node;

}   // addAnimatedMesh

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
/** Adds a sky dome. Documentation from irrlicht:
 *  A skydome is a large (half-) sphere with a panoramic texture on the inside
 *  and is drawn around the camera position.
 *  \param texture: Texture for the dome.
 *  \param horiRes: Number of vertices of a horizontal layer of the sphere.
 *  \param vertRes: Number of vertices of a vertical layer of the sphere.
 *  \param texturePercentage: How much of the height of the texture is used.
 *         Should be between 0 and 1.
 *  \param spherePercentage: How much of the sphere is drawn. Value should be
 *          between 0 and 2, where 1 is an exact half-sphere and 2 is a full
 *          sphere.
 */
scene::ISceneNode *IrrDriver::addSkyDome(video::ITexture *texture,
                                         int hori_res, int vert_res,
                                         float texture_percent,
                                         float sphere_percent)
{
    Log::error("skybox", "Using deprecated SkyDome");
    return m_scene_manager->addSkyDomeSceneNode(texture, hori_res, vert_res,
                                                texture_percent,
                                                sphere_percent);
}   // addSkyDome

// ----------------------------------------------------------------------------
/** Adds a skybox using. Irrlicht documentation:
 *  A skybox is a big cube with 6 textures on it and is drawn around the camera
 *  position.
 *  \param top: Texture for the top plane of the box.
 *  \param bottom: Texture for the bottom plane of the box.
 *  \param left: Texture for the left plane of the box.
 *  \param right: Texture for the right plane of the box.
 *  \param front: Texture for the front plane of the box.
 *  \param back: Texture for the back plane of the box.
 */
scene::ISceneNode *IrrDriver::addSkyBox(const std::vector<video::ITexture*> &texture,
    const std::vector<video::ITexture*> &spherical_harmonics_textures)
{
    assert(texture.size() == 6);

    m_renderer->addSkyBox(texture, spherical_harmonics_textures);

    return m_scene_manager->addSkyBoxSceneNode(texture[0], texture[1],
                                               texture[2], texture[3],
                                               texture[4], texture[5]);
}   // addSkyBox

// ----------------------------------------------------------------------------
void IrrDriver::suppressSkyBox()
{
    m_renderer->removeSkyBox();;
}   // suppressSkyBox
#endif

// ----------------------------------------------------------------------------
/** Adds a camera to the scene.
 */
scene::ICameraSceneNode *IrrDriver::addCameraSceneNode()
 {
     return m_scene_manager->addCameraSceneNode();
 }   // addCameraSceneNode

// ----------------------------------------------------------------------------
/** Removes a camera. This can't be done with removeNode() since the camera
 *  can be marked as active, meaning a drop will not delete it. While this
 *  doesn't really cause a memory leak (the camera is removed the next time
 *  a camera is added), it's a bit cleaner and easier to check for memory
 *  leaks, since the scene root should now always be empty.
 */
void IrrDriver::removeCameraSceneNode(scene::ICameraSceneNode *camera)
{
    if(camera==m_scene_manager->getActiveCamera())
        m_scene_manager->setActiveCamera(NULL);    // basically causes a drop
    camera->remove();
}   // removeCameraSceneNode

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
/** Loads a texture from a file and returns the texture object. This is just
 *  a convenient wrapper which loads the texture from a STK asset directory.
 *  It calls the file manager to get the full path, then calls the normal
 *  getTexture() function.s
 *  \param type The FileManager::AssetType of the texture.
 *  \param filename File name of the texture to load.
 *  \param is_premul If the alpha values needd to be multiplied for
 *         all pixels.
 *  \param is_prediv If the alpha value needs to be divided into
 *         each pixel.
 */
video::ITexture *IrrDriver::getTexture(FileManager::AssetType type,
                                       const std::string &filename,
                                       bool is_premul,
                                       bool is_prediv,
                                       bool complain_if_not_found)
{
    const std::string path = file_manager->getAsset(type, filename);
    return getTexture(path, is_premul, is_prediv, complain_if_not_found);
}   // getTexture

// ----------------------------------------------------------------------------
/** Loads a texture from a file and returns the texture object.
 *  \param filename File name of the texture to load.
 *  \param is_premul If the alpha values needd to be multiplied for
 *         all pixels.
 *  \param is_prediv If the alpha value needs to be divided into
 *         each pixel.
 */
video::ITexture *IrrDriver::getTexture(const std::string &filename,
                                       bool is_premul,
                                       bool is_prediv,
                                       bool complain_if_not_found)
{
    return STKTexManager::getInstance()->getTexture(filename);
}   // getTexture

// ----------------------------------------------------------------------------
/** Appends a pointer to each texture used in this mesh to the vector.
 *  \param mesh The mesh from which the textures are being determined.
 *  \param texture_list The list to which to attach the pointer to.
 */
void IrrDriver::grabAllTextures(const scene::IMesh *mesh)
{
#ifndef SERVER_ONLY
    if (CVS->isGLSL())
    {
        // SPM files has shared_ptr auto-delete texture 
        return;
    }
#endif
    const unsigned int n = mesh->getMeshBufferCount();

    for(unsigned int i=0; i<n; i++)
    {
        scene::IMeshBuffer *b = mesh->getMeshBuffer(i);
        video::SMaterial   &m = b->getMaterial();
        for(unsigned int j=0; j<video::MATERIAL_MAX_TEXTURES; j++)
        {
            video::ITexture *t = m.getTexture(j);
            if(t)
                t->grab();
        }   // for j < MATERIAL_MAX_TEXTURE
    }   // for i <getMeshBufferCount
}   // grabAllTextures

// ----------------------------------------------------------------------------
/** Appends a pointer to each texture used in this mesh to the vector.
 *  \param mesh The mesh from which the textures are being determined.
 *  \param texture_list The list to which to attach the pointer to.
 */
void IrrDriver::dropAllTextures(const scene::IMesh *mesh)
{
#ifndef SERVER_ONLY
    if (CVS->isGLSL())
    {
        // SPM files has shared_ptr auto-delete texture 
        return;
    }
#endif
    const unsigned int n = mesh->getMeshBufferCount();

    for(unsigned int i=0; i<n; i++)
    {
        scene::IMeshBuffer *b = mesh->getMeshBuffer(i);
        video::SMaterial   &m = b->getMaterial();
        for(unsigned int j=0; j<video::MATERIAL_MAX_TEXTURES; j++)
        {
            video::ITexture *t = m.getTexture(j);
            if(t)
            {
                t->drop();
                if(t->getReferenceCount()==1)
                    removeTexture(t);
            }   // if t
        }   // for j < MATERIAL_MAX_TEXTURE
    }   // for i <getMeshBufferCount
}   // dropAllTextures
#endif

// ----------------------------------------------------------------------------
void IrrDriver::onLoadWorld()
{
#ifndef SERVER_ONLY
    m_renderer->onLoadWorld();
#endif
}   // onLoadWorld

    // ----------------------------------------------------------------------------
void IrrDriver::onUnloadWorld()
{
#ifndef SERVER_ONLY
    m_renderer->onUnloadWorld();
#endif
}   // onUnloadWorld

void IrrDriver::minimalUpdate(float dt) {
    PropertyAnimator::get()->update(dt);
    if (World::getWorld())
    {
#ifndef SERVER_ONLY
        m_renderer->minimalRender(dt);
#endif
    }
}

#ifndef SERVER_ONLY

// ----------------------------------------------------------------------------
/** Sets the ambient light.
 *  \param light The colour of the light to set.
 *  \param force_SH_computation If false, do not recompute spherical harmonics
 *  coefficient when spherical harmonics textures have been defined
 */
void IrrDriver::setAmbientLight(const video::SColorf &light, bool force_SH_computation)
{
    video::SColorf color = light;
    color.r = powf(color.r, 1.0f / 2.2f);
    color.g = powf(color.g, 1.0f / 2.2f);
    color.b = powf(color.b, 1.0f / 2.2f);

    m_scene_manager->setAmbientLight(color);
    m_renderer->setAmbientLight(light, force_SH_computation);
}   // setAmbientLight

// ----------------------------------------------------------------------------
video::SColorf IrrDriver::getAmbientLight() const
{
    return m_scene_manager->getAmbientLight();
}
// ----------------------------------------------------------------------------
scene::ISceneNode *IrrDriver::addLight(const core::vector3df &pos,
                                       float energy, float radius,
                                       float r, float g, float b,
                                       bool sun, scene::ISceneNode* parent)
{
    if (CVS->isGLSL())
    {
        if (parent == NULL) parent = m_scene_manager->getRootSceneNode();
        LightNode *light = NULL;

        if (!sun)
            light = new LightNode(m_scene_manager, parent, energy, radius,
                                  r, g, b);
        else
            light = new SunNode(m_scene_manager, parent, r, g, b);

        light->setPosition(pos);
        light->updateAbsolutePosition();

        m_lights.push_back(light);

        if (sun)
        {
            m_renderer->addSunLight(pos);
        }
        return light;
    }
    else
    {
        scene::ILightSceneNode* light = m_scene_manager
               ->addLightSceneNode(m_scene_manager->getRootSceneNode(),
                                   pos, video::SColorf(r, g, b, 1.0f));
        light->setRadius(radius);
        return light;
    }
}   // addLight

// ----------------------------------------------------------------------------

void IrrDriver::clearLights()
{
    for (unsigned int i = 0; i < m_lights.size(); i++)
    {
        m_lights[i]->drop();
    }

    m_lights.clear();
}   // clearLights

#endif
