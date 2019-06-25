#include <memory.h>
#include <sstream>

#include <cxlog/include/ChainLogger.h>

// Constants:
const std::string BASIC_STRING_TO_LOG{"CSV logger test"};

const std::string FATAL_PREFIX  {"FATAL, "  };
const std::string ERROR_PREFIX  {"ERROR, "  };
const std::string WARNING_PREFIX{"WARNING, "};
const std::string INFO_PREFIX   {"INFO, "   };
const std::string DEBUG_PREFIX  {"DEBUG, "  };

const std::string _FILE_    {"File.cpp"};
const std::string _FUNCTION_{"nsp::function()"};
const size_t      _LINE_    {200};

const std::string SEPARATOR  {", "};
const std::string END_OF_LINE{"\n"};

const std::string EMPTY_STRING{std::string()};


// Testing utilities:
std::string generateLineToLog();
std::string fatalResult();
std::string errorResult();
std::string warningResult();
std::string infoResult();
std::string debugResult();
std::string headerLine();

std::unique_ptr<cxlog::ILogger> createCVSStringStreamLogger(std::ostringstream& p_stream,
                                                            const bool p_generateHeader = false);

std::unique_ptr<cxlog::ChainLogger> createCVSStringStreamChainLogger(std::ostringstream& p_stream,
                                                                     const bool p_generateHeader = false);