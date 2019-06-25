#pragma once

#include "IChainLogging.h"
#include "Logger.h"

namespace cxlog
{

class ChainLogger : public Logger,
                    public IChainLogging
{
public:

    void log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override = 0;

    void setSucessor(std::unique_ptr<ILogger>&& p_sucessor) override;
    bool hasSucessor() const override;

protected:

    std::unique_ptr<ILogger> m_successor;  // Next logger, if any.

private:
    VerbosityLevel m_verbosityLevel{VerbosityLevel::NONE};  // Actual verbosity level.
};

} // namespace cxlog