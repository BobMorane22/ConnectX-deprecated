#pragma once

#include "ITimestampFormatter.h"

namespace cxlog
{

enum class TimePrecision
{
    SECONDS      = 0,
    MILLISECONDS = 3,
    MICROSECONDS = 6,
    NANOSECONDS  = 9
};

class ISO8601TimestampFormatter : public ITimestampFormatter
{
public:

    ISO8601TimestampFormatter(const TimePrecision p_precision);

    ~ISO8601TimestampFormatter() override;

    std::string formatTimestamp() const override;

private:

    const bool m_precisionNeeded{false};
    const TimePrecision m_precision{TimePrecision::SECONDS};
};

} // namespace cxlog