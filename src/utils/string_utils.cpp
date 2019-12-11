//  SuperTuxKart - a fun racing game with go-kart
//
//  Copyright (C) 2004-2015  Steve Baker <sjbaker1@airmail.net>,
//  Copyright (C) 2004-2015  Ingo Ruhnke <grumbel@gmx.de>
//  Copyright (C) 2006-2015  SuperTuxKart-Team
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

#include "utils/string_utils.hpp"

#include "config/stk_config.hpp"
#include "utils/constants.hpp"
#include "utils/log.hpp"
#include "utils/time.hpp"
#include "utils/types.hpp"
#include "utils/utf8.h"
#include "irrArray.h"

#include "coreutil.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <exception>

namespace StringUtils
{
    bool startsWith(const std::string& str, const std::string& prefix)
    {
        if (str.length() < prefix.length())
            return false;
        else
            return strncmp(str.c_str(), prefix.c_str(), prefix.size())==0;
    }

    //-------------------------------------------------------------------------
    /** Returns the path of a filename, i.e. everything till the last '/'.
     */
    std::string getPath(const std::string& filename)
    {
        for(int i = int(filename.size()) - 1; i >= 0; --i)
        {
            if (filename[i]=='/' || filename[i]=='\\')
            {
                return filename.substr(0,i);
            }
        }
        return "";
    }   // getPath

    //-------------------------------------------------------------------------
    /** Returns the basename of a filename, i.e. everything after the last "/".
     */
    std::string getBasename(const std::string& filename)
    {
        for(int i = int(filename.size()) - 1; i >= 0; --i)
        {
            if (filename[i]=='/' || filename[i]=='\\')
            {
                return filename.substr(i+1);
            }
        }
        return filename;
    }   // getBasename

    //-------------------------------------------------------------------------
    /** Removes the extension, i.e. everything after the last ".".
     */
    std::string removeExtension(const std::string& filename)
    {
        for(int i = int(filename.size()) - 1; i >= 0; --i)
        {
            if (filename[i] == '.')
            {
                return filename.substr(0, i);
            }
        }
        return filename;
    }   // removeExtension

    //-------------------------------------------------------------------------
    /** Returns the extension, i.e. everything after the last "."
     */
    std::string getExtension(const std::string& filename)
    {
        for(int i = int(filename.size()) - 1; i >= 0; --i)
        {
            if (filename[i] == '.')
            {
                return filename.substr(i+1);
            }
        }
        return filename;
    }   // getExtension

    //-------------------------------------------------------------------------
    /** Returns a string converted to lower case.
     */
    std::string toLowerCase(const std::string& str)
    {
        std::string name = str;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        return name;
    }   // toLowerCase

    //-------------------------------------------------------------------------
    /** Splits a string into substrings separated by a certain character, and
     *  returns a std::vector of all those substring. E.g.:
     *  split("a b=c d=e",' ')  --> ["a", "b=c", "d=e"]
     *  \param s The string to split.
     *  \param c The character  by which the string is split.
     */
    std::vector<std::string> split(const std::string& s, char c,
                                   bool keepSplitChar)
    {
        std::vector<std::string> result;

        try
        {
            std::string::size_type start=0;
            while(start < (unsigned int) s.size())
            {
                std::string::size_type i=s.find(c, start);
                if (i!=std::string::npos)
                {
                    if (keepSplitChar)
                    {
                        int from = (int)start-1;
                        if (from < 0) from = 0;

                        result.push_back(std::string(s, from, i-from));
                    }
                    else result.push_back(std::string(s,start, i-start));

                    start=i+1;
                }
                else   // end of string reached
                {
                    if (keepSplitChar && start != 0)
                        result.push_back(std::string(s,start-1));
                    else
                        result.push_back(std::string(s,start));
                    return result;
                }
            }
            return result;
        }
        catch (std::exception& e)
        {
            Log::error("StringUtils",
                       "Error in split(std::string) : %s @ line %i : %s.",
                     __FILE__, __LINE__, e.what());
            Log::error("StringUtils", "Splitting '%s'.", s.c_str());

            for (int n=0; n<(int)result.size(); n++)
            {
                Log::error("StringUtils", "Split : %s", result[n].c_str());
            }
            Log::fatal("StringUtils", "");
        }
        return result;
    }   // split

