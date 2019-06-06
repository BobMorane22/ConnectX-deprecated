#pragma once

#include <memory>
#include <string>

#include "ILogTarget.h"
#include "VerbosityLevel.h"

namespace cxlog
{

class ILogger
{
public:
    virtual ~ILogger() = default;

    virtual void           log(const VerbosityLevel p_mode, const std::string& p_message) = 0;

    virtual void           setVerbosityLevel(const VerbosityLevel p_verbosityLevel) = 0;
    virtual VerbosityLevel verbosityLevel() const = 0;

    virtual void           setSucessor(std::unique_ptr<ILogger>&& p_sucessor) = 0;
    virtual bool           hasSucessor() const = 0;
};

} // namespace cxlog
