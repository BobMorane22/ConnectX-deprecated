#include "../include/VerbosityLevel.h"


bool cxlog::operator<(const VerbosityLevel p_first, const VerbosityLevel p_second)
{
    return static_cast<int>(p_first) < static_cast<int>(p_second);
}

bool cxlog::operator<=(const VerbosityLevel p_first, const VerbosityLevel p_second)
{
    return p_first < p_second || p_first == p_second;
}

bool cxlog::operator>(const VerbosityLevel p_first, const VerbosityLevel p_second)
{
    return static_cast<int>(p_first) > static_cast<int>(p_second);
}

bool cxlog::operator>=(const VerbosityLevel p_first, const VerbosityLevel p_second)
{
    return p_first > p_second || p_first == p_second;
}