    //-------------------------------------------------------------------------
    /** Splits a string into substrings separated by a certain character, and
     *  returns a std::vector of all those substring. E.g.:
     *  split("a b=c d=e",' ')  --> ["a", "b=c", "d=e"]
     *  \param s The string to split.
     *  \param c The character  by which the string is split.
     */
    std::vector<std::u32string> split(const std::u32string& s, char32_t c,
                                      bool keepSplitChar)
    {
        std::vector<std::u32string> result;

        try
        {
            std::u32string::size_type start=0;
            while(start < (unsigned int) s.size())
            {
                std::u32string::size_type i=s.find(c, start);
                if (i!=std::u32string::npos)
                {
                    if (keepSplitChar)
                    {
                        int from = (int)start-1;
                        if (from < 0) from = 0;

                        result.push_back(std::u32string(s, from, i-from));
                    }
                    else result.push_back(std::u32string(s,start, i-start));

                    start=i+1;
                }
                else   // end of string reached
                {
                    if (keepSplitChar && start != 0)
                        result.push_back(std::u32string(s,start-1));
                    else
                        result.push_back(std::u32string(s,start));
                    return result;
                }
            }
            return result;
        }
        catch (std::exception& e)
        {
            Log::error("StringUtils",
                       "Error in split(std::string) : %s @ line %i : %s.",
                     __FILE__, __LINE__, e.what());
            Log::error("StringUtils", "Splitting '%s'.",
                       wideToUtf8(utf32ToWide(s)).c_str());

            for (int n=0; n<(int)result.size(); n++)
            {
                Log::error("StringUtils", "Split : %s",
                           wideToUtf8(utf32ToWide(result[n])).c_str());
            }
            Log::fatal("StringUtils", "");
        }
        return result;
    }   // split

    //-------------------------------------------------------------------------
    /** Splits a string into substrings separated by a certain character, and
     *  returns a std::vector of all those substring. E.g.:
     *  split("a b=c d=e",' ')  --> ["a", "b=c", "d=e"]
     *  This is the version for wide strings.
     *  \param s The string to split.
     *  \param c The character  by which the string is split.
     */
    std::vector<irr::core::stringw> split(const irr::core::stringw& s, char c,
                                           bool keepSplitChar)
    {
        try
        {
            std::vector<irr::core::stringw> result;

            irr::s32 start = 0;
            while (start < (irr::s32)s.size())
            {
                irr::s32 i = s.findNext(c, start);
                if (i != -1)
                {
                    if (keepSplitChar)
                    {
                        int from = start-1;
                        if (from < 0) from = 0;
                        result.push_back( s.subString(from, i-from) );
                    }
                    else result.push_back( s.subString(start, i-start) );
                    start = i+1;
                }
                else
                {
                    if (keepSplitChar && start != 0)
                        result.push_back( s.subString(start - 1,
                                                      s.size()-start + 1) );
                    else
                        result.push_back( s.subString(start, s.size()-start) );

                    return result;
                }
            }
            return result;
        }
        catch (std::exception& e)
        {
            (void)e;  // avoid warning about unused variable
            Log::fatal("StringUtils",
                       "Fatal error in split(stringw) : %s @ line %i : '%s'.",
                       __FILE__, __LINE__, e.what());
        }
        return std::vector<irr::core::stringw>();
    }   // split


    std::vector<uint32_t> splitToUInt(const std::string& s, char c, bool keepSplitChar)
    {
        std::vector<std::string> parts = split(s, c, keepSplitChar);
        std::vector<uint32_t> ints;
        for(unsigned int i = 0; i < parts.size(); ++i)
        {
           ints.push_back(atoi(parts[i].c_str()));
        }
        return ints;
    }


