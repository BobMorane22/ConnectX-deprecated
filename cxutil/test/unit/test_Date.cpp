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
 * Unit tests for the Date class.
 *
 * @file    test_Date.cpp
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/


#include <gtest/gtest.h>

#include <include/Date.h>


TEST(Date, DefaultConstructor_TwoSubsequentCalls_SameDate)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_EQ(t_date1, t_date2);
}


TEST(Date, ConstructorWithParameters_ValidDate_DateSet)
{
    cxutil::Date t_date{1988, 1, 22};

    ASSERT_EQ(1988, t_date.year());
    ASSERT_EQ(1,    t_date.month());
    ASSERT_EQ(22,   t_date.day());
}


TEST(Date, ConstructorWithParameters_ValidLeapYearsDates_NoExceptionThrown)
{
    using namespace cxutil;
    
    ASSERT_NO_THROW((Date{1504, 2, 29}));
    ASSERT_NO_THROW((Date{1600, 2, 29}));
    ASSERT_NO_THROW((Date{1712, 2, 29}));
    ASSERT_NO_THROW((Date{1916, 2, 29}));
    ASSERT_NO_THROW((Date{1964, 2, 29}));
    ASSERT_NO_THROW((Date{1988, 2, 29}));
    ASSERT_NO_THROW((Date{2000, 2, 29}));
    ASSERT_NO_THROW((Date{2012, 2, 29}));
}


TEST(Date, ConstructorWithParameters_YearBelow1_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Date{0, 1, 22}), PreconditionException);
}


TEST(Date, ConstructorWithParameters_YearOver2100_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Date{2101, 1, 22}), PreconditionException);
}


TEST(Date, ConstructorWithParameters_MonthBelow1_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Date{1988, 0, 22}), PreconditionException);
}


TEST(Date, ConstructorWithParameters_MonthOver12_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Date{1988, 13, 22}), PreconditionException);
}


TEST(Date, ConstructorWithParameters_NonLeapInvalid_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Date{1989, 02, 29}), PreconditionException);
}


class ValidDate: public::testing::Test
{
public:
    ValidDate(): t_date{1988, 01, 22}{};

    cxutil::Date t_date;
};


TEST_F(ValidDate, Year_ValidDate_ReturnsYear)
{
    ASSERT_EQ(1988, t_date.year());
}


TEST_F(ValidDate, Month_ValidDate_ReturnsMonth)
{
    ASSERT_EQ(1, t_date.month());
}


TEST_F(ValidDate, Day_ValidDate_ReturnsDay)
{
    ASSERT_EQ(22, t_date.day());
}


TEST_F(ValidDate, Print_ValidDateMonthOver10DayOver10_GoodFormatPrinted)
{
    std::ostringstream stream;
    cxutil::Date t_date{1988, 11, 22};
    
    stream << t_date;

    ASSERT_EQ("1988/11/22", stream.str());
}

TEST_F(ValidDate, Print_ValidDateMonthUnder10DayOver10_GoodFormatPrinted)
{
    std::ostringstream stream;
    cxutil::Date t_date{1988, 1, 22};
    
    stream << t_date;

    ASSERT_EQ("1988/01/22", stream.str());
}

TEST_F(ValidDate, Print_ValidDateMonthOver10DayUnder10_GoodFormatPrinted)
{
    std::ostringstream stream;
    cxutil::Date t_date{1988, 11, 2};
    
    stream << t_date;

    ASSERT_EQ("1988/11/02", stream.str());
}

TEST_F(ValidDate, Print_ValidDateMonthUnder10DayUnder10_GoodFormatPrinted)
{
    std::ostringstream stream;
    cxutil::Date t_date{1988, 1, 2};
    
    stream << t_date;

    ASSERT_EQ("1988/01/02", stream.str());
}

TEST(Date, OperatorEQ_TwoSubsequentSystemDates_ReturnsTrue)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_TRUE(t_date1 == t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentYears_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 1, 22};

    ASSERT_FALSE(t_date1 == t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentMonths_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 2, 22};

    ASSERT_FALSE(t_date1 == t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentDays_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 23};

    ASSERT_FALSE(t_date1 == t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentYears_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 1, 22};

    ASSERT_TRUE(t_date1 != t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentMonths_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 2, 22};

    ASSERT_TRUE(t_date1 != t_date2);
}


TEST(Date, OperatorEQ_TwoDifferentDays_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 23};

    ASSERT_TRUE(t_date1 != t_date2);
}


TEST(Date, OperatorEQ_TwoSubsequentSystemDates_ReturnsFalse)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_FALSE(t_date1 != t_date2);
}


TEST(Date, OperatorLT_Date1BeforeDate2_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 3, 19};

    ASSERT_TRUE(t_date1 < t_date2);
}


TEST(Date, OperatorLT_Date1AfterDate2_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 15};

    ASSERT_FALSE(t_date1 < t_date2);
}


TEST(Date, OperatorLT_Date1EqualsDate2_ReturnsTrue)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_FALSE(t_date1 < t_date2);
}


TEST(Date, OperatorLE_Date1BeforeDate2_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 3, 19};

    ASSERT_TRUE(t_date1 <= t_date2);
}


TEST(Date, OperatorLE_TwoEqualDates_ReturnsTrue)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_TRUE(t_date1 <= t_date2);
}


TEST(Date, OperatorLE_Date1AfterDate2_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 15};

    ASSERT_FALSE(t_date1 <= t_date2);
}


TEST(Date, OperatorGT_Date1AfterDate2_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 15};

    ASSERT_TRUE(t_date1 > t_date2);
}


TEST(Date, OperatorGT_Date1BeforeDate2_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 3, 19};

    ASSERT_FALSE(t_date1 > t_date2);
}


TEST(Date, OperatorGT_TwoEqualDates_ReturnsTrue)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_FALSE(t_date1 > t_date2);
}


TEST(Date, OperatorGE_Date1AfterDate2_ReturnsTrue)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1988, 1, 15};

    ASSERT_TRUE(t_date1 >= t_date2);
}


TEST(Date, OperatorGE_TwoEqualDates_ReturnsTrue)
{
    cxutil::Date t_date1, t_date2;

    ASSERT_TRUE(t_date1 >= t_date2);
}


TEST(Date, OperatorGE_Date1BeforeDate2_ReturnsFalse)
{
    cxutil::Date t_date1{1988, 1, 22}, t_date2{1989, 3, 19};

    ASSERT_FALSE(t_date1 >= t_date2);
}

