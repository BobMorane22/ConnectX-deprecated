/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
 *
 * This file is part of Connect X.
 *
 * Connect X is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Connect X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************************************/

/***********************************************************************************************//**
 * @file    util.cpp
 * @author  Eric Poirier
 * @date    July 2018
 * @version 1.0
 *
 * Temporary utilities file (to be refactored once the UI is more stable).
 *
 **************************************************************************************************/

#include <algorithm>
#include <cstdio>
#include <iomanip>

#include <unistd.h>
#include <linux/limits.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/Color.h>

#include "../include/util.h"

// Temporary file for dev utilities. To be factored out when the GUI
// code will be more mature...

std::string currentExecutablePath(const bool p_pathOnly)
{
    // Get the symlink path to the current exexutable:
    char symlinkToCurrentExec[32];
    sprintf(symlinkToCurrentExec, "/proc/%d/exe", getpid());

    // Read the symlink:
    char readPath[PATH_MAX];

    const ssize_t nbBytesRead{readlink(symlinkToCurrentExec,
                                       readPath,
                                       PATH_MAX)};

    // Make sure there is no overflow in path length from readlink:
    const ssize_t nbBytesInPath{std::min(nbBytesRead,
                                static_cast<ssize_t>(PATH_MAX - 1))};

    // If something has been read, the 'end of string' character must be added
    // before the read path can be manipulated:
    if(nbBytesInPath >= 0)
    {
        readPath[nbBytesInPath] = '\0';
    }

    // Make sure file exists:
    CX_ASSERT_MSG(access(readPath, F_OK) != -1, "The executable path does not exist.")

    std::string pathToCurrentExecutable(readPath);

    if(p_pathOnly)
    {
        // Only the path to directory is wanted, so the executable name is
        // removed from the path:
        const size_t indexOfDirectoryDelim{pathToCurrentExecutable.find_last_of("/")};

        CX_ASSERT_MSG(indexOfDirectoryDelim != std::string::npos, "Error while trying to get the directory containing the current running executable.");

        pathToCurrentExecutable = pathToCurrentExecutable.substr(0, indexOfDirectoryDelim);
    }

    return pathToCurrentExecutable;
}


std::string cx::ui::buildGdkColorString(const cxutil::Color& p_localColor)
{
    std::ostringstream os;

    os << "rgba(" << unsigned(p_localColor.r())
       << ", "    << unsigned(p_localColor.g())
       << ", "    << unsigned(p_localColor.b())
       << ", "    << p_localColor.alpha()
       << ")";

    return os.str();
}


std::string cx::ui::deprecated::buildGdkColorString(const cxutil::Color& p_localColor)
{
    using namespace std;

    ostringstream os;

    os << "#"
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.r())
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.g())
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.b());

    return os.str();
}


cxutil::Color cx::ui::convertToLocalColor(const Gdk::RGBA& p_gdkColor)
{
    const uint8_t red   {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_red_u()   >> 8) & 0xFF)};
    const uint8_t green {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_green_u() >> 8) & 0xFF)};
    const uint8_t blue  {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_blue_u()  >> 8) & 0xFF)};
    const uint8_t alpha {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_alpha_u() >> 8) & 0xFF)};

    return cxutil::Color{cxutil::RGBA{red, green, blue, alpha}};
}


cxutil::Color cx::ui::deprecated::convertToLocalColor(const Gdk::Color& p_gdkColor)
{
    const uint8_t red   {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_red()   >> 8) & 0xFF)};
    const uint8_t green {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_green() >> 8) & 0xFF)};
    const uint8_t blue  {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_blue()  >> 8) & 0xFF)};

    return cxutil::Color{cxutil::RGBA{red, green, blue, 255}};
}


Gdk::RGBA cx::ui::convertToGdkRGBA(const cxutil::Color& p_localColor)
{
    return Gdk::RGBA{cx::ui::buildGdkColorString(p_localColor)};
}


Gdk::Color cx::ui::deprecated::convertToGdkColor(const cxutil::Color& p_localColor)
{
    return Gdk::Color{cx::ui::deprecated::buildGdkColorString(p_localColor)};
}