    // ------------------------------------------------------------------------
    /** Splits a : separated string (like PATH) into its individual components.
     *  It especially handles Windows-style paths (c:/mydir1:d:/mydir2)
     *  correctly, and removes a trailing "/" which can cause a problem with
     *  windows' stat function.
     *  \param path The string to split.
     */
    std::vector<std::string> splitPath(const std::string& path)
    {
        try
        {
            std::vector<std::string> dirs=StringUtils::split(path,':');
            for(int i=(int)dirs.size()-1; i>=0; i--)
            {
                // Remove '/' at the end of paths, since this can cause
                // problems with windows when using stat()
                while(dirs[i].size()>=1 && dirs[i][dirs[i].size()-1]=='/')
                {
                    dirs[i]=dirs[i].substr(0, dirs[i].size()-1);
                }
                // remove empty entries
                if(dirs[i].size()==0)
                {
                    dirs.erase(dirs.begin()+i);
                    continue;
                }
            }   // for i
#ifdef WIN32
            // Handle filenames like d:/dir, which becomes ["d","/dir"]
            for(int i=(int)dirs.size()-1; i>=0; i--)
            {
                if(dirs[i].size()>1) continue;
                if(i==(int)dirs.size()-1)    // last element
                {
                    dirs[i]+=":";      // turn "c" back into "c:"
                }
                else
                {
                    dirs[i]+=":"+dirs[i+1]; // restore "d:/dir" back
                    dirs.erase(dirs.begin()+i+1);
                }
            }   // for i
#endif
            return dirs;
        }
        catch (std::exception& e)
        {
            (void)e;  // avoid warning about unused variable
            Log::fatal("StringUtils",
                "Fatal error in splitPath : %s @ line %i: '%s'.",
                        __FILE__, __LINE__, path.c_str());
        }
        return std::vector<std::string>();
    }   // splitPath

    // ------------------------------------------------------------------------
    std::string insertValues(const std::string &s,
                             std::vector<std::string>& all_vals)
    {
        try
        {
            std::vector<std::string> sv = StringUtils::split(s, '%', true);
            std::string new_string="";

            unsigned int insertValID = 0;

            const unsigned int item_count = (int)sv.size();
            for (unsigned int i=0; i<item_count; i++)
            {
                if(sv[i][0] != '%')
                {
                    new_string += sv[i];
                }
                else
                {
                    if(sv[i][1]=='s' || sv[i][1]=='d' || sv[i][1]=='i' ||
                       sv[i][1]=='f' || sv[i][1]=='u')
                    {
                        if (insertValID >= all_vals.size())
                        {
                            Log::warn("StringUtils",
                                      "insertValues: "
                                      "Invalid number of arguments in '%s'.",
                                      s.c_str());
                            new_string += "??" + sv[i].substr(2);
                        }
                        else
                        {
                            new_string += all_vals[insertValID]
                                        + sv[i].substr(2);
                        }
                        insertValID++;
                    }
                    else if(sv[i][1]>='0' && sv[i][1]<= '9')
                    {
                        const unsigned int index = sv[i][1] - '0';
                        if (index >= all_vals.size())
                        {
                            Log::warn("StringUtils", "insertValues: "
                                      " Invalid argument index in '%s' "
                                      "for %i.", s.c_str(), index);
                            new_string += "??" + sv[i].substr(2);
                        }
                        else
                        {
                            new_string += all_vals[index] + sv[i].substr(2);
                        }
                    }
                    else
                    {
                        new_string += sv[i];
                    }
                }
            }
            return new_string;
        }
        catch (std::exception& e)
        {
            (void)e;  // avoid warning about unused variable
            Log::fatal("StringUtils",
                       "Fatal error in insertValues(std::string) : %s @ "
                       "line %i: '%s'", __FILE__, __LINE__, s.c_str());
        }
        return "";
    }

