#pragma once

#include "IMessageFormatter.h"

#include "Logger.h"

namespace cxlog
{

class IncrementalLogger : public Logger
{
public:

    IncrementalLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                      std::unique_ptr<ILogTarget>&&        p_logTarget,
                      bool                                 p_addHeader = false);

    void log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override;

private:

    std::unique_ptr<IMessageFormatter> m_msgFormatter;
    std::unique_ptr<ILogTarget>        m_logTarget;
};

} // namespace cxlog