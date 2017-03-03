/***********************************************************************************************//**
 * @file    AsciiColorCode.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for an ASCII color code utility.
 *
 **************************************************************************************************/

#ifndef ASCIICOLORCODE_H_
#define ASCIICOLORCODE_H_

#include "../source/cXbaseInternal.h"


BEGIN_CXBASE_NAMESPACE

/***********************************************************************************************//**
 * @class AsciiColorCode
 *
 * An ASCII code representing a color.
 *
 * An ASCII color code is an ASCII character that is used to represent a color (for example in a
 * terminal, or a text file). Not all ASCII characters can be used to represent a color. In fact,
 * only letters (lower or upper case) and the space character can be used.
 *
 * For example, these are some of the ways the color @a Black can be represented:
 *      @li the character @c 'B';
 *      @li the character @c 'b';
 *      @li the character @c 'x';
 *      @li the character @c ' '.
 *
 * However, the last two examples are not recommended for readibility purposes.
 *
 * @invariant An ASCII color code is always a letter (lower or upper case) or a space character.
 *
 * @see Color
 *
 **************************************************************************************************/
class AsciiColorCode : public IEnforceContract
{

public:

///@{ @name Object construction and destruction
    AsciiColorCode()            = delete;
    virtual ~AsciiColorCode()   = default;


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Constructs an @c AsciiColorCode object from a character (@c char).
     *
     * @param[in]   p_asciiColorCode The char containing the ASCII code.
     * @pre         @c p_asciiColorCode is a letter (lower or upper case) or a space.
     * @post        @c m_asciiColorCode is a letter (lower or upper case) or a space.
     *
     **********************************************************************************************/
    AsciiColorCode(char p_asciiColorCode);
///@}

///@{ @name Data access
    /*******************************************************************************************//**
     * Accessor for the ascii color code attribute.
     *
     * @return A char containing the ascii color code.
     *
     **********************************************************************************************/
    char toChar() const { return m_asciiColorCode; }
///@}


/// @name Operators
///@{
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The operator compares for equality the @c char code value of the two AsciiColorCode objects
     * for equality.
     *
     * @param[in] p_asciiColorCode The AsciiColorCode to compare with.
     *
     **********************************************************************************************/
    bool operator==(const AsciiColorCode& p_asciiColorCode) const { return p_asciiColorCode.m_asciiColorCode == m_asciiColorCode; }


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * The operator compares for equality the @c char code value of the two AsciiColorCode objects
     * for non-equality.
     *
     * @param[in] p_asciiColorCode The AsciiColorCode to compare with.
     *
     **********************************************************************************************/
    bool operator!=(const AsciiColorCode& p_asciiColorCode) const { return p_asciiColorCode.m_asciiColorCode != m_asciiColorCode; }


    /*******************************************************************************************//**
     * Stream insertion operator.
     *
     * The operator simply inserts the @c char encoding the color in @c p_flux.
     *
     * @param[in] p_flux            The stream.
     * @param[in] p_asciiColorCode  The ASCII color code to insert.
     *
     * @todo Add an indirection such that subclasses can use polymorphic behaviour with
     * <tt> operator<< </tt>. See <a href="http://stackoverflow.com/questions/4571611/
     * making-operator-virtual"> this </a> for a nice hot-to example.
     *
     **********************************************************************************************/
    friend std::ostream& operator<<(std::ostream& p_flux, const AsciiColorCode& p_asciiColorCode);
///@}


protected:

    virtual void checkInvariant() const;


private:

    char m_asciiColorCode; ///< The ASCII color code.

};

END_CXBASE_NAMESPACE

#endif // ASCIICOLORCODE_H_
