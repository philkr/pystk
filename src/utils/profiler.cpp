//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 SuperTuxKart-Team
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

#include "profiler.hpp"

#include "graphics/glwrap.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/2dutils.hpp"
#include "graphics/irr_driver.hpp"
#include "io/file_manager.hpp"
#include "utils/file_utils.hpp"
#include "utils/string_utils.hpp"
#include "utils/vs.hpp"

#include <algorithm>
#include <fstream>
#include <ostream>
#include <stack>
#include <sstream>

Profiler profiler;

// Unit is in pencentage of the screen dimensions
#define MARGIN_X    0.02f    // left and right margin
#define MARGIN_Y    0.02f    // top margin
#define LINE_HEIGHT 0.030f   // height of a line representing a thread

#define MARKERS_NAMES_POS     core::rect<s32>(50,100,150,600)
#define GPU_MARKERS_NAMES_POS core::rect<s32>(50,165,150,300)

// The width of the profiler corresponds to TIME_DRAWN_MS milliseconds
#define TIME_DRAWN_MS 30.0f 

// --- Begin portable precise timer ---
#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    double getTimeMilliseconds()
    {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        double perFreq = double(freq.QuadPart) / 1000.0;

        LARGE_INTEGER timer;
        QueryPerformanceCounter(&timer);
        return double(timer.QuadPart) / perFreq;
    }   // getTimeMilliseconds

#else
    #include <sys/time.h>
    double getTimeMilliseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return double(tv.tv_sec * 1000) + (double(tv.tv_usec) / 1000.0);
    }   // getTimeMilliseconds
#endif
// --- End portable precise timer ---

//-----------------------------------------------------------------------------
Profiler::Profiler()
{
    m_time_last_sync      = getTimeMilliseconds();
    m_time_between_sync   = 0.0;
    m_freeze_state        = UNFROZEN;

    m_max_frames          = 20 * 120;
    m_current_frame       = 0;
    m_has_wrapped_around  = false;
    m_threads_used = 1;
}   // Profile

//-----------------------------------------------------------------------------
Profiler::~Profiler()
{
}   // ~Profiler

//-----------------------------------------------------------------------------
/** It is split from the constructor so that it can be avoided allocating
 *  unnecessary memory when the profiler is never used (for example in no
 *  graphics). */
void Profiler::init()
{
    const int MAX_THREADS = 10;
    m_all_threads_data.resize(MAX_THREADS);
    m_thread_mapping.resize(MAX_THREADS);

    // Add this thread to the thread mapping
    m_thread_mapping[0] = std::this_thread::get_id();
    m_gpu_times.resize(Q_LAST * m_max_frames);
}   // init

//-----------------------------------------------------------------------------
/** Returns a unique index for a thread. If the calling thread is not yet in
 *  the mapping, it will assign a new unique id to this thread. This function
 *  is NOT thread-safe and must be called from a properly protected code
 *  section. */
int Profiler::getThreadID()
{
    std::thread::id thread = std::this_thread::get_id();
    int i = 0;
    while(i < m_threads_used)
    {
        if (memcmp( &m_thread_mapping[i],
                    &thread,
                    sizeof(thread)) ==0 )
        {
            return i;
        }
        i++;
    }   // for i <m_threads_used

    assert(m_threads_used < (int)m_thread_mapping.size());
    m_thread_mapping[m_threads_used] = thread;
    m_threads_used++;

    return m_threads_used - 1;
}   // getThreadID

//-----------------------------------------------------------------------------
/// Push a new marker that starts now
void Profiler::pushCPUMarker(const char* name, const video::SColor& colour)
{
}   // pushCPUMarker

//-----------------------------------------------------------------------------
/// Stop the last pushed marker
void Profiler::popCPUMarker()
{
}   // popCPUMarker

//-----------------------------------------------------------------------------
/** Switches the profiler either on or off.
 */
void Profiler::toggleStatus()
{
}   // toggleStatus

//-----------------------------------------------------------------------------
/** Saves all data for the current frame, and starts the next frame in the
 *  circular buffer. Any events that are currently active (e.g. in a separate
 *  thread) will be split in two parts: the beginning (till now) in the current
 *  frame, the rest will be added to the next frame.
 */
void Profiler::synchronizeFrame()
{
}   // synchronizeFrame

//-----------------------------------------------------------------------------
/** Saves the collected profile data to a file. Filename is based on the
 *  stdout name (with -profile appended).
 */
void Profiler::writeToFile()
{
    std::string base_name =
               file_manager->getUserConfigFile(file_manager->getStdoutName());
    // First CPU data
    for (int thread_id = 0; thread_id < m_threads_used; thread_id++)
    {
        std::ofstream f(FileUtils::getPortableWritingPath(
            base_name + ".profile-cpu-" + StringUtils::toString(thread_id)));
        ThreadData &td = m_all_threads_data[thread_id];
        f << "#  ";
        for (unsigned int i = 0; i < td.m_ordered_headings.size(); i++)
            f << "\"" << td.m_ordered_headings[i] << "(" << i+1 <<")\"   ";
        f << std::endl;
        int start = m_has_wrapped_around ? m_current_frame + 1 : 0;
        if (start > m_max_frames) start -= m_max_frames;
        while (start != m_current_frame)
        {
            for (unsigned int i = 0; i < td.m_ordered_headings.size(); i++)
            {
                const EventData &ed = td.m_all_event_data[td.m_ordered_headings[i]];
                f << int(ed.getMarker(start).getDuration()*1000) << " ";
            }   // for i i new_headings
            f << std::endl;
            start = (start + 1) % m_max_frames;
        }   // while start != m_current_frame
        f.close();
    }   // for all thread_ids

    std::ofstream f_gpu(FileUtils::getPortableWritingPath(base_name + ".profile-gpu"));
    f_gpu << "# ";

    for (unsigned i = 0; i < Q_LAST; i++)
    {
        f_gpu << "\"" << irr_driver->getGPUQueryPhaseName(i) << "(" << i+1 << ")\"   ";
    }   // for i < Q_LAST
    f_gpu << std::endl;

    int start = m_has_wrapped_around ? m_current_frame + 1 : 0;
    if (start > m_max_frames) start -= m_max_frames;
    while (start != m_current_frame)
    {
        for (unsigned i = 0; i < Q_LAST; i++)
        {
            f_gpu << m_gpu_times[start*Q_LAST + i] << "   ";
        }   // for i < Q_LAST
        f_gpu << std::endl;
        start = (start + 1) % m_max_frames;
    }
    f_gpu.close();

}   // writeFile
