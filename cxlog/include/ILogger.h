#pragma once

#include <string>

#include "ILogTarget.h"
#include "VerbosityLevel.h"

namespace cxlog
{

class ILogger
{
public:
    virtual ~ILogger() = default;

    virtual void log(const VerbosityLevel p_verbosityLevel,
                     const std::string&   p_fileName,
                     const std::string&   p_functionName,
                     const size_t         p_lineNumber,
                     const std::string&   p_message) = 0;

    virtual void setVerbosityLevel(const VerbosityLevel p_verbosityLevel) = 0;
    virtual VerbosityLevel verbosityLevel() const = 0;
};

} // namespace cxlog