#pragma once

#include <memory>

#include "IMessageFormatter.h"
#include "ITimestampFormatter.h"

namespace cxlog
{

class CSVMessageFormatter final : public IMessageFormatter
{
public:

    CSVMessageFormatter(std::unique_ptr<ITimestampFormatter>&& p_timeFormatter);

    ~CSVMessageFormatter() override;

    std::string formatHeaders() const override final;

    virtual std::string formatMessage(const VerbosityLevel p_verbosityLevel,
                                      const std::string&   p_fileName,
                                      const std::string&   p_functionName,
                                      const size_t         p_lineNumber,
                                      const std::string&   p_message) const override final;

private:

    std::unique_ptr<ITimestampFormatter> m_timeFormatter;
};

} // namespace cxlog