    // ------------------------------------------------------------------------
    irr::core::stringw insertValues(const irr::core::stringw &s,
                                    std::vector<irr::core::stringw>& all_vals)
    {
        try
        {
            unsigned int insertValID = 0;

            const std::vector<irr::core::stringw> sv =
                                              StringUtils::split(s, '%', true);

            irr::core::stringw new_string="";

            const unsigned int size = (int)sv.size();
            for (unsigned int i=0; i<size; i++)
            {
                if(sv[i][0] != '%')
                {
                    new_string += sv[i];
                }
                else
                {
                    if (sv[i][1]=='s' || sv[i][1]=='d' || sv[i][1]=='i' ||
                        sv[i][1]=='f' || sv[i][1]=='u')
                    {
                        if (insertValID >= all_vals.size())
                        {
                            Log::warn("StringUtils", "insertValues: "
                                      "Invalid number of arguments in '%s'\n",
                                      irr::core::stringc(s.c_str()).c_str());
                            new_string += "??";
                            new_string += sv[i].subString(2, sv[i].size()-2);
                        }
                        else
                        {
                            new_string += all_vals[insertValID].c_str();
                            new_string += sv[i].subString(2, sv[i].size()-2);
                        }
                        insertValID++;
                    }
                    else if(irr::core::isdigit(sv[i][1]))
                    {
                        irr::core::stringw rest =
                                            sv[i].subString(2, sv[i].size()-2);
                        int delta = 0;

                        if (sv[i].size() >= 4 && sv[i][2]=='$')
                        {
                            rest = sv[i].subString(4, sv[i].size()-4);
                            delta = -1;
                        }

                        const unsigned int index =
                                 irr::core::stringc(sv[i].c_str()).c_str()[1]
                                 - '0' + delta;
                        if (index >= all_vals.size())
                        {
                            Log::warn("StringUtils", "insertValues: "
                                      "Invalid argument ID in '%s' : %i\n",
                                      irr::core::stringc(s.c_str()).c_str(),
                                      index);
                            new_string += "??";
                            new_string += rest;
                        }
                        else
                        {
                            new_string += all_vals[index] + rest;
                        }
                    }
                    else
                    {
                        new_string+=sv[i];
                    }
                }
            }
            return new_string;
        }
        catch (std::exception& e)
        {
            (void)e;  // avoid warning about unused variable
            Log::fatal("StringUtils",
                       "Fatal error in insertValues(stringw) : %s @ line %i.",
                       __FILE__, __LINE__);
        }
        return "";
    }

    // ------------------------------------------------------------------------
    /** Returns the time (in seconds) as string, based on ticks. */
    std::string ticksTimeToString(int ticks)
    {
        return timeToString(stk_config->ticks2Time(ticks));
    }   // ticksTimeToString(ticks)

