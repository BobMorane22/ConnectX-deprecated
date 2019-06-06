#pragma once

#include "IMessageFormatter.h"

#include "Logger.h"

namespace cxlog
{

class StringLogger : public Logger
{
public:

    StringLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                 std::unique_ptr<ILogTarget>&&        p_logTarget,
                 bool                                 p_addHeader = false);

    void log(const VerbosityLevel p_mode, const std::string& p_message) override;

private:

    std::unique_ptr<IMessageFormatter> m_msgFormatter;
    std::unique_ptr<ILogTarget>        m_logTarget;
};

} // namespace cxlog