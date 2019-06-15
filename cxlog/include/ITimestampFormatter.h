#pragma once

#include <string>

namespace cxlog
{

class ITimestampFormatter
{
public:
    virtual ~ITimestampFormatter() = default;

    virtual std::string formatTimestamp() const = 0;
};

} // namespace cxlog