    // ------------------------------------------------------------------------
    /** Converts a time in seconds into a string of the form mm:ss.hhh (minutes,
     *  seconds, milliseconds)
     *  \param time Time in seconds.
     *  \param precision The number of seconds decimals - 3 to display ms, default 2
     */
    std::string timeToString(float time, unsigned int precision, bool display_minutes_if_zero, bool display_hours)
    {
        //Time more detailed than ms are mostly meaningless
        if (precision > 3)
            precision = 3;

        int int_time;
        int precision_power = 1;

        for (unsigned int i=0;i<precision;i++)
        {
            precision_power *=10;
        }

        float fprecision_power = (float) precision_power;

        bool negative_time = (time < 0.0f);

        // If the time is negative, make it positve
        // And add a "-" later
        if (negative_time) time *= -1.0f;

        // cast to int truncates the value,
        // so add 0.5f to get the closest int

        int_time = (int)(time*fprecision_power+0.5f);

        // Avoid problems if time is negative or way too large (which
        // should only happen if something is broken in a track elsewhere,
        // and an incorrect finishing time is estimated.
        if(int_time<0)
        {
            std::string final_append;
            if (precision == 3)
                final_append = ".000";
            else if (precision == 2)
                final_append = ".00";
            else if (precision == 1)
                final_append = ".0";
            else
                final_append = "";
            // concatenate the strings with +
            if (display_hours)
                return (std::string("00:00:00") + final_append);
            else if (display_minutes_if_zero)
                return (std::string("00:00") + final_append);
            else
                return (std::string("00") + final_append);
        }
        else if((int_time >= 60*60*precision_power && !display_hours) ||
                int_time >= 100*60*60*precision_power)
        {
            std::string final_append;
            if (precision == 3)
                final_append = ".999";
            else if (precision == 2)
                final_append = ".99";
            else if (precision == 1)
                final_append = ".9";
            else
                final_append = "";
            // concatenate the strings with +
            if (display_hours)
                return (std::string("99:59:59") + final_append);
            else
                return (std::string("59:59") + final_append);
        }

        // Principle of the computation in pseudo-code
        // 1) Divide by (current_time_unit_duration/next_smaller_unit_duration)
        //    (1 if no smaller)
        // 2) Apply modulo (next_bigger_time_unit_duration/current_time_unit_duration)
        //    (no modulo if no bigger)
        int subseconds = int_time % precision_power;
        int_time       = int_time/precision_power;
        int sec        = int_time % 60;
        int_time       = int_time/60;
        int min        = int_time % 60;
        int_time       = int_time/60;
        int hours      = int_time;

        // Convert the times to string and add the missing zeroes if any

        std::string s_hours = toString(hours);
        if (hours < 10)
            s_hours = std::string("0") + s_hours;
        std::string s_min = toString(min);
        if (min < 10)
            s_min = std::string("0") + s_min;
        std::string s_sec = toString(sec);
        if (sec < 10)
            s_sec = std::string("0") + s_sec;
        std::string s_subsec = toString(subseconds);

        // If subseconds is 0 ; it is already in the string,
        // so skip one step
        for (unsigned int i=1;i<precision;i++)
        {
            precision_power = precision_power/10;
            if (subseconds < precision_power)
                s_subsec = std::string("0") + s_subsec;
        }

        std::string s_neg = "";

        if(negative_time)
            s_neg = "-";

        std::string s_hours_min_and_sec = s_sec;
        if (display_minutes_if_zero || min > 0 || display_hours)
            s_hours_min_and_sec = s_min + std::string(":") + s_sec;
        if (display_hours)
            s_hours_min_and_sec = s_hours + std::string(":") + s_hours_min_and_sec;
        if (precision == 0)
            return (s_neg + s_hours_min_and_sec);
        else
            return (s_neg + s_hours_min_and_sec + std::string(".") + s_subsec);
    }   // timeToString

    // ------------------------------------------------------------------------
    /** Shows a increasing number of dots.
      * \param interval A float representing the time it takes to add a new dot
      * \param max_dots The number of dots used. Defaults to 3.
      */
    irr::core::stringw loadingDots(float interval, int max_dots)
    {
        int nr_dots = int(floor(StkTime::getRealTime() / interval))
                    % (max_dots + 1);
        return irr::core::stringw((std::string(nr_dots, '.') +
                                   std::string(max_dots - nr_dots, ' ')).c_str());
    }   // loadingDots

    // ------------------------------------------------------------------------
    /** Returns the string given with loadingDots appended. A simple
     *  convenience function to type less in calls.
     *  \parameter s The string to which the loading dots are appended.
     */
    irr::core::stringw loadingDots(const irr::core::stringw& s)
    {
        return s + loadingDots();
    }   // loadingDots

    // ------------------------------------------------------------------------
    /** Replaces values in a string.
     * \param other string in which to replace stuff
     * \param from  pattern to remove from the string
     * \param to    pattern to insert instead
     * \return      a string with all occurrences of \c from replaced by
     *              occurrences of \c to
     */
    std::string replace(const std::string& other, const std::string& from,
                        const std::string& to)
    {
        std::string wip = other;


        while (true)
        {
            const int pos = (int) wip.find(from);
            if (pos == -1)
            {
                return wip;
            }
            wip.replace(pos, from.size(), to.c_str(), to.size());
        }

    }

