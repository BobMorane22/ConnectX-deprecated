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
 * @file    test_ReturnCode.cpp
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Unit tests for a the RturnCode class.
 *
 **************************************************************************************************/


#include <gtest/gtest.h>

#include <include/ReturnCode.h>

using namespace cxutil;


TEST(ReturnCode, Constructor_Default_CodeOkIsSet)
{
    ReturnCode t_returnCode;
    
    ASSERT_TRUE(t_returnCode.isOk());
}

TEST(ReturnCode, Constructor_Default_MessageIsEmpty)
{
    ReturnCode t_returnCode;
    t_returnCode.isOk(); // Otherwise assertions pop!
    
    ASSERT_EQ(t_returnCode.message(), ReturnCode::NO_MESSAGE);
}

TEST(ReturnCode, Constructor_Default_ReturnCodeIsNotTested)
{
    ReturnCode t_returnCode;
    
    ASSERT_FALSE(t_returnCode.isTested());
    
    t_returnCode.isOk();
}

TEST(ReturnCode, ConstructorWithParameters_ErrorAndMessage_CodeErrorIsSet)
{
    ReturnCode t_returnCode{ReturnCode::Code::ERROR, "This in an error..."};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isError());
}

TEST(ReturnCode, ConstructorWithParameters_ErrorAndMessage_MessageIsSet)
{
    std::string theMessage{"This in an error..."};

    ReturnCode t_returnCode{ReturnCode::Code::ERROR, theMessage};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.message() == theMessage);
}

TEST(ReturnCode, IsOk_CodeIsOK_ReturnsTrue)
{
    ReturnCode t_returnCode;
    
    ASSERT_TRUE(t_returnCode.isOk());
}

TEST(ReturnCode, IsOk_CodeIsError_ReturnsFalse)
{
    ReturnCode t_returnCode{ReturnCode::Code::ERROR, ReturnCode::NO_MESSAGE};
    
    ASSERT_FALSE(t_returnCode.isOk());
}

TEST(ReturnCode, IsOk_NewReturnCode_ReturnCodeIsTested)
{
    ReturnCode t_returnCode;
    
    ASSERT_FALSE(t_returnCode.isTested());
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isTested());
}

TEST(ReturnCode, IsWarning_CodeIsWarning_ReturnsTrue)
{
    ReturnCode t_returnCode{ReturnCode::Code::WARNING, ReturnCode::NO_MESSAGE};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isWarning());
}

TEST(ReturnCode, IsWarning_CodeIsError_ReturnsFalse)
{
    ReturnCode t_returnCode{ReturnCode::Code::ERROR, ReturnCode::NO_MESSAGE};
    t_returnCode.isOk();
    
    ASSERT_FALSE(t_returnCode.isWarning());
}

TEST(ReturnCode, IsError_CodeIsError_ReturnsTrue)
{
    ReturnCode t_returnCode{ReturnCode::Code::ERROR, ReturnCode::NO_MESSAGE};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isError());
}

TEST(ReturnCode, IsError_CodeIsOK_ReturnsFalse)
{
    ReturnCode t_returnCode;
    t_returnCode.isOk();
    
    ASSERT_FALSE(t_returnCode.isError());
}

TEST(ReturnCode, IsCancelled_CodeIsCancel_ReturnsTrue)
{
    ReturnCode t_returnCode{ReturnCode::Code::CANCEL, ReturnCode::NO_MESSAGE};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isCancelled());
}

TEST(ReturnCode, IsCancelled_CodeIsError_ReturnsFalse)
{
    ReturnCode t_returnCode{ReturnCode::Code::ERROR, ReturnCode::NO_MESSAGE};
    t_returnCode.isOk();
    
    ASSERT_FALSE(t_returnCode.isCancelled());
}

TEST(ReturnCode, HoldsMessage_CodeHasNoMessage_ReturnsFalse)
{
    ReturnCode t_returnCode;
    t_returnCode.isOk();
    
    ASSERT_FALSE(t_returnCode.holdsMessage());
}

TEST(ReturnCode, HoldsMessage_CodeHasMessage_ReturnsTrue)
{
    ReturnCode t_returnCode{ReturnCode::Code::OK, "A message!"};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.holdsMessage());
}

TEST(ReturnCode, IsTested_ReturnCodeIsNotTested_ReturnsFalse)
{
    ReturnCode t_returnCode;
    
    ASSERT_FALSE(t_returnCode.isTested());
    
    t_returnCode.isOk(); // Shut assertion...
}

TEST(ReturnCode, IsTested_ReturnCodeIsTested_ReturnsTrue)
{
    ReturnCode t_returnCode;
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.isTested());
}

TEST(ReturnCode, Message_ReturnCodeHasMessage_ReturnsMessage)
{
    std::string theMessage{"This in an error..."};

    ReturnCode t_returnCode{ReturnCode::Code::OK, theMessage};
    t_returnCode.isOk();
    
    ASSERT_TRUE(t_returnCode.message() == theMessage);
}

TEST(ReturnCode, Message_ReturnCodeHasNoMessage_ReturnsEmptyString)
{
    ReturnCode t_returnCode;
    t_returnCode.isOk();
    
    ASSERT_EQ(t_returnCode.message(), ReturnCode::NO_MESSAGE);
}
