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
 * @file    ReturnCode.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Interface for a return code utility.
 *
 **************************************************************************************************/

#ifndef RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F
#define RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F

#include <string>


namespace cxutil
{

/***********************************************************************************************//**
 * @class ReturnCode
 *
 * This class is meant to be used as function and method return information holder. Its internal 
 * information can help the programmer get more interesting feedback from the program's functions 
 * and method. Basically, a ReturnCode object holds three informations:
 *
 *   @li A code which gives an overview of the status of the object. Is everything ok or has 
 *       the function failed?
 *
 *   @li A message, which gives personalized information about the status. It is the function
 *       implementer's' reponsability to ensure that the message he leaves is clear and accurate.
 *
 *   @li A "is tested" flag which is set to true as soon as the ReturnCode has been tested once.
 *       By tested, we mean that is code, at least, has been checked after the return.
 *
 * @note In debug mode, it the ReturnCode has not been tested, it will assert upon destruction.
 *
 **************************************************************************************************/
class ReturnCode final
{
public:

    static const std::string NO_MESSAGE; ///< No message (empty string).

    /*******************************************************************************************//**
     * @enum Code
     *
     * A ReturnCode object can have many meanings and its Code represents its high level intent.
     * By looking at the specific Code attached to the ReturnCode object, you can tell in what 
     * state the program is left in if that ReturnCode is ever catched.
     *
     **********************************************************************************************/
    enum class Code : int
    {
        OK,       /* Action executes as expected.                                        */
        WARNING,  /* Action does NOT execute as expected. Executable may not be unstable */
        ERROR,    /* Action does NOT execute as expected. Executable is unstable.        */
        CANCEL    /* Action is canceled.                                                 */
    };


///@{ Object construction and destruction

    /*******************************************************************************************//**
     * Constructor with parameters..
     *
     * @param[in] p_code    The ReturnCode's general intent Code.
     * @param[in] p_message The ReturnCode's human readable message.
     *
     * @note You can use this construtor as the default constructor. It will then define a
     *       Code::OK with an empty message ReturnCode, which is the most used case.
     *
     **********************************************************************************************/
     ReturnCode(Code p_code = Code::OK, const std::string& p_message = NO_MESSAGE);


    /*******************************************************************************************//**
     * Destructor.
     *
     * In debug mode, this destrutor checks it the ReturnCode has been checked at least once
     * elsewhere in the code. To check a ReturnCode object, you need to use one of the four
     * following methods:
     *
     *      @li @c isOK()
     *      @li @c isWarning()
     *      @li @c isError()
     *      @li @c isCancelled() 
     *
     * @see @c isOK()
     * @see isWarning()
     * @see isError()
     * @see isCancelled() 
     *
     **********************************************************************************************/
    ~ReturnCode();
///@}


///@{ Checks

    /*******************************************************************************************//**
     * Check if a ReturnCode holds a Code::OK.
     *
     * If @c true is returned, it means the program is in a valid state. If @c false is returned, 
     * it generally means that some further handeling and investigation is required. 
     *
     * @return A boolean indicating if the ReturnCode holds a Code::OK.
     *
     **********************************************************************************************/
    bool isOk();


    /*******************************************************************************************//**
     * Check if a ReturnCode holds a Code::WARNING.
     *
     * If @c true is returned, it means the program is potentialy in an unstabke state. If @c false 
     * is returned, it  generally means that some further handeling and investigation is required. 
     *
     * @return A boolean indicating if the ReturnCode holds a Code::WARNING.
     *
     **********************************************************************************************/
    bool isWarning();


    /*******************************************************************************************//**
     * Check if a ReturnCode holds a Code::ERROR.
     *
     * If @c true is returned, it means the program is in an unstabke state. If @c false 
     * is returned, it  generally means that some further handeling and investigation is required. 
     *
     * @return A boolean indicating if the ReturnCode holds a Code::ERROR.
     *
     **********************************************************************************************/
    bool isError();


    /*******************************************************************************************//**
     * Check if a ReturnCode holds a Code::CANCEL.
     *
     * If @c true is returned, it means the action performed by the routine returning has been 
     * canceled.. If @c false is returned, it  generally means that some further investigation 
     * is required. 
     *
     * @return A boolean indicating if the ReturnCode holds a Code::CANCEL.
     *
     **********************************************************************************************/
    bool isCancelled();


    /*******************************************************************************************//**
     * Tells wether a ReturnCode holds a non-empty message.
     *
     * @return @c true if the ReturnCode's messge is empty, @c false if it isn't.
     *
     **********************************************************************************************/
    bool holdsMessage() const;


    /*******************************************************************************************//**
     * Tells wether a ReturnCode has been tested at least once.
     *
     * @return @c true if the ReturnCode has been tested at least once, @c false otherwise.
     *
     **********************************************************************************************/
    bool isTested() const;

///@}


///@{ Accessors

    /*******************************************************************************************//**
     * Gets the ReturnCode's message.
     *
     * @return The ReturnCode's message.
     *
     **********************************************************************************************/
    std::string message() const;

///@}

private:

    bool        m_tested   {false   };   ///< Flag thats knows if the ReturnCode has been tested at least once.
    Code        m_code     {Code::OK};   ///< The internal error code.
    std::string m_message;               ///< The human readable message.
};

} // cxutil

#endif /* RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F */
