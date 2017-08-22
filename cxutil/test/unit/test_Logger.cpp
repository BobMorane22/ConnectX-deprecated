/***************************************************************************************************
 * 
 * Copyright (C) 2017 Connect X team
 *
 * This file is part of Connect X.
 *
 * Connect X is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Connect X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************************************/

/***********************************************************************************************//**
 * @file    test_Logger.cpp
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Unit tests for a the Logger class.
 *
 **************************************************************************************************/


#include <regex>
#include <sstream>

#include <gtest/gtest.h>

#include <include/Logger.h>

using namespace cxutil;

class LoggerTests : public::testing::Test
{
public:
    LoggerTests()
    {
        std::string separator     {"\\t"                          };
        std::string endOfLine     {"\\n"                          };
        std::string lineNumber    {"(\\d)+"                       };
        std::string executionTime {"(\\d)+\\.(\\d)+"              };    /* "x.y" (where x and y = d...)         */
        std::string date          {"20\\d\\d/\\d(\\d)?/\\d(\\d)?" };    /* "20ab/x/y" (where x and y = d or dd) */
        std::string time          {"\\d(\\d)?:\\d(\\d)?:\\d(\\d)?"};    /* "x:y:z (where x, y and z = d or dd)  */
        std::string info          {"INFO\\s\\s\\s\\s:"            };    /* "INFO    :"                          */
        std::string warning       {"WARNING\\s:"                  };    /* "WARNING :"                          */
        std::string error         {"ERROR\\s\\s\\s:"              };    /* "ERROR   :"                          */
        std::string debug         {"DEBUG\\s\\s\\s:"              };    /* "DEBUG   :"                          */
        std::string message       {"(.)+"                         };

        std::string header        {"(" + info + "|" + warning + "|" + error + "|" + debug + ")"};

        std::string oneLine       {lineNumber    + separator + 
                                   executionTime + separator + 
                                   date          + separator + 
                                   time          + separator + 
                                   header        + separator +
                                   message       + endOfLine   };
        
        t_logFileFormat = "(" + oneLine + oneLine + oneLine + oneLine + ")+";
    };

    std::regex logFileFormat() const {return t_logFileFormat;}
    void silenceCout() const {std::cout.setstate(std::ios_base::failbit);};

private:
    std::regex t_logFileFormat;
};

TEST_F(LoggerTests, ConstructorWithParameter)
{
    std::ostringstream t_logStream;
    std::string messageInfo    {"Beginning of unit test..."};
    std::string messageWarning {"Something is weird..."};
    std::string messageError   {"Oops, that does not work!"};
    std::string messageDebug   {"Interesting..."};
    
    Logger t_logger(&t_logStream);
    
    silenceCout();
    t_logger.logInfo(messageInfo);
    
    silenceCout();
    t_logger.logWarning(messageWarning);

    silenceCout();
    t_logger.logError(messageError);

    silenceCout();
    t_logger.logDebug(messageDebug);
    
    std::string t_logContents{t_logStream.str()};
    
    ASSERT_TRUE(std::regex_match(t_logContents, logFileFormat()));
}
