#pragma once

#include <string>

namespace cxlog
{

class ILogTarget
{
public:
    virtual ~ILogTarget() = default;

    virtual void log(const std::string& p_message) = 0;
};

} // namespace cxlog