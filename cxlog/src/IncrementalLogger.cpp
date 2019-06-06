#include <cxinv/include/assertion.h>

#include "../include/IncrementalLogger.h"

cxlog::StringLogger::StringLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
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


void cxlog::StringLogger::log(const VerbosityLevel p_verbosityLevel, const std::string& p_message)
{
    if(!m_msgFormatter)
    {
        ASSERT_FALSE_MSG("No reference to a formatter.");

        return;
    }

    if(p_verbosityLevel > verbosityLevel() || verbosityLevel() == VerbosityLevel::NONE)
    {
        return;
    }

    // Create well formatted message:
    const std::string msg{m_msgFormatter->formatMessage(p_verbosityLevel, p_message)};

    if(!m_logTarget)
    {
        ASSERT_FALSE_MSG("No reference to a log target.");

        // Release formatter, no logging will be done after all:
        m_msgFormatter.reset(nullptr);

        return;
    }

    // Log it to the target:
    m_logTarget->log(msg);

    if(hasSucessor())
    {
        // Forward message to next logger:
        m_successor->log(p_verbosityLevel, p_message);
    }

    INVARIANT(m_msgFormatter != nullptr);
    INVARIANT(m_logTarget != nullptr);
}
