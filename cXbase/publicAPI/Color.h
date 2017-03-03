/***********************************************************************************************//**
 * @file    Color.h
 * @author  Eric Poirier
 * @date    September 2016
 * @version 0.1
 *
 * Interface for a color utility.
 *
 **************************************************************************************************/

#ifndef COLOR_H_
#define COLOR_H_

#include "AsciiColorCode.h"
#include "Name.h"

BEGIN_CXBASE_NAMESPACE


/***********************************************************************************************//**
 * @class Color
 *
 * A Color refers to a color Name paired with an ASCII @c char AsciiColorCode to be displayed in
 * text mode. When a Color object representing the absence of color is needed, two values are
 * made available to the developper: @c NO_COLOR (Name) and @c NO_COLOR_ASCII_CODE (AsciiColorCode).
 *
 * @see Name
 * @see AsciiColorCode
 *
 **************************************************************************************************/
class Color
{

public:

///@{ @name Object construction and destruction
    virtual ~Color() = default;


    /*******************************************************************************************//**
     * Default constructor.
     *
     * Construct an object with the "No color" values mentionned above (@c NO_COLOR and
     * @c NO_COLOR_ASCII_CODE).
     *
     **********************************************************************************************/
    Color() : m_name{NO_COLOR}, m_asciiColorCode{NO_COLOR_ASCII_CODE} {}


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * @param[in] p_name            The Color name.
     * @param[in] p_asciiColorCode  The wanted AsciiColorCode.
     *
     **********************************************************************************************/
    Color(Name p_name, AsciiColorCode p_asciiColorCode) : m_name{p_name}, m_asciiColorCode{p_asciiColorCode} {}
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Name accessor.
     *
     * @return The Color's name.
     *
     **********************************************************************************************/
    Name name() const {return m_name;}


    /*******************************************************************************************//**
     * ASCII code accessor.
     *
     * @return The Color's ASCII code.
     *
     **********************************************************************************************/
    AsciiColorCode asciiColorCode() const {return m_asciiColorCode;}
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two Colors are considered equal <em> if and only if </em> their names are equal. The way
     * the color is represented in text mode has no effect on the equality check.
     *
     * @param[in] p_color The Color to compare with.
     *
     **********************************************************************************************/
    virtual bool operator==(const Color& p_color) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Colors are considered @b NOT equal <em> if and only if </em> their names are @ b NOT
     * equal. The way the color is represented in text mode has no effect on the non-equality
     * check.
     *
     * @param[in] p_color The Color to compare with.
     *
     **********************************************************************************************/
    virtual bool operator!=(const Color& p_color) const;
///@}

private:

    Name                NO_COLOR               { "No color" };
    AsciiColorCode      NO_COLOR_ASCII_CODE    { ' ' };

    Name                m_name;             ///< The Color name.
    AsciiColorCode      m_asciiColorCode;   ///< The Color ASCII code.

};

END_CXBASE_NAMESPACE

#endif /* COLOR_H_ */
