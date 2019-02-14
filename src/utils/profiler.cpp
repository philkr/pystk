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

#include "config/user_config.hpp"
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

    // When initializing profile class during static initialization
    // UserConfigParams::m_max_fps may not be properly initialized with default
    // value, so we use hard-coded default value
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
/// Draw the markers
void Profiler::draw()
{
#ifndef SERVER_ONLY
    PROFILER_PUSH_CPU_MARKER("ProfilerDraw", 0xFF, 0xFF, 0x00);
    video::IVideoDriver*    driver = irr_driver->getVideoDriver();

    // Current frame points to the frame in which currently data is
    // being accumulated. Draw the previous (i.e. complete) frame.
    m_lock.lock();
    int indx = m_current_frame - 1;
    if (indx < 0) indx = m_max_frames - 1;
    m_lock.unlock();

    drawBackground();

    // Force to show the pointer
    irr_driver->showPointer();

    // Compute some values for drawing (unit: pixels, but we keep floats
    // for reducing errors accumulation)
    core::dimension2d<u32> screen_size = driver->getScreenSize();
    const double profiler_width = (1.0 - 2.0*MARGIN_X) * screen_size.Width;
    const double x_offset       = MARGIN_X*screen_size.Width;
    const double y_offset       = (MARGIN_Y + LINE_HEIGHT)*screen_size.Height;
    const double line_height    = LINE_HEIGHT*screen_size.Height;


    // Compute start end end time for this frame
    double start = 99999.0f;
    double end   = -1.0f;

    // Use this thread to compute start and end time. All other
    // threads might have 'unfinished' events, or multiple identical events
    // in this frame (i.e. start time would be incorrect).
    int thread_id = getThreadID();
    AllEventData &aed = m_all_threads_data[thread_id].m_all_event_data;
    AllEventData::iterator j;
    for (j = aed.begin(); j != aed.end(); ++j)
    {
        const Marker &marker = j->second.getMarker(indx);
        start = std::min(start, marker.getStart());
        end = std::max(end, marker.getEnd());
    }   // for j in events


    const double duration = end - start;
    const double factor = profiler_width / duration;

    std::stack<AllEventData::iterator> hovered_markers;
    for (int i = 0; i < m_threads_used; i++)
    {
        ThreadData &td = m_all_threads_data[i];
        AllEventData &aed = td.m_all_event_data;

        // Thread 1 has 'proper' start and end events (assuming that each
        // event is at most called once). But all other threads might have
        // multiple start and end events, so the recorder start time is only
        // of the last event and so can not be used to draw the bar graph
        double start_xpos = 0;
        for(int k=0; k<(int)td.m_ordered_headings.size(); k++)
        {
            AllEventData::iterator j = aed.find(td.m_ordered_headings[k]);
            const Marker &marker = j->second.getMarker(indx);
            if (i == thread_id)
                start_xpos = factor*marker.getStart();
            core::rect<s32> pos((s32)(x_offset + start_xpos),
                                (s32)(y_offset + i*line_height),
                                (s32)(x_offset + start_xpos
                                               + factor*marker.getDuration()),
                                (s32)(y_offset + (i + 1)*line_height)        );
            if (i != 0)
                start_xpos += factor*marker.getDuration();

            // Reduce vertically the size of the markers according to their layer
            pos.UpperLeftCorner.Y  += 2 * (int)marker.getLayer();
            pos.LowerRightCorner.Y -= 2 * (int)marker.getLayer();

            GL32_draw2DRectangle(j->second.getColour(), pos);
        }   // for j in AllEventdata
    }   // for i in threads


    // GPU profiler
    QueryPerf hovered_gpu_marker = Q_LAST;
    long hovered_gpu_marker_elapsed = 0;
    int gpu_y = int(y_offset + m_threads_used*line_height + line_height/2);
    float total = 0;
    for (unsigned i = 0; i < Q_LAST; i++)
    {
#ifndef SERVER_ONLY
        int n = irr_driver->getGPUTimer(i).elapsedTimeus();
        m_gpu_times[indx*Q_LAST + i] = n;
        total += n;
#endif
    }

    static video::SColor colors[] = {
        video::SColor(255, 255, 0, 0),
        video::SColor(255, 0, 255, 0),
        video::SColor(255, 0, 0, 255),
        video::SColor(255, 255, 255, 0),
        video::SColor(255, 255, 0, 255),
        video::SColor(255, 0, 255, 255)
    };

    if (hovered_markers.empty())
    {
        float curr_val = 0;
        for (unsigned i = 0; i < Q_LAST; i++)
        {
            //Log::info("GPU Perf", "Phase %d : %d us\n", i,
            //           irr_driver->getGPUTimer(i).elapsedTimeus());

            float elapsed = float(m_gpu_times[indx*Q_LAST+i]);
            core::rect<s32> pos((s32)(x_offset + (curr_val / total)*profiler_width),
                (s32)(y_offset + gpu_y),
                (s32)(x_offset + ((curr_val + elapsed) / total)*profiler_width),
                (s32)(y_offset + gpu_y + line_height));

            curr_val += elapsed;
            GL32_draw2DRectangle(colors[i % 6], pos);
        }

    }

    // Draw the end of the frame
    {
        s32 x_sync = (s32)(x_offset + factor*m_time_between_sync);
        s32 y_up_sync = (s32)(MARGIN_Y*screen_size.Height);
        s32 y_down_sync = (s32)( (MARGIN_Y + (2+m_threads_used)*LINE_HEIGHT)
                                * screen_size.Height                         );

        GL32_draw2DRectangle(video::SColor(0xFF, 0x00, 0x00, 0x00),
                             core::rect<s32>(x_sync, y_up_sync,
                                             x_sync + 1, y_down_sync));
    }

    PROFILER_POP_CPU_MARKER();
#endif
}   // draw

