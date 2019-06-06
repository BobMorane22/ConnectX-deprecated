#pragma once

#include <string>

#include "VerbosityLevel.h"

namespace cxlog
{

class IMessageFormatter
{
public:

    virtual ~IMessageFormatter() = default;

    virtual std::string formatHeaders() const = 0;
    virtual std::string formatMessage(const VerbosityLevel p_mode,
                                      const std::string& p_message) const = 0;
};

} // namespace cxlog