#pragma once

#include "IMessageFormatter.h"

namespace cxlog
{

class CSVMessageFormatter final : public IMessageFormatter
{
public:

    std::string formatHeaders() const override final;
    std::string formatMessage(const VerbosityLevel p_verbosityLevel,
                              const std::string& p_message) const override final;
};

} // namespace cxlog