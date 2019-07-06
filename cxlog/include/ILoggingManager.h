#pragma once

#include <string>

#include "VerbosityLevel.h"

namespace cxlog
{

class ILoggingManager
{
public:
    virtual ~ILoggingManager() = default;

    virtual void setVerbosityLevel(const cxlog::VerbosityLevel p_level) = 0;
    virtual VerbosityLevel verbosityLevel() const = 0;

    virtual void log(const VerbosityLevel p_verbosityLevel,
                     const std::string&   p_fileName,
                     const std::string&   p_functionName,
                     const size_t         p_lineNumber,
                     const std::string&   p_message) = 0;
};

} // namespace cxlog