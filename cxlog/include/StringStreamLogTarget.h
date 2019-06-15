#pragma once

#include <sstream>

#include "ILogTarget.h"

namespace cxlog
{

class StringStreamLogTarget : public ILogTarget
{
public:

    StringStreamLogTarget(std::ostringstream& p_stringStream);

    void log(const std::string& p_message) override;

private:

    std::ostringstream& stringStream() const {return m_stringStream;};

    std::ostringstream& m_stringStream;
};

} // namespace cxlog