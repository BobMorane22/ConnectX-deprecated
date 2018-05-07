#include <algorithm>
#include <cstdio>

#include <unistd.h>
#include <linux/limits.h>

#include <cxutil/include/Assertion.h>

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
