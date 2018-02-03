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
 * Unit tests for the Time class.
 *
 * @file    test_Time.cpp
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/


#include <gtest/gtest.h>

#include <cxutil/include/Time.h>


TEST(Time, DefaultConstructor_TwoSubsequentCalls_SameTime)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_EQ(t_time1, t_time2);
}


TEST(Time, ConstructorWithParameters_ValidTimes_ValidObjectConstructed)
{
    cxutil::Time t_time{5, 10, 15};

    ASSERT_EQ(5,                                   t_time.hours()       );
    ASSERT_EQ(10,                                  t_time.minutes()     );
    ASSERT_EQ(15,                                  t_time.seconds()     );
    ASSERT_EQ(cxutil::Time::CycleFormat::CYCLE_24, t_time.cycleFormat() );
}


TEST(Time, ConstructorWithParameters_HoursBelowMin_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{-1, 10, 15}), PreconditionException);
}


TEST(Time, ConstructorWithParameters_HoursOverMax_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{24, 10, 15}), PreconditionException);
}


TEST(Time, ConstructorWithParameters_MinutesBelowMin_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{5, -1, 15}), PreconditionException);
}


TEST(Time, ConstructorWithParameters_MinutesOverMax_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{5, 60, 15}), PreconditionException);
}


TEST(Time, ConstructorWithParameters_SecondesBelowMin_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{5, 10, -1}), PreconditionException);
}


TEST(Time, ConstructorWithParameters_SecondesOverMax_ExceptionThrown)
{
    ASSERT_THROW((cxutil::Time{5, 10, 60}), PreconditionException);
}


class ValidTime: public::testing::Test
{
public:
    ValidTime(): t_time{5, 10, 15}
    {
    }

    cxutil::Time t_time;
};


TEST_F(ValidTime, Hours_ValidTime_ReturnsHours)
{
    ASSERT_EQ(5, t_time.hours());
}


TEST_F(ValidTime, Minutes_ValidTime_ReturnsMinutes)
{
    ASSERT_EQ(10, t_time.minutes());
}


TEST_F(ValidTime, Seconds_ValidTime_ReturnsSeconds)
{
    ASSERT_EQ(15, t_time.seconds());
}


TEST(Time, CycleFormat_ValidTime12_Returns12HoursCycleFormat)
{
    cxutil::Time t_time{5, 10, 15, cxutil::Time::CycleFormat::CYCLE_12};

    ASSERT_EQ(t_time.cycleFormat(), cxutil::Time::CycleFormat::CYCLE_12);
}


TEST(Time, CycleFormat_ValidTime24_Returns24HoursCycleFormat)
{
    cxutil::Time t_time{5, 10, 15, cxutil::Time::CycleFormat::CYCLE_24};

    ASSERT_EQ(t_time.cycleFormat(), cxutil::Time::CycleFormat::CYCLE_24);
}


TEST_F(ValidTime, CycleFormat_ValidTime_CycleFormatToggled)
{
    ASSERT_EQ(t_time.cycleFormat(), cxutil::Time::CycleFormat::CYCLE_24);

    t_time.toggleCycleFormat();
    ASSERT_EQ(t_time.cycleFormat(), cxutil::Time::CycleFormat::CYCLE_12);

    t_time.toggleCycleFormat();
    ASSERT_EQ(t_time.cycleFormat(), cxutil::Time::CycleFormat::CYCLE_24);
}


TEST_F(ValidTime, StreamInsertionOperator_Cycle12BeforeNoon_PrintsWithAM)
{
    t_time.toggleCycleFormat();

    std::ostringstream stream;
    stream << t_time;

    ASSERT_EQ("05:10:15 AM", stream.str());
}


TEST(Time, StreamInsertionOperator_Cycle12AfterMorning_PrintsWithPM)
{
    cxutil::Time t_time{17, 10, 15};
    t_time.toggleCycleFormat();

    std::ostringstream stream;
    stream << t_time;

    ASSERT_EQ("05:10:15 PM", stream.str());
}


TEST(Time, StreamInsertionOperator_Cycle12AfterMorning_PrintsNoConversion)
{
    cxutil::Time t_time{17, 10, 15};

    std::ostringstream stream;
    stream << t_time;

    ASSERT_EQ("17:10:15", stream.str());
}


TEST(Time, OperatorEQ_TwoSubsequentSystemTimes_ReturnsTrue)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_TRUE(t_time1 == t_time2);
}


TEST(Time, OperatorEQ_HoursNotSame_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{6, 10, 15};

    ASSERT_FALSE(t_time1 == t_time2);
}


TEST(Time, OperatorEQ_MinutesNotSame_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 11, 15};

    ASSERT_FALSE(t_time1 == t_time2);
}


TEST(Time, OperatorEQ_SecondsNotSame_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_FALSE(t_time1 == t_time2);
}


TEST(Time, OperatorNEQ_HoursNotSame_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{6, 10, 15};

    ASSERT_TRUE(t_time1 != t_time2);
}


TEST(Time, OperatorNEQ_MinutesNotSame_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 11, 15};

    ASSERT_TRUE(t_time1 != t_time2);
}


TEST(Time, OperatorNEQ_SecondesNotSame_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_TRUE(t_time1 != t_time2);
}


TEST(Time, OperatorNEQ_SameTime_ReturnsFalse)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_FALSE(t_time1 != t_time2);
}


TEST(Time, OperatorLT_SecondsLessInFirstTime_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_TRUE(t_time1 < t_time2);
}


TEST(Time, OperatorLT_SecondsMoreInFirstTime_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 16};
    cxutil::Time t_time2{5, 10, 15};

    ASSERT_FALSE(t_time1 < t_time2);
}


TEST(Time, OperatorLT_TwoEqualTimes_ReturnsFalse)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_FALSE(t_time1 < t_time2);
}


TEST(Time, OperatorLE_SecondsLessInFirstTime_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_TRUE(t_time1 <= t_time2);
}


TEST(Time, OperatorLE_TwoEqualTimes_ReturnsTrue)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_TRUE(t_time1 <= t_time2);
}


TEST(Time, OperatorLE_SecondsMoreInFirstTime_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 16};
    cxutil::Time t_time2{5, 10, 15};

    ASSERT_FALSE(t_time1 <= t_time2);
}


TEST(Time, OperatorGT_SecondsMoreInFirstTime_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 16};
    cxutil::Time t_time2{5, 10, 15};

    ASSERT_TRUE(t_time1 > t_time2);
}


TEST(Time, OperatorGT_SecondsLessInFirstTime_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_FALSE(t_time1 > t_time2);
}


TEST(Time, OperatorGT_TwoEqualTimes_ReturnsFalse)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_FALSE(t_time1 > t_time2);
}


TEST(Time, OperatorGE_SecondsMoreInFirstTime_ReturnsTrue)
{
    cxutil::Time t_time1{5, 10, 16};
    cxutil::Time t_time2{5, 10, 15};

    ASSERT_TRUE(t_time1 >= t_time2);
}


TEST(Time, OperatorGE_TwoEqualTimes_ReturnsTrue)
{
    cxutil::Time t_time1, t_time2;

    ASSERT_TRUE(t_time1 >= t_time2);
}


TEST(Time, OperatorGE_SecondsLessInFirstTime_ReturnsFalse)
{
    cxutil::Time t_time1{5, 10, 15};
    cxutil::Time t_time2{5, 10, 16};

    ASSERT_FALSE(t_time1 >= t_time2);
}

