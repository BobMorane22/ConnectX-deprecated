#include <memory.h>
#include <sstream>

#include <cxlog/include/ILogger.h>

// Constants:
const std::string BASIC_STRING_TO_LOG{"CSV logger test"};

const std::string FATAL_PREFIX  {"FATAL, "  };
const std::string ERROR_PREFIX  {"ERROR, "  };
const std::string WARNING_PREFIX{"WARNING, "};
const std::string INFO_PREFIX   {"INFO, "   };
const std::string DEBUG_PREFIX  {"DEBUG, "  };

const std::string END_OF_LINE{"\n"};


// Testing utilities:
std::string generateLineToLog();
std::string fatalResult();
std::string errorResult();
std::string warningResult();
std::string infoResult();
std::string debugResult();

std::unique_ptr<cxlog::ILogger> createCVSStringStreamLogger(std::ostringstream& p_stream);
