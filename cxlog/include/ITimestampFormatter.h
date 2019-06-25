#pragma once

#include <string>

namespace cxlog
{

class ITimestampFormatter
{
public:
    virtual ~ITimestampFormatter(){}

    virtual std::string formatTimestamp() const = 0;
};

} // namespace cxlog