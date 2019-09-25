//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2014-2015 Joerg Henrichs
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

#ifdef __MINGW32__
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include "config/hardware_stats.hpp"

#include "config/user_config.hpp"
#include "config/stk_config.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/glwrap.hpp"
#include "graphics/irr_driver.hpp"
#include "utils/log.hpp"
#include "utils/random_generator.hpp"

#include <fstream>
#include <set>
#include <sstream>
#include <string>
#ifndef WIN32
#  include <sys/param.h>    // To get BSD macro
#  include <sys/utsname.h>
#endif
#if defined(__APPLE__) || defined(BSD)
#  include <sys/sysctl.h>
#endif

#include <vector>

