#pragma once

#include <fstream>

#include "ILogTarget.h"

namespace cxlog
{

class FileLogTarget : public ILogTarget
{
public:

    FileLogTarget(const std::string& p_logFileName);

    void log(const std::string& p_message) override;

private:

    std::ofstream& fileStream() {return m_fileStream;};

    std::ofstream m_fileStream;
};

} // namespace cxlog
