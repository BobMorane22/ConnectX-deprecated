/***********************************************************************************************//**
 * @file    Name.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for a name utility.
 *
 **************************************************************************************************/

#ifndef NAME_H_
#define NAME_H_

#include "../source/cXbaseInternal.h"

#include <string>


BEGIN_CXBASE_NAMESPACE

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

    virtual void checkInvariant() const;


private:

    std::string m_name; ///< The name value.

};

END_CXBASE_NAMESPACE

#endif /* NAME_H_ */
