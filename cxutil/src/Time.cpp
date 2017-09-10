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
 * Implementation of the Time class
 *
 * @file    Time.cpp
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/

#include <ctime>

#include "Assertion.h"
#include "Time.h"


const int cxutil::Time::SECONDS_MIN {0};
const int cxutil::Time::MINUTES_MIN {0};
const int cxutil::Time::HOURS_MIN   {0};
    
const int cxutil::Time::SECONDS_MAX {60};
const int cxutil::Time::MINUTES_MAX {60};
const int cxutil::Time::HOURS_MAX   {24};


cxutil::Time::Time(bool p_daylightSavingEnabled, CycleFormat p_cycleFormat): 
                   m_cycleFormat{p_cycleFormat}
{
    time_t rawTime = time(NULL);
    struct tm* timeInfo = localtime(&rawTime);

    timeInfo->tm_isdst = static_cast<int>(p_daylightSavingEnabled);

    m_hours = timeInfo->tm_hour;
    m_minutes = timeInfo->tm_min;
    m_seconds = timeInfo->tm_sec;

    INVARIANTS();
}


cxutil::Time::Time(int p_hours, int p_minutes, int p_seconds, CycleFormat p_cycleFormat): 
                   m_hours{p_hours}, m_minutes{p_minutes}, m_seconds{p_seconds}, m_cycleFormat{p_cycleFormat}
{
    PRECONDITION(p_hours   >= HOURS_MIN   && p_hours   < HOURS_MAX  );
    PRECONDITION(p_minutes >= MINUTES_MIN && p_minutes < MINUTES_MAX);
    PRECONDITION(p_seconds >= SECONDS_MIN && p_seconds < SECONDS_MAX);

    INVARIANTS();
}


void cxutil::Time::toggleCycleFormat()
{
    if(m_cycleFormat == cxutil::Time::CycleFormat::CYCLE_12)
    {
        m_cycleFormat = cxutil::Time::CycleFormat::CYCLE_24;
    }
    else
    {
        m_cycleFormat = cxutil::Time::CycleFormat::CYCLE_12;
    }
}


bool cxutil::Time::operator==(const Time& p_time) const
{
    return p_time.m_hours   == m_hours   &&
           p_time.m_minutes == m_minutes &&
           p_time.m_seconds == m_seconds;
}


bool cxutil::Time::operator!=(const Time& p_time) const
{
    return !(*this == p_time);
}


bool cxutil::Time::operator<(const Time& p_time) const
{
    return m_hours * 3600 + m_minutes * 60 + m_seconds <
           p_time.m_hours * 3600 + p_time.m_minutes * 60 + p_time.m_seconds;
}


bool cxutil::Time::operator<=(const Time& p_time) const
{
    return *this < p_time || *this == p_time;
}


bool cxutil::Time::operator>(const Time& p_time) const
{
    return !(*this <= p_time);
}


bool cxutil::Time::operator>=(const Time& p_time) const
{
    return !(*this < p_time);
}


void cxutil::Time::print12format(std::ostream& p_stream) const
{
    int hours {m_hours % 12};

    if(hours == 0)
    {
        hours = 12;
    }

    if(hours < 10)
    {
        p_stream << "0";
    }
    
    p_stream << hours << ":";

    if(m_minutes < 10)
    {
        p_stream << "0";
    }
    
    p_stream << m_minutes;
    p_stream << ":";

    if(m_seconds < 10)
    {
        p_stream << "0";
    }
    
    p_stream << m_seconds;

    if(m_hours < 12)
    {
        p_stream << " AM";
    }
    else
    {
        p_stream << " PM";
    }
}


void cxutil::Time::print24format(std::ostream& p_stream) const
{
    if(m_hours < 10)
    {
        p_stream << "0";
    }
    
    p_stream << m_hours << ":";

    if(m_minutes < 10)
    {
        p_stream << "0";
    }
    
    p_stream << m_minutes;
    p_stream << ":";

    if(m_seconds < 10)
    {
        p_stream << "0";
    }
    
    p_stream << m_seconds;
}


void cxutil::Time::print(std::ostream& p_stream) const
{
    if(m_cycleFormat == cxutil::Time::CycleFormat::CYCLE_12)
    {
        print12format(p_stream);
    }
    else if(m_cycleFormat == cxutil::Time::CycleFormat::CYCLE_24)
    {
        print24format(p_stream);
    }
    else
    {
        CX_ASSERT("Unknown cycle format.");
    }
}


bool cxutil::Time::isValidTime() const
{
    bool isValid {false};
    
    if(m_hours   >= HOURS_MIN   && m_hours   < HOURS_MAX   &&
       m_minutes >= MINUTES_MIN && m_minutes < MINUTES_MAX &&
       m_seconds >= SECONDS_MIN && m_seconds < SECONDS_MAX   )
    {
        isValid = true;
    }
    
    return isValid;
}


void cxutil::Time::checkInvariant() const
{
    INVARIANT(isValidTime());
}
