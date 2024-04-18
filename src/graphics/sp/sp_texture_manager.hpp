//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2018 SuperTuxKart-Team
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

#ifndef HEADER_SP_TEXTURE_MANAGER_HPP
#define HEADER_SP_TEXTURE_MANAGER_HPP

#ifndef SERVER_ONLY

#include "graphics/gl_headers.hpp"
#include "utils/log.hpp"
#include "utils/no_copy.hpp"

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "irrString.h"

class Material;

namespace SP
{
class SPTexture;

class SPTextureManager : public NoCopy
{
private:
    static SPTextureManager* m_sptm;

    std::map<std::string, std::shared_ptr<SPTexture> > m_textures;

public:
    // ------------------------------------------------------------------------
    static SPTextureManager* get()
    {
        if (m_sptm == NULL)
        {
            m_sptm = new SPTextureManager();
        }
        return m_sptm;
    }
    // ------------------------------------------------------------------------
    static void destroy()
    {
        delete m_sptm;
        m_sptm = NULL;
    }
    // ------------------------------------------------------------------------
    SPTextureManager();
    // ------------------------------------------------------------------------
    ~SPTextureManager();
    // ------------------------------------------------------------------------
    void removeUnusedTextures();
    // ------------------------------------------------------------------------
    std::shared_ptr<SPTexture> getTexture(const std::string& p,
                                          Material* m, bool undo_srgb,
                                          const std::string& container_id);
    // ------------------------------------------------------------------------
    void dumpAllTextures();
    // ------------------------------------------------------------------------
    irr::core::stringw reloadTexture(const irr::core::stringw& name);

};

}

#endif

#endif
