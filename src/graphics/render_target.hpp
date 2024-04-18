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

#ifndef HEADER_RENDER_TARGET_HPP
#define HEADER_RENDER_TARGET_HPP

#include <irrlicht.h>
#include <string>
#include "utils/no_copy.hpp"

class FrameBuffer;
class RTT;
class ShaderBasedRenderer;

#ifndef SERVER_ONLY
class RenderTarget: public NoCopy
{
private:
    ShaderBasedRenderer* m_renderer;
    std::string m_name;
    RTT* m_rtts;
    FrameBuffer* m_frame_buffer;

public:
    RenderTarget(const irr::core::dimension2du &dimension,
                    const std::string &name,
                    ShaderBasedRenderer *renderer);
    ~RenderTarget();
    void draw2DImage(const irr::core::rect<irr::s32>& dest_rect,
                     const irr::core::rect<irr::s32>* clip_rect,
                     const irr::video::SColor &colors,
                     bool use_alpha_channel_of_texture) const;
    irr::core::dimension2du getTextureSize() const;
    void renderToTexture(irr::scene::ICameraSceneNode* camera, float dt);
    void setFrameBuffer(FrameBuffer* fb) { m_frame_buffer = fb; }
    virtual RTT* getRTTs() { return m_rtts; }
};
#endif
#endif
