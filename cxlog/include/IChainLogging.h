#pragma once

#include <memory>

#include "ILogger.h"

namespace cxlog
{

class IChainLogging
{
public:

    virtual void setSucessor(std::unique_ptr<ILogger>&& p_sucessor) = 0;
    virtual bool hasSucessor() const = 0;
};

} // namespace cxlog