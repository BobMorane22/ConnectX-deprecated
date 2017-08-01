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
 * @file    Name.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for a name utility.
 *
 **************************************************************************************************/

#ifndef NAME_H_2DA14333_B8DB_4500_93A3_12263270A65C
#define NAME_H_2DA14333_B8DB_4500_93A3_12263270A65C

#include "../src/cxutilInternal.h"
#include "IEnforceContract.h"

#include <string>


BEGIN_CXUTIL_NAMESPACE

/***********************************************************************************************//**
 * @class Name
 *
 * A name utility.
 *
 * @invariant A name is assumed to never be empty. This is the main difference between an @c
 * std::string and a @c Name object.
 *
 **************************************************************************************************/
class Name : public IEnforceContract
{

public:

///@{ @name Object construction and destruction
    Name()          = delete;
    virtual ~Name() = default;


    /*******************************************************************************************//**
     * Constructor with parameter.
     *
     * Constructs a @c Name object from a non-empty @c std::string. The string value becomes the
     * name value.
     *
     * @param[in]   p_name An @c std::string containing the wanted name.
     * @pre         @c p_name should never be empty.
     *
     **********************************************************************************************/
    Name(const std::string& p_name);
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Accessor for the name attribute.
     *
     * @return  An @c std::string containing the Name value.
     *
     **********************************************************************************************/
    std::string toString() const { return m_name; } // std::string toString() const { return m_name; }
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * @param[in]   p_name The Name to compare with.
     *
     **********************************************************************************************/
    bool operator==(const Name& p_name) const {return m_name == p_name.m_name;}


    /*******************************************************************************************//**
     * Not-equal-to operator
     *
     * @param[in]   p_name The name to compare with.
     *
     **********************************************************************************************/
    bool operator!=(const Name& p_name) const {return m_name != p_name.m_name;}
///@}


protected:

    virtual void checkInvariant() const override;


private:

    std::string m_name; ///< The name value.

};

END_CXUTIL_NAMESPACE

#endif /* NAME_H_2DA14333_B8DB_4500_93A3_12263270A65C */
