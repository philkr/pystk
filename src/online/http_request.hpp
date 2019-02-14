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

#ifndef HEADER_HTTP_REQUEST_HPP
#define HEADER_HTTP_REQUEST_HPP

#include "io/file_manager.hpp"
#include "online/request.hpp"
#include "utils/cpp2011.hpp"
#include "utils/string_utils.hpp"
#include "utils/synchronised.hpp"

#include <assert.h>
#include <string>

namespace Online
{
    class API
    {
    public:
        static const std::string USER_PATH;
        static const std::string SERVER_PATH;
    };

    /** A http request.
     */
    class HTTPRequest : public Request
    {
        std::string NO_CURL = "NO CURL support";
        std::string empty_;
    public :
        HTTPRequest(bool manage_memory = false, int priority = 1);
        HTTPRequest(const std::string &filename, bool manage_memory = false,
                    int priority = 1);
        HTTPRequest(const char * const filename, bool manage_memory = false,
                    int priority = 1);
        virtual           ~HTTPRequest() {}
        virtual bool       isAllowedToAdd() const { return false; }
        void               setApiURL(const std::string& url, const std::string &action) {}
        void               setAddonsURL(const std::string& path) {}

        // ------------------------------------------------------------------------
        /** Returns true if there was an error downloading the file. */
        bool hadDownloadError() const { return true; }

        // ------------------------------------------------------------------------
        /** Returns the curl error message if an error has occurred.
         *  \pre m_curl_code!=CURLE_OK
         */
        const char* getDownloadErrorMessage() const
        {
            return NO_CURL.c_str();
        }   // getDownloadErrorMessage

        // ------------------------------------------------------------------------
        /** Returns the downloaded string.
         *  \pre request has to be done
         *  \return get the result string from the request reply
         */
        const std::string & getData() const
        {
            return empty_;
        }   // getData

        // --------------------------------------------------------------------
        /** Sets a parameter to 'value' (std::string). */
        void addParameter(const std::string & name, const std::string &value)
        {
        }   // addParameter

        // --------------------------------------------------------------------
        /** Sets a parameter to 'value' (stringw). */
        void addParameter(const std::string &name,
                          const irr::core::stringw &value)
        {
        }   // addParameter

        // --------------------------------------------------------------------
        /** Sets a parameter to 'value' (arbitrary types). */
        template <typename T>
        void addParameter(const std::string &name, const T& value)
        {
        }   // addParameter

        // --------------------------------------------------------------------
        /** Returns the current progress. */
        float getProgress() const { return 1.f; }

        // --------------------------------------------------------------------
        /** Sets the current progress. */
        void setProgress(float f) { }

        // --------------------------------------------------------------------
        /** Sets the URL for this request. */
        void setURL(const std::string & url)
        {
        }   // setURL

    };   // class HTTPRequest
} //namespace Online
#endif // HEADER_HTTP_REQUEST_HPP
