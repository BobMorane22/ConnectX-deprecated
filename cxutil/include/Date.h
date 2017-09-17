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
 * Interface of the Date class
 *
 * @file    Date.h
 * @author  Éric Poirier
 * @date    June 2015
 * @version 2.0
 *
 **************************************************************************************************/

#ifndef DATE_H_9A0E690A_9429_4913_BAA2_6E341347674F
#define DATE_H_9A0E690A_9429_4913_BAA2_6E341347674F


#include "ICliObject.h"
#include "IEnforceContract.h"


namespace cxutil
{
/***********************************************************************************************//**
 * @class Date
 *
 * A class to work with dates.
 *
 * The Date class is meant to work with Gregorian calendar dates. It deals with three different 
 * time entities: years, months and days.The user can get Dates as strings in only one 
 * format: YYYY/MM/DD.
 *
 * Since the Date class uses the @c time.h facilities, it is only valid until 2038 
 * (or 2100 for methods not using ctime). More precisely, this class will be valid until 
 * January 19, 2038 at 03:14:07.
 *
 * Sources:
 *   @li time.h documentation: <http://www.cplusplus.com/reference/ctime/>
 *   @li Class limitations:    <https://en.wikipedia.org/wiki/Year_2038_problem>
 *
 * @invariant The Date object represents a date on the gregorian calendar.
 *
 **************************************************************************************************/
class Date : public IEnforceContract, public ICliObject
{
public:

///@{ @name Construction and destruction

    /*******************************************************************************************//**
     * Default constructor.
     *
     * The default constructor generates a Date object representing the current system date.
     *
     **********************************************************************************************/
    Date();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * The three input parameters are used to compose a Date object.
     *
     * @param[in] p_year    The date's year.
     * @param[in] p_month   The date's month.
     * @param[in] p_day     The date's day.
     *
     * @pre The date wanted is a valid date (i.e. it exists in the Gregorian calendar).
     *
     * @see isValid
     *
     **********************************************************************************************/
    Date(int p_year, int p_month, int p_day);


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Date() = default;

///@}

///@{ @name Accessors

    /*******************************************************************************************//**
     * Get the year.
     *
     * @return The Date object's year component.
     *
     **********************************************************************************************/
    int year() const {return m_year;}


    /*******************************************************************************************//**
     * Get the month.
     *
     * @return The Date object's month component.
     *
     **********************************************************************************************/
    int month() const {return m_month;}


    /*******************************************************************************************//**
     * Get the day.
     *
     * @return The Date object's day component.
     *
     **********************************************************************************************/
    int day() const {return m_day;}

///@}

///@{ @name Operators

    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two Date objects are considered equal <em> if and only if </em> the two dates they represent 
     * are the same on the gregorian calendar.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the two Date objects are equal, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator==(const Date& p_date) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Date objects are considered @b NOT equal <em> if and only if </em> the two dates they 
     * represent are different on the gregorian calendar.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the two Date objects are different, @c false otherwise.
     *
     **********************************************************************************************/
    bool operator!=(const Date& p_date) const;


    /*******************************************************************************************//**
     * Smaller-than operator.
     *
     * A Date object is considered smaller than another Date object if it comes before on the 
     * gregorian calendar.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the current Date object comes before in the gregorian calendar. 
     *            @c false otherwise.
     *
     **********************************************************************************************/
    bool operator<(const Date& p_date) const;


    /*******************************************************************************************//**
     * Smaller-than-or-equal-to operator.
     *
     * A Date object is considered smaller than or equal to another Date object if it comes before 
     * on the gregorian calendar or if it is the same.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the current Date object comes before in the gregorian calendar or is 
     *            equal. @c false otherwise.
     *
     **********************************************************************************************/
    bool operator<=(const Date& p_date) const;


    /*******************************************************************************************//**
     * Greater-than operator.
     *
     * A Date object is considered greater than another Date object if it comes after on the 
     * gregorian calendar.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the current Date object comes after in the gregorian calendar. 
     *            @c false otherwise.
     *
     **********************************************************************************************/
    bool operator>(const Date& p_date) const;


    /*******************************************************************************************//**
     * Greater-than-or-equal-to operator.
     *
     * A Date object is considered greater than or equal to another Date object if it comes after 
     * on the gregorian calendar or if it is the same.
     *
     * @param[in] p_date The Date with which to compare.
     * @return    @c true if the current Date object comes after in the gregorian calendar or is 
     *            equal. @c false otherwise.
     *
     **********************************************************************************************/
    bool operator>=(const Date& p_date) const;

///@}

protected:

    virtual void print(std::ostream& p_stream) const override;

private:

///@{ Boolean checks

    /*******************************************************************************************//**
     * Checks if a year is a leap year.
     *
     * @param[in] p_year The year to test.
     *
     * @return @c true if the year is a leap year, @c false otherwise.
     *
     **********************************************************************************************/
    bool isLeap(int p_year) const;


    /*******************************************************************************************//**
     * Checks if a date is valid.
     *
     * Checks if a date is valid (i.e. it exists on the gregorian calendar). The year range of
     * accepted valued is [@c YEAR_BEGINNING, @c YEAR_END] .
     *
     **********************************************************************************************/
    bool isValid(int p_year, int p_month, int p_day) const;

///@}


    virtual void checkInvariant() const override;

    /*******************************************************************************************//**
     * @enum Months
     *
     * The 12 months of the gregorian calendar.
     *
     **********************************************************************************************/
    enum Months
    {
        JANUARY,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    
    static const int       YEAR_BEGINNING; ///< Year inferior limit.
    static const int       YEAR_END;       ///< Year superior limit.
    
    int                    m_year;    ///< The year
    int                    m_month;   ///< The month
    int                    m_day;     ///< The day
    
};

} /* namespace tools */

#endif // DATE_H_9A0E690A_9429_4913_BAA2_6E341347674F
