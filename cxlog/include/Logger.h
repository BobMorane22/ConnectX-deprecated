#pragma once

#include <memory>

#include "ILogger.h"

namespace cxlog
{

class Logger : public ILogger
{
public:

    void log( const VerbosityLevel p_verbosityLevel,
              const std::string&   p_fileName,
              const std::string&   p_functionName,
              const size_t         p_lineNumber,
              const std::string&   p_message ) override = 0;

    void           setVerbosityLevel(const VerbosityLevel p_verbosityLevel) override;
    VerbosityLevel verbosityLevel() const override;

protected:

    std::unique_ptr<ILogger> m_successor;  // Next logger, if any.

private:
    VerbosityLevel m_verbosityLevel{VerbosityLevel::NONE};  // Actual verbosity level.
};

} // namespace cxlog