//-----------------------------------------------------------------------------
/// Handle freeze/unfreeze
void Profiler::onClick(const core::vector2di& mouse_pos)
{
    video::IVideoDriver*            driver = irr_driver->getVideoDriver();
    const core::dimension2d<u32>&   screen_size = driver->getScreenSize();

    core::rect<s32>background_rect(
        (int)(MARGIN_X                      * screen_size.Width),
        (int)(MARGIN_Y                      * screen_size.Height),
        (int)((1.0-MARGIN_X)                * screen_size.Width),
        (int)((MARGIN_Y + 3.0f*LINE_HEIGHT) * screen_size.Height)   );

    if(!background_rect.isPointInside(mouse_pos))
        return;

    switch(m_freeze_state)
    {
    case UNFROZEN:
        m_freeze_state = WAITING_FOR_FREEZE;
        break;

    case FROZEN:
        m_freeze_state = WAITING_FOR_UNFREEZE;
        break;

    case WAITING_FOR_FREEZE:
    case WAITING_FOR_UNFREEZE:
        // the user should not be that quick, and we prefer avoiding to introduce
        // bugs by unfrozing it while it has not frozen yet.
        // Same the other way around.
        break;
    }
}   // onClick

//-----------------------------------------------------------------------------
/// Helper to draw a white background
void Profiler::drawBackground()
{
#ifndef SERVER_ONLY
    video::IVideoDriver*            driver = irr_driver->getVideoDriver();
    const core::dimension2d<u32>&   screen_size = driver->getScreenSize();

    core::rect<s32>background_rect(
        (int)(MARGIN_X                      * screen_size.Width),
        (int)((MARGIN_Y + 1.75f*LINE_HEIGHT) * screen_size.Height),
        (int)((1.0-MARGIN_X)                * screen_size.Width),
        (int)((MARGIN_Y + 0.25f)             * screen_size.Height));

    video::SColor   color(0x88, 0xFF, 0xFF, 0xFF);
    GL32_draw2DRectangle(color, background_rect);
#endif
}   // drawBackground

//-----------------------------------------------------------------------------
/** Saves the collected profile data to a file. Filename is based on the
 *  stdout name (with -profile appended).
 */
void Profiler::writeToFile()
{
    m_lock.lock();
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
    m_lock.unlock();

}   // writeFile
