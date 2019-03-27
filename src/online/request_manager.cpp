//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2015 Lucas Baudin
//            (C) 2014-2015 Joerg Henrichs
//            (C) 2013-2015 Glenn De Jonghe
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

#include "online/request_manager.hpp"

#include "config/player_manager.hpp"
#include "config/user_config.hpp"
#include "states_screens/state_manager.hpp"
#include "utils/vs.hpp"

#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <errno.h>

#if defined(WIN32) && !defined(__CYGWIN__)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#else
#  include <sys/time.h>
#  include <math.h>
#endif

using namespace Online;

namespace Online
{
    RequestManager * RequestManager::m_request_manager = NULL;
    bool RequestManager::m_disable_polling = false;
    // ------------------------------------------------------------------------
    /** Deletes the http manager.
     */
    void RequestManager::deallocate()
    {
        if (m_request_manager!= NULL)
        {
            delete m_request_manager;
            m_request_manager = NULL;
        }
    }   // deallocate

    // ------------------------------------------------------------------------
    /** Checks if the http manager is running.
     */
    bool RequestManager::isRunning()
    {
        return m_request_manager != NULL;
    }   // isRunning
    // ------------------------------------------------------------------------
    /** Constructor. It only initialised values, it does not start the actual
     *  thread.
     */
    RequestManager::RequestManager()
    {
        m_menu_polling_interval = 60;  // Default polling: every 60 seconds.
        m_game_polling_interval = 60;  // same for game polling
        m_time_since_poll       = m_menu_polling_interval;
    }   // RequestManager

    // ------------------------------------------------------------------------
    RequestManager::~RequestManager()
    {
    }   // ~RequestManager

    // ------------------------------------------------------------------------
    /** Start the actual network thread. This can not be done as part of
     *  the constructor, since the assignment to the global network_http
     *  variable has not been assigned at that stage, and the thread might
     *  use network_http - a very subtle race condition. So the thread can
     *  only be started after the assignment (in main) has been done.
     *  \pre PlayerManager was created and has read the main data for each
     *                     player so that all data for automatic login is
     *                     availale.
     */
    void RequestManager::startNetworkThread()
    {
        // In case that login id was not saved (or first start of stk),
        // current player would not be defined at this stage.
        PlayerProfile *player = PlayerManager::getCurrentPlayer();
        if (player && player->wasOnlineLastTime() &&
            !UserConfigParams::m_always_show_login_screen &&
            UserConfigParams::m_internet_status != RequestManager::IPERM_NOT_ALLOWED)
        {
            PlayerManager::resumeSavedSession();
        }
    }   // startNetworkThread

    // ------------------------------------------------------------------------
    /** This function inserts a high priority request to quit into the request
     *  queue of the network thead, and also aborts any ongoing download.
     *  Separating this allows more time for the thread to finish cleanly,
     *  before it gets cancelled in the destructor.
     */
    void RequestManager::stopNetworkThread()
    {
        // This will queue a sign-out or client-quit request
        PlayerManager::onSTKQuit();

    }   // stopNetworkThread

    // ------------------------------------------------------------------------
    /** Inserts a request into the queue of all requests. The request will be
     *  sorted by priority.
     *  \param request The pointer to the new request to insert.
     */
    void RequestManager::addRequest(Request *request)
    {
    }   // addRequest

    // ------------------------------------------------------------------------
    /** Should be called every frame and takes care of processing the result
     *  queue and polling the database server if a user is signed in.
     */
    void RequestManager::update(float dt)
    {
        // Database polling starts here, only needed for registered users. If
        // there is no player data yet (i.e. either because first time start
        // of stk, and loging screen hasn't finished yet, or no default player
        // was saved), don't do anything
        if (!PlayerManager::getCurrentPlayer() ||
            !PlayerManager::isCurrentLoggedIn())
            return;

        m_time_since_poll += dt;
        float interval = m_game_polling_interval;
        if (StateManager::get()->getGameState() == GUIEngine::MENU)
                interval = m_menu_polling_interval;

        if (!m_disable_polling && m_time_since_poll > interval)
        {
            m_time_since_poll = 0;
            PlayerManager::requestOnlinePoll();
        }

    }   // update
} // namespace Online
