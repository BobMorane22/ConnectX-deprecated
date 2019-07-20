#include <cxinv/include/assertion.h>

#include "../include/IncrementalLogger.h"

cxlog::IncrementalLogger::IncrementalLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                                            std::unique_ptr<ILogTarget>&&        p_logTarget,
                                            bool                                 p_addHeader)
 : m_msgFormatter{std::move(p_msgFormatter)}
 , m_logTarget{std::move(p_logTarget)}
{
    // We take member variables as preconditions because parameters
    // have been moved away:
    PRECONDITION(m_msgFormatter != nullptr);
    PRECONDITION(m_logTarget != nullptr);

    if(m_msgFormatter && m_logTarget && p_addHeader)
    {
        // Log the header:
        m_logTarget->log(m_msgFormatter->formatHeaders());
    }

    INVARIANT(m_msgFormatter != nullptr);
    INVARIANT(m_logTarget != nullptr);
}


void cxlog::IncrementalLogger::log(const VerbosityLevel p_verbosityLevel,
                                   const std::string&   p_fileName,
                                   const std::string&   p_functionName,
                                   const size_t         p_lineNumber,
                                   const std::string&   p_message)
{
    if(!m_msgFormatter)
    {
        ASSERT_ERROR_MSG("No reference to a formatter.");

        return;
    }

    if(p_verbosityLevel > verbosityLevel() ||
        p_verbosityLevel == VerbosityLevel::NONE ||
        verbosityLevel() == VerbosityLevel::NONE)
    {
        return;
    }

    // Create well formatted message:
    const std::string msg{m_msgFormatter->formatMessage(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message)};

    if(!m_logTarget)
    {
        ASSERT_ERROR_MSG("No reference to a log target.");

        // Release formatter, no logging will be done after all:
        m_msgFormatter.reset(nullptr);

        return;
    }

    // Log it to the target:
    m_logTarget->log(msg);

    INVARIANT(m_msgFormatter != nullptr);
    INVARIANT(m_logTarget != nullptr);
}
