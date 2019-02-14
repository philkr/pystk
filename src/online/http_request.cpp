//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013-2015 Glenn De Jonghe
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

#include "online/http_request.hpp"

#include "config/user_config.hpp"
#include "config/stk_config.hpp"
#include "online/request_manager.hpp"
#include "utils/constants.hpp"
#include "utils/translation.hpp"

#include <assert.h>

namespace Online
{
    const std::string API::USER_PATH = "user/";
    const std::string API::SERVER_PATH = "server/";

    /** Creates a HTTP(S) request that will have a raw string as result. (Can
     *  of course be used if the result doesn't matter.)
     *  \param manage_memory whether or not the RequestManager should take care of
     *         deleting the object after all callbacks have been done.
     *  \param priority by what priority should the RequestManager take care of
     *         this request.
     */
    HTTPRequest::HTTPRequest(bool manage_memory, int priority)
               : Request(manage_memory, priority, 0)
    {
    }   // HTTPRequest

    // ------------------------------------------------------------------------
    /** This constructor configures this request to save the data in a flie.
     *  \param filename Name of the file to save the data to.
     *  \param manage_memory whether or not the RequestManager should take care of
     *         deleting the object after all callbacks have been done.
     *  \param priority by what priority should the RequestManager take care of
     *         this request.
     */
    HTTPRequest::HTTPRequest(const std::string &filename, bool manage_memory,
                                       int priority)
               : Request(manage_memory, priority, 0)
    {
    }   // HTTPRequest(filename ...)

    // ------------------------------------------------------------------------
    /** Char * needs a separate constructor, otherwise it will be considered
     *  to be the no-filename constructor (char* -> bool).
     */
    HTTPRequest::HTTPRequest(const char* const filename, bool manage_memory,
                                       int priority)
               : Request(manage_memory, priority, 0)
    {
    }   // HTTPRequest(filename ...)

} // namespace Online
