#pragma once

#include <iostream>

#include "ILogTarget.h"

namespace cxlog
{

class StdLogTarget : public ILogTarget
{
public:

    void log(const std::string& p_message) override;

private:

    std::ostream& stdStream() const {return *m_stdStream;};

    std::ostream* m_stdStream{&std::cout};
};

} // namespace cxlog
