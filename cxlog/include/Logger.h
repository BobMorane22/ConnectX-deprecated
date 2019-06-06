#pragma once

#include "ILogger.h"

namespace cxlog
{

class Logger : public ILogger
{
public:

    void log(const VerbosityLevel p_mode, const std::string& p_message) override = 0;

    void setVerbosityLevel(const VerbosityLevel p_verbosityLevel) override;
    VerbosityLevel verbosityLevel() const override;

    void setSucessor(std::unique_ptr<ILogger>&& p_sucessor);
    bool hasSucessor() const;

protected:

    std::unique_ptr<ILogger> m_successor;  // Next logger, if any.

private:
    VerbosityLevel m_verbosityLevel{VerbosityLevel::NONE};  // Actual verbosity level.
};

} // namespace cxlog