    // ------------------------------------------------------------------------
    /** Converts ASCII text with XML entities (e.g. &x00;) to unicode strings
     *  \param input The input string which should be decoded.
     *  \return A irrlicht wide string with unicode characters.
     */
    irr::core::stringw xmlDecode(const std::string& input)
    {
        std::u32string output;
        std::string entity;
        bool isHex = false;

        enum
        {
            NORMAL,
            ENTITY_PREAMBLE,
            ENTITY_BODY
        } state = NORMAL;

        for (unsigned int n=0; n<input.size(); n++)
        {
            switch (state)
            {
                case NORMAL:
                    if (input[n] == '&')
                    {
                        state = ENTITY_PREAMBLE;
                        entity = "";
                        isHex = false;
                    }
                    else
                    {
                        output += char32_t(input[n]);
                    }
                    break;

                case ENTITY_PREAMBLE:
                    if (input[n] != '#')
                    {
                        output += U"&";
                        output += char32_t(input[n]);
                        // This is actually an error, but we can't print a
                        // warning here: irrxml replaces &amp; in (e.g.)
                        // attribute values with '&' - so we can have a single
                        // '&' that is correct. On the other hand we have to
                        // convert esp. &# hex codes, since we use this to
                        // encode special characters, but irrlicht does not
                        // decode those.
                        state = NORMAL;
                    }
                    else
                    {
                        state = ENTITY_BODY;
                    }
                    break;

                case ENTITY_BODY:
                    if (input[n] == 'x' && entity.size() == 0)
                    {
                        isHex = true;
                    }
                    else if (input[n] == ';')
                    {
                        int c;

                        const char* format = (isHex ? "%x" : "%i");
                        if (sscanf(entity.c_str(), format, &c) == 1)
                        {
                            output += char32_t(c);
                        }
                        else
                        {
                            Log::warn("StringUtils", "non-numeric HTML "
                                      "entity not supported in '%s'.",
                                      input.c_str());
                        }
                        state = NORMAL;
                    }
                    else
                    {
                        entity += char32_t(input[n]);
                    }
                    break;
            }
        }
        if (sizeof(wchar_t) == 2)
        {
            return utf32ToWide(output);
        }
        else
        {
            const wchar_t* ptr = (const wchar_t*)output.c_str();
            return irr::core::stringw(ptr);
        }
    }   // xmlDecode

    // ------------------------------------------------------------------------
    /** Converts a unicode string to plain ASCII using XML entites (e.g. &x00;)
     *  \param s The input string which should be encoded.
     *  \return A std:;string with ASCII characters.
     */
    std::string xmlEncode(const irr::core::stringw &s)
    {
        std::ostringstream output;
        const std::u32string& utf32 = wideToUtf32(s);
        for(unsigned i = 0; i < utf32.size(); i++)
        {
            if (utf32[i] >= 128 || utf32[i] == '&' || utf32[i] == '<' ||
                utf32[i] == '>' || utf32[i] == '\"' || utf32[i] == ' ')
            {
                output << "&#x" << std::hex << std::uppercase << utf32[i] << ";";
            }
            else
            {
                irr::c8 c = (char)(utf32[i]);
                output << c;
            }
        }
        return output.str();
    }   // xmlEncode

    // ------------------------------------------------------------------------

    std::string wideToUtf8(const wchar_t* input)
    {
        std::vector<char> utf8line;
        try
        {
            if (sizeof(wchar_t) == 2)
            {
                utf8::utf16to8(input, input + wcslen(input),
                    back_inserter(utf8line));
            }
            else if (sizeof(wchar_t) == 4)
            {
                utf8::utf32to8(input, input + wcslen(input),
                    back_inserter(utf8line));
            }
            utf8line.push_back(0);
        }
        catch (std::exception& e)
        {
            utf8line.push_back(0);
            Log::error("StringUtils",
                "wideToUtf8 error: %s, incompleted string: %s", e.what(),
                utf8line.data());
        }
        return std::string(&utf8line[0]);
    }   // wideToUtf8

