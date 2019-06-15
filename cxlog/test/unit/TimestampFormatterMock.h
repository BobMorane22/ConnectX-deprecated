#pragma once

#include <cxlog/include/ITimestampFormatter.h>

class TimestampFormatterMock : public cxlog::ITimestampFormatter
{

public:

    ~TimestampFormatterMock() override = default;

    std::string formatTimestamp() const override {return "AAAA:MM:JJTHH:MM:SS:mm";}
};