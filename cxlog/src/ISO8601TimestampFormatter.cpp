#include <chrono>
#include <iomanip>
#include <sstream>

#include <cxinv/include/assertion.h>

#include "../include/ISO8601TimestampFormatter.h"

using namespace std::chrono;

namespace
{

double countFromPrecision(const system_clock::time_point& p_timePoint,
                          const cxlog::TimePrecision p_precision)

{
    switch(p_precision)
    {
        case cxlog::TimePrecision::MILLISECONDS:
        {
            const auto milli{duration_cast<milliseconds>(p_timePoint.time_since_epoch()) % 1000};

            return milli.count();
        }
        case cxlog::TimePrecision::MICROSECONDS:
        {
            const auto micro{duration_cast<microseconds>(p_timePoint.time_since_epoch()) % 1000000};

            return micro.count();
        }
        case cxlog::TimePrecision::NANOSECONDS:
        {
            const auto nano{duration_cast<nanoseconds>(p_timePoint.time_since_epoch()) % 1000000000};

            return nano.count();
        }
    }

    ASSERT_FALSE_MSG("Unknown precision!");

    return 0.0;
}

} // namespace

cxlog::ISO8601TimestampFormatter::ISO8601TimestampFormatter(const cxlog::TimePrecision p_precision)
 : m_precision{p_precision}
 , m_precisionNeeded{p_precision != TimePrecision::SECONDS ? true : false}
{
}

cxlog::ISO8601TimestampFormatter::~ISO8601TimestampFormatter() = default;

// yyyy-mm-ddThh:mm:ss[.mmm]
std::string cxlog::ISO8601TimestampFormatter::formatTimestamp() const
{
    // Get current time:
    const auto now{system_clock::now()};

    // Get broken down time:
    const auto timer{system_clock::to_time_t(system_clock::now())};
    const auto brokenTime{*(std::localtime(&timer))};

    // Format:
    std::ostringstream oss;

    oss << std::put_time(&brokenTime, "%Y-%m-%dT%H:%M:%S");

    if(m_precisionNeeded)
    {
        oss.precision(0);

        oss << '.'
            << std::setfill('0')
            << std::setw(static_cast<std::streamsize>(m_precision))
            << std::fixed
            << countFromPrecision(now, m_precision);
    }

    return oss.str();
}