    // ------------------------------------------------------------------------
    /** Converts the irrlicht wide string to an utf8-encoded std::string.
     */
    std::string wideToUtf8(const irr::core::stringw& input)
    {
        return wideToUtf8(input.c_str());
    }   // wideToUtf8

    // ------------------------------------------------------------------------
    /** Converts the irrlicht wide string to an utf8-encoded std::string. */
    irr::core::stringw utf8ToWide(const char* input)
    {
        std::vector<wchar_t> wchar_line;
        try
        {
            if (sizeof(wchar_t) == 2)
            {
                utf8::utf8to16(input, input + strlen(input),
                    back_inserter(wchar_line));
            }
            else if (sizeof(wchar_t) == 4)
            {
                utf8::utf8to32(input, input + strlen(input),
                    back_inserter(wchar_line));
            }
            wchar_line.push_back(0);
        }
        catch (std::exception& e)
        {
            wchar_line.push_back(0);
            Log::error("StringUtils",
                "wideToUtf8 error: %s, input string: %s", e.what(), input);
        }
        return irr::core::stringw(&wchar_line[0]);
    }   // utf8ToWide

    // ------------------------------------------------------------------------
    /** Converts a utf8-encoded std::string into an irrlicht wide string. */
    irr::core::stringw utf8ToWide(const std::string &input)
    {
        return utf8ToWide(input.c_str());
    }   // utf8ToWide

    /* This function checks if a char is suitable to break lines.
     * Currently a copy of the function found at irrlicht/include/utfwrapping.h */
    bool breakable (wchar_t c)
    {
	    if ((c > 12287 && c < 40960) || //Common CJK words
	    	(c > 44031 && c < 55204)  || //Hangul
	    	(c > 63743 && c < 64256)  || //More Chinese
	    	c == 45 || c == 173 || c == L' ' || //Hypen, soft hyphen and white space
	    	c == 47 || c == 92) //Slash and blackslash
	    	return true;
	    return false;
    } // breakable

    // ------------------------------------------------------------------------
    irr::core::stringw utf32ToWide(const std::u32string& input)
    {
        std::vector<wchar_t> wchar_line;
        try
        {
            if (sizeof(wchar_t) == 2)
            {
                const uint32_t* chars = (const uint32_t*)input.c_str();
                utf8::utf32to16(chars, chars + input.size(),
                    back_inserter(wchar_line));
            }
            else if (sizeof(wchar_t) == sizeof(char32_t))
            {
                wchar_line.resize(input.size());
                memcpy(wchar_line.data(), input.c_str(),
                    input.size() * sizeof(char32_t));
            }
            wchar_line.push_back(0);
        }
        catch (std::exception& e)
        {
            wchar_line.push_back(0);
            Log::error("StringUtils", "utf32ToWide error: %s", e.what());
        }
        return irr::core::stringw(&wchar_line[0]);
    }   // utf32ToWide

    // ------------------------------------------------------------------------
    std::u32string wideToUtf32(const irr::core::stringw& input)
    {
        std::u32string utf32_line;
        try
        {
            if (sizeof(wchar_t) != sizeof(char32_t))
            {
                const uint16_t* chars = (const uint16_t*)input.c_str();
                utf8::utf16to32(chars, chars + input.size(),
                    back_inserter(utf32_line));
            }
            else if (sizeof(wchar_t) == sizeof(char32_t))
                utf32_line = (const char32_t*)input.c_str();
        }
        catch (std::exception& e)
        {
            Log::error("StringUtils", "wideToUtf32 error: %s", e.what());
        }
        return utf32_line;
    }   // wideToUtf32
} // namespace StringUtils

/* EOF */
