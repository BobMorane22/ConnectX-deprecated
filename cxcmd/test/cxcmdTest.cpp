/***************************************************************************************************
* 
* Copyright (C) 2016 Connect X team
* 
* This file is part of Connect X.
* 
* Connect X is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Connect X is distributed in the hope that it will be useful
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Connect X.  If not, see <http://www.gnu.org/licenses./>.
* 
**************************************************************************************************/

/***********************************************************************************************//**
* @file    cxcmdTest.cpp
* @author  elliotchance
* @date    September 2016
* @version 0.1
* 
* Unit tests main. All unit tests for the cxcmdlibrary run from here. All source code from this
* file comes from <a href="https://gist.github.com/ "elliotchance/8215283"> here </a>.
* 
***************************************************************************************************/
#include "gtest/gtest.h"

using namespace testing;


class ConfigurableEventListener : public TestEventListener
{

protected:
    TestEventListener* eventListener;

public:

    /**
     * Show the names of each test case.
     */
    bool showTestCases;

    /**
     * Show the names of each test.
     */
    bool showTestNames;

    /**
     * Show each success.
     */
    bool showSuccesses;

    /**
     * Show each failure as it occurs. You will also see it at the bottom after the full suite is run.
     */
    bool showInlineFailures;

    /**
     * Show the setup of the global environment.
     */
    bool showEnvironment;

    explicit ConfigurableEventListener(TestEventListener* theEventListener) : eventListener(theEventListener)
    {
        showTestCases        = true;
        showTestNames        = true;
        showSuccesses        = true;
        showInlineFailures   = true;
        showEnvironment      = true;
    }

    virtual ~ConfigurableEventListener()
    {
        delete eventListener;
    }

    virtual void OnTestProgramStart(const UnitTest& unit_test)
    {
        eventListener->OnTestProgramStart(unit_test);
    }

    virtual void OnTestIterationStart(const UnitTest& unit_test, int iteration)
    {
        eventListener->OnTestIterationStart(unit_test, iteration);
    }

    virtual void OnEnvironmentsSetUpStart(const UnitTest& unit_test)
    {
        if(showEnvironment) {
            eventListener->OnEnvironmentsSetUpStart(unit_test);
        }
    }

    virtual void OnEnvironmentsSetUpEnd(const UnitTest& unit_test)
    {
        if(showEnvironment) {
            eventListener->OnEnvironmentsSetUpEnd(unit_test);
        }
    }

    virtual void OnTestCaseStart(const TestCase& test_case)
    {
        if(showTestCases) {
            eventListener->OnTestCaseStart(test_case);
        }
    }

    virtual void OnTestStart(const TestInfo& test_info)
    {
        if(showTestNames) {
            eventListener->OnTestStart(test_info);
        }
    }

    virtual void OnTestPartResult(const TestPartResult& result)
    {
        eventListener->OnTestPartResult(result);
    }

    virtual void OnTestEnd(const TestInfo& test_info)
    {
        if((showInlineFailures && test_info.result()->Failed()) || (showSuccesses && !test_info.result()->Failed())) {
            eventListener->OnTestEnd(test_info);
        }
    }

    virtual void OnTestCaseEnd(const TestCase& test_case)
    {
        if(showTestCases) {
            eventListener->OnTestCaseEnd(test_case);
        }
    }

    virtual void OnEnvironmentsTearDownStart(const UnitTest& unit_test)
    {
        if(showEnvironment) {
            eventListener->OnEnvironmentsTearDownStart(unit_test);
        }
    }

    virtual void OnEnvironmentsTearDownEnd(const UnitTest& unit_test)
    {
        if(showEnvironment) {
            eventListener->OnEnvironmentsTearDownEnd(unit_test);
        }
    }

    virtual void OnTestIterationEnd(const UnitTest& unit_test, int iteration)
    {
        eventListener->OnTestIterationEnd(unit_test, iteration);
    }

    virtual void OnTestProgramEnd(const UnitTest& unit_test)
    {
        eventListener->OnTestProgramEnd(unit_test);
    }

};

int main(int argc, char **argv)
{
    // initialize
    ::testing::InitGoogleTest(&argc, argv);

    // remove the default listener

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    auto default_printer = listeners.Release(listeners.default_result_printer());


    // add our listener, by default everything is on (the same as using the default listener)
    // here I am turning everything off so I only see the 3 lines for the result
    // (plus any failures at the end), like:

    // [==========] Running 149 tests from 53 test cases.
    // [==========] 149 tests from 53 test cases ran. (1 ms total)
    // [  PASSED  ] 149 tests.

    ConfigurableEventListener *listener = new ConfigurableEventListener(default_printer);
    listener->showEnvironment = false;
    listener->showTestCases = false;
    listener->showTestNames = false;
    listener->showSuccesses = false;
    listener->showInlineFailures = false;
    listeners.Append(listener);

    // run
    return RUN_ALL_TESTS();
}
