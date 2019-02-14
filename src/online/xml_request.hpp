//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2011-2015 Joerg Henrichs
//                2013 Glenn De Jonghe
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

#ifndef HEADER_XML_REQUEST_HPP
#define HEADER_XML_REQUEST_HPP

#include "io/file_manager.hpp"
#include "online/http_request.hpp"
#include "utils/cpp2011.hpp"
#include "utils/string_utils.hpp"
#include "utils/synchronised.hpp"

#include <assert.h>
#include <memory>
#include <string>


namespace Online
{
    /** A http request expecting a xml return value.
     */
    class XMLRequest : public HTTPRequest
    {
        irr::core::stringw NO_CORL_W = "No Curl support";
    public :
        XMLRequest(bool manage_memory = false, int priority = 1);
        virtual ~XMLRequest();

        // ------------------------------------------------------------------------
        /** Get the downloaded XML tree.
         *  \pre request has to be executed.
         *  \return get the complete result from the request reply.
         */
        const XMLNode * getXMLData() const
        {
            return nullptr;
        }   // getXMLData

        // ------------------------------------------------------------------------
        /** Returns the additional information (or error message) contained in
         *  a finished request.
        * \pre request had to be executed.
        * \return get the info from the request reply
        */
        const irr::core::stringw & getInfo() const
        {
            assert(hasBeenExecuted());
            return NO_CORL_W;
        }   // getInfo

        // --------------------------------------------------------------------
        /** Returns whether the request was successfully executed on the server.
         * \pre request had to be executed.
         * \return whether or not the request was a success. */
        bool isSuccess() const
        {
            assert(hasBeenExecuted());
            return false;
        }   // isSuccess

    };   // class XMLRequest
} //namespace Online
#endif // HEADER_XML_REQUEST_HPP
