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
 * Interface of the Time class
 *
 * @file    Time.h
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/

#ifndef TIME_H_D4106369_434F_4ED5_A13F_C1FCAD668090
#define TIME_H_D4106369_434F_4ED5_A13F_C1FCAD668090

#include "ICliObject.h"
#include "IEnforceContract.h"

namespace cxutil
{

/***********************************************************************************************//**
 * @class Time
 * @brief A class to work with time.
 *
 * The Time class deals with three different time components: hours, minutes and seconds.
 * A constructor allows the user to get the current system time while a second one accepts 
 * parameters. The user has two options for storing times in a string: either in a 12 hours
 * cycle, or in a 24 hours cycle.
 *
 * Since the Time class uses the @c time.h facilities, it is only valid until 2038 
 * (or 2100 for methods not using ctime). More precisely, this class will be valid until 
 * January 19, 2038 at 03:14:07.
 *
 * Sources:
 *   @li time.h documentation: <http://www.cplusplus.com/reference/ctime/>
 *   @li Class limitations:    <https://en.wikipedia.org/wiki/Year_2038_problem>
 *
 * @invariant hours are in the interval [0, 23].
 * @invariant minutes are in the interval [0, 59].
 * @invatiant seconds are in the interval [0, 59].
 *
 **************************************************************************************************/
class Time : public IEnforceContract, public ICliObject
{
public:

    /*******************************************************************************************//**
     * @enum CycleFormat
     *
     * Represents the cycle on which the hours are read. Two formats are available: 12 hours cycle 
     * (i.e. 4h may represent 4h00 AM or 4:00 PM) or a 24 hour cycle (i.e. 16h00 represents 
     * 4h00 PM).
     *
     **********************************************************************************************/
    enum class CycleFormat : int
    {
        CYCLE_12,
        CYCLE_24
    };

///{@name Constructors and destructors

    /*******************************************************************************************//**
     * Default constructor.
     *
     * The default constructor generates a Date object representing the current system date.
     *
     * @param[in] p_cycleFormat The cycle format.
     *
     **********************************************************************************************/
    Time(CycleFormat p_cycleFormat = CycleFormat::CYCLE_24);


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * This constructor generates a user defined Time.
     *
     * @param[in] p_hours        The hour. This parameter should always be set as if the cycle 
     *                           format is 24 hours (i.e. 16 for 4hXX PM).
     * @param[in] p_minutes      The minutes.
     * @param[in] p_seconds      The seconds.
     * @param[in] p_cycleFormat  The cycle format.
     *
     * @pre The time represented by p_hours, p_minutes and p_seconds is a valid time.
     *
     **********************************************************************************************/
    Time(int p_hours, int p_minutes, int p_seconds, CycleFormat p_cycleFormat = CycleFormat::CYCLE_24);


    virtual ~Time() = default;

///}

///{@name Accessors

    /*******************************************************************************************//**
     * Hours accessor.
     *
     * @return The hours.
     *
     **********************************************************************************************/
    int hours() const {return m_hours;}


    /*******************************************************************************************//**
     * Minutes accessor
     *
     * @return The minutes.
     *
     **********************************************************************************************/
    int minutes() const {return m_minutes;}


    /*******************************************************************************************//**
     * Seconds accessor.
     *
     * @return The seconds.
     *
     **********************************************************************************************/
    int seconds() const {return m_seconds;}


    /*******************************************************************************************//**
     * Cycle format accessor.
     *
     * @return The current cycle format.
     *
     **********************************************************************************************/
    CycleFormat cycleFormat() const {return m_cycleFormat;}

///}

///{@name Mutators

    /*******************************************************************************************//**
     * Toogle the current cycle format.
     *
     **********************************************************************************************/
    void toggleCycleFormat();

///}

///{@name Operators

    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two Time objects are equal <em> if and only if </em> they both represent the same time.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if the two Time objects represent the same time, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator==(const Time& p_time) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Time objects are @b NOT equal <em> if and only if </em> they do @b NOT represent the 
     * same time.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if the two Time objects do not represent the same time, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator!=(const Time& p_time) const;


    /*******************************************************************************************//**
     * Smaller-than operator
     *
     * A Time object is smaller than another Time object <em> if and only if </em> the time it 
     * represents comes before on the clock.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if current Time object comes before, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator<(const Time& p_time) const;


    /*******************************************************************************************//**
     * Smaller-than-or-equal-to operator
     *
     * A Time object is smaller than or equal to another Time object <em> if and only if </em> the 
     * time it represents comes before on the clock or is the same.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if current Time object comes before or is the same, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator<=(const Time& p_time) const;


    /*******************************************************************************************//**
     * Greater-than operator
     *
     * A Time object is greater than another Time object <em> if and only if </em> the time it 
     * represents comes after on the clock.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if current Time object comes after, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator>(const Time& p_time) const;


    /*******************************************************************************************//**
     * Greater-than-or-equal-to operator
     *
     * A Time object is greater than or equal to another Time object <em> if and only if </em> the 
     * time it represents comes after on the clock or is the same.
     *
     * @param[in] p_time The Time object with which to compare.
     *
     * @return @c true if current Time object comes after or is the same, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator>=(const Time& p_time) const;

///}

protected:

    virtual void print(std::ostream& p_stream) const override;

private:

///{@name Boolean checks

    /*******************************************************************************************//**
     * Checks if the Time object is valid.
     *
     * For a Time object to be valid, the time it represents must be valid (i.e. readable on a 
     * standard clock).
     *
     * @return @c true if the Time object is valid, @false otherwise.
     *
     **********************************************************************************************/
    bool isValidTime() const;

///}


///@{ @name Printers

    /*******************************************************************************************//**
     * Prints Time to a stream in a 12-hours format.
     *
     * The format is: HH::MM::SS AM/PM, where HH goes from 00 to 11.
     *
     * @param[out] p_stream The stream in which to print the time.
     *
     **********************************************************************************************/
    void print12format(std::ostream& p_stream) const;


    /*******************************************************************************************//**
     * Prints Time to a stream in a 12-hours format.
     *
     * The format is: HH::MM::SS, where HH goes from 00 to 23.
     *
     * @param[out] p_stream The stream in which to print the time.
     *
     **********************************************************************************************/
    void print24format(std::ostream& p_stream) const;

///@}


    virtual void checkInvariant() const override;

    static const int SECONDS_MIN;          ///< The minimum number of seconds.
    static const int MINUTES_MIN;          ///< The minimum number of minutes.
    static const int HOURS_MIN;            ///< The minimum number of hours.
    
    static const int SECONDS_MAX;          ///< The maximum number of seconds.
    static const int MINUTES_MAX;          ///< The maximum number of minutes.
    static const int HOURS_MAX;            ///< The The maximum number of hours.

    int         m_hours;                   ///< The hours.
    int         m_minutes;                 ///< The minutes.
    int         m_seconds;                 ///< The seconds.
    
    CycleFormat m_cycleFormat;             ///< The time format
};

} /* namespace cxutil */

#endif // TIME_H_D4106369_434F_4ED5_A13F_C1FCAD668090

