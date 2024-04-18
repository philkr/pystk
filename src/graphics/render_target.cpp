//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2014-2015 SuperTuxKart-Team
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

#ifndef SERVER_ONLY
#include "graphics/render_target.hpp"

#include "graphics/2dutils.hpp"
#include "graphics/frame_buffer.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/rtts.hpp"
#include "graphics/shader_based_renderer.hpp"

//-----------------------------------------------------------------------------
RenderTarget::RenderTarget(const irr::core::dimension2du &dimension,
                                 const std::string &name,
                                 ShaderBasedRenderer *renderer)
               : m_renderer(renderer), m_name(name)
{
    m_rtts = new RTT(dimension.Width, dimension.Height);
    m_frame_buffer = NULL;
}   // RenderTarget

//-----------------------------------------------------------------------------

RenderTarget::~RenderTarget()
{
    delete m_rtts;
}   // ~RenderTarget

//-----------------------------------------------------------------------------
void RenderTarget::renderToTexture(irr::scene::ICameraSceneNode* camera,
                                      float dt)
{
    m_frame_buffer = NULL;
    camera->setAspectRatio(1.f * m_rtts->getWidth() / m_rtts->getHeight());
    m_renderer->renderToTexture(this, camera, dt);
}   // renderToTexture

//-----------------------------------------------------------------------------
irr::core::dimension2du RenderTarget::getTextureSize() const
{
    return irr::core::dimension2du(m_rtts->getWidth(),
                                   m_rtts->getHeight());
}   // getTextureSize

//-----------------------------------------------------------------------------
void RenderTarget::draw2DImage(const irr::core::rect<s32>& dest_rect,
                                  const irr::core::rect<s32>* clip_rect,
                                  const irr::video::SColor &colors,
                                  bool use_alpha_channel_of_texture) const
{
    assert(m_frame_buffer != NULL);
    irr::core::rect<s32> source_rect(0, 0, m_frame_buffer->getWidth(),
                                     m_frame_buffer->getHeight());
    draw2DImageFromRTT(m_frame_buffer->getRTT()[0],
                       m_frame_buffer->getWidth(), m_frame_buffer->getHeight(),
                       dest_rect, source_rect,
                       clip_rect, colors, use_alpha_channel_of_texture);
}   // draw2DImage

#endif   // !SERVER_ONLY
