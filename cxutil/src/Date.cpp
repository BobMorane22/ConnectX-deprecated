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
 * Implementation of the Date class
 *
 * @file    Date.cpp
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/

#include <ctime>
#include <iostream>
#include <sstream>

#include"Date.h"

using namespace std;

const int cxutil::Date::YEAR_BEGINNING {1};
const int cxutil::Date::YEAR_END       {2100};


cxutil::Date::Date()
{
    time_t rawTime = time(nullptr);
    struct tm* timeInfo = localtime(&rawTime);

    m_year  = timeInfo->tm_year + 1900;
    m_month = timeInfo->tm_mon + 1;
    m_day   = timeInfo->tm_mday;

    INVARIANTS();
}


cxutil::Date::Date(int p_year, int p_month, int p_day): m_year{p_year}, m_month{p_month}, m_day{p_day}
{
    PRECONDITION(Date::isValid(p_year, p_month, p_day));
}


void cxutil::Date::print(std::ostream& p_stream) const
{
    if(m_day < 10)
    {
        p_stream << 0;
    }

    p_stream << m_day << "/";

    if(m_month < 10)
    {
        p_stream << 0;
    }

    p_stream << m_month << "/";

    p_stream << m_year;
}


bool cxutil::Date::operator==(const Date& p_date) const
{
    return m_year == p_date.m_year && m_month == p_date.m_month && m_day == p_date.m_day;
}


bool cxutil::Date::operator!=(const Date& p_date) const
{
    return !(*this == p_date);
}


bool cxutil::Date::operator<(const Date& p_date) const
{
    bool isSmaller{false};

    if(m_year < p_date.m_year)
    {
        isSmaller = true;
    }
    else if(m_year == p_date.m_year && m_month < p_date.m_month)
    {
        isSmaller = true;
    }
    else if(m_year == p_date.m_year && m_month == p_date.m_month && m_day < p_date.m_day)
    {
        isSmaller = true;
    }

    return isSmaller;
}


bool cxutil::Date::operator<=(const Date& p_date) const
{
    return *this < p_date || *this == p_date;
}


bool cxutil::Date::operator>(const Date& p_date) const
{
    return !(*this <= p_date);
}


bool cxutil::Date::operator>=(const Date& p_date) const
{
    return *this > p_date || *this == p_date;
}


bool cxutil::Date::isLeap(int p_year) const
{
    bool isLeapYear{false};

    if (((p_year % 4 == 0) && (p_year % 100 != 0)) || ((p_year % 4 == 0) && (p_year % 100 == 0) && (p_year % 400 == 0)))
    {
        isLeapYear = true;
    }

    return isLeapYear;
}


bool cxutil::Date::isValid(int p_year, int p_month, int p_day) const
{
    using namespace cxutil;
    
    bool isValid{false};
    
    int daysPerMonths[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(isLeap(p_year))
    {
        ++daysPerMonths[Date::Months::FEBRUARY];
    }

    const bool monthRangeGood {p_month > Date::Months::JANUARY && p_month <= Date::Months::DECEMBER};
    const bool yearRangeGood  {p_year >= Date::YEAR_BEGINNING && p_year <= Date::YEAR_END};

    if(monthRangeGood && yearRangeGood)
    {
        const bool dayRangeGood {p_day > 0 && p_day <= daysPerMonths[p_month - 1]};
    
        if(dayRangeGood)
        {
            isValid = true;
        }
    }

    return isValid;
}


void cxutil::Date::checkInvariant() const
{
    INVARIANT(isValid(m_year, m_month, m_day));
}

