#pragma once

namespace cxlog
{

enum class VerbosityLevel
{
    NONE    = 0,   // Do no logging.
    FATAL   = 1,   // System can't recover
    ERROR   = 2,   // System can recover, but something is wrong
    WARNING = 3,   // Warn about something unexpected that is not an error
                   // but that could lead to errors.
    INFO    = 4,   // General information that has no impact on the system.
    DEBUG   = 5    // Debug information, for developpers only.
};

bool operator<(const VerbosityLevel p_first, const VerbosityLevel p_second);
bool operator<=(const VerbosityLevel p_first, const VerbosityLevel p_second);
bool operator>(const VerbosityLevel p_first, const VerbosityLevel p_second);
bool operator>=(const VerbosityLevel p_first, const VerbosityLevel p_second);

} // namespace cxlog