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
 * @file    ContractException.h
 * @author  ULaval
 * @author  Eric Poirier (translation)
 * @date    January 2014
 * @version 1.0
 *
 * Interfaces for the <a href="https://en.wikipedia.org/wiki/Design_by_contract">
 * design-by-contract </a> exceptions classes and MACROs.
 *
 **************************************************************************************************/


#ifndef CONTRACTEXCEPTION_H_
#define CONTRACTEXCEPTION_H_

#include <string>
#include <stdexcept>

/***********************************************************************************************//**
 * @class ContractException
 *
 * Basis for design-by-contract type exceptions.
 *
 * Defines a common anatomy for design-by-contract type exceptions. Each of these exceptions
 * must document four key components: the file and line where the exception is thrown, the
 * expression throwing the exception and the message carried by the exception. All
 * design-by-contract exceptions must at least inherit from this class.
 *
 * @see AssertionException
 * @see PreconditionException
 * @see PostconditionException
 *
 **************************************************************************************************/
class ContractException: public std::logic_error
{

public:

     /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Feeds the ContratException object with the basic information about the exception.
     *
     * @param[in] p_file        The file in which the exception was thrown.
     * @param[in] p_line        The line at which the exception was thrown.
     * @param[in] p_expression  The logical test that has failed (and thrown the exception)
     * @param[in] p_message     A message describing the exception.
     *
     **********************************************************************************************/
    ContractException(
                      std::string p_file,
                      unsigned int p_line,
                      std::string p_expression,
                      std::string p_message
                      ): logic_error{p_message},
                         m_expression{p_expression},
                         m_file{p_file},
                         m_line{p_line}{}


    /*******************************************************************************************//**
    * Destructor.
    *
    **********************************************************************************************/
    ~ContractException() {};


    /*******************************************************************************************//**
    * Constructs a complete string describing the contract error.
    *
    * Constructs an @c std::string containing all the information about the contract error (file,
    * line, test failed and message).
    *
    * @return An @c std::string containing the complete contract error information.
    *
    **********************************************************************************************/
    std::string getTextException() const;

private:

    std::string     m_expression;   ///< The test that has failed (by contract).
    std::string     m_file;         ///< The file in which the failed test is located.
    unsigned int    m_line;         ///< The line in which the failed test is located.

};


/***********************************************************************************************//**
 * @class AssertionException
 *
 * Class for assertion errors management.
 *
 * In this context, an <a href="https://en.wikipedia.org/wiki/Assertion_(software_development)">
 * assertion </a> is a predicate that is expected to be true at a specific point in the program.
 *
 * @see ContractException
 **************************************************************************************************/
class AssertionException: public ContractException
{

public:

    /*******************************************************************************************//**
    * Constructor with parameters.
    *
    * Feeds the AssertionException object with the basic information about the exception.
    *
    * @param[in] p_file        The file in which the exception was thrown.
    * @param[in] p_line        The line at which the exception was thrown.
    * @param[in] p_expression  The logical test that has failed (and thrown the exception)
    *
    * @note In this specialized case of the ContractException, the message is internally set
    * to <tt> ASSERTION ERROR </tt>
    *
    **********************************************************************************************/
    AssertionException(
                       std::string p_file,
                       unsigned int p_line,
                       std::string p_expression
                       ): ContractException(
                                            p_file,
                                            p_line,
                                            p_expression,
                                            "ASSERTION ERROR"
                                            ){}

};


/***********************************************************************************************//**
 * @class PreconditionException
 *
 * Class for precondition errors management.
 *
 * In this context, an <a href="https://en.wikipedia.org/wiki/Precondition"> precondition </a> is a
 * predicate that is expected to be true before the execution of a certain section of code.
 *
 * @see ContractException
 *
 **************************************************************************************************/
class PreconditionException: public ContractException
{

public:

    /******************************************************************************************//**
    * Constructor with parameters.
    *
    * Feeds the PreconditionException object with the basic information about the exception.
    *
    * @param[in] p_file        The file in which the exception was thrown.
    * @param[in] p_line        The line at which the exception was thrown.
    * @param[in] p_expression  The logical test that has failed (and thrown the exception)
    *
    * @note In this specialized case of the ContractException, the message is internally set
    * to <tt> PRECONDITION ERROR </tt>
    *
    **********************************************************************************************/
    PreconditionException(std::string p_file,
                          unsigned int p_line,
                          std::string p_expression
                          ): ContractException(
                                               p_file,
                                               p_line,
                                               p_expression,
                                               "PRECONDITION ERROR"
                                               ){}

};


/***********************************************************************************************//**
 * @class PostconditionException
 *
 * Class for postcondition errors management.
 *
 * In this context, an <a href="https://en.wikipedia.org/wiki/Postcondition"> postcondition </a>
 * is a predicate that is expected to be true before the execution of a certain section of code.
 *
 * @see ContractException
 *
 **************************************************************************************************/
class PostconditionException: public ContractException
{

public:

    /******************************************************************************************//**
    * Constructor with parameters.
    *
    * Feeds the PostconditionException object with the basic information about the exception.
    *
    * @param[in] p_file        The file in which the exception was thrown.
    * @param[in] p_line        The line at which the exception was thrown.
    * @param[in] p_expression  The logical test that has failed (and thrown the exception)
    *
    * @note In this specialized case of the ContractException, the message is internally set
    * to <tt> POSTCONDITION ERROR </tt>
    *
    **********************************************************************************************/
    PostconditionException(std::string p_file,
                           unsigned int p_line,
                           std::string p_expression
                           ): ContractException(
                                                p_file,
                                                p_line,
                                                p_expression,
                                                "POSTCONDITION ERROR"
                                                ){}

};


/***********************************************************************************************//**
 * @class InvariantException
 *
 * Class for class invariant errors management.
 *
 * In this context, an <a href="https://en.wikipedia.org/wiki/Class_invariant"> invariant </a>
 * is a predicate that is expected to be true before the execution of a certain section of code.
 *
 * @see ContractException
 *
 **************************************************************************************************/
class InvariantException: public ContractException
{

public:

    /******************************************************************************************//**
    * Constructor with parameters.
    *
    * Feeds the InvariantException object with the basic information about the exception.
    *
    * @param[in] p_file        The file in which the exception was thrown.
    * @param[in] p_line        The line at which the exception was thrown.
    * @param[in] p_expression  The logical test that has failed (and thrown the exception)
    *
    * @note In this specialized case of the ContractException, the message is internally set
    * to <tt> INVARIANT ERROR </tt>
    *
    **********************************************************************************************/
    InvariantException(
                       std::string p_file,
                       unsigned int p_line,
                       std::string p_expression
                       ): ContractException(
                                            p_file,
                                            p_line,
                                            p_expression,
                                            "INVARIANT ERROR"
                                            ){}

};




#if !defined(NDEBUG)
// --- Debug mode (all design-by-contract checks are activated).

/***********************************************************************************************//**
 * @def INVARIANTS()
 *
 * Checks the state an object.
 *
 * The MACRO calls the @c checkInvariant() method (which has to be defined by the developper for
 * each class). This methods checks the state of various @a invariants (also defined by the class
 * developper). For example, if you have a @c People class which has a @c name member. An invariant
 * for this class could be that the @c name member should never be empty. Thus, at every time,
 * if you want your object to be valid, you should check that the @c name member is not empty
 * (i.e. the invariant is respected). This is done using this MACRO.
 *
 * The nice thing about the @c checkInvariant() method is that it enables the developper to
 * check many invariants all at once. This is especially easy with this MACRO.
 *
 **************************************************************************************************/
# define INVARIANTS() \
    checkInvariant()


/***********************************************************************************************//**
 * @def ASSERTION(f)
 *
 * Checks the validity of a predicate @c f.
 *
 * This MACRO is usually used as a checkpoint inside a complex procedure to validate the state of
 * the procedure so far. This MACRO should not be used as Pre/postconditions checks.
 *
 * @throw   AssertionException if @c f is not valid.
 * @note    Should not be used in constant methods.
 * @see     AssertionException
 *
 **************************************************************************************************/
# define ASSERTION(f)     \
    if (!(f)) throw AssertionException(__FILE__,__LINE__, #f);


/***********************************************************************************************//**
 * @def PRECONDITION(f)
 *
 * Checks the validity of a predicate @c f to determine if the preconditions for the contract are
 * met.
 *
 * This MACRO is usually used as the first step(s) in a method implementation, to check wether
 * the contract's preconditions are met.
 *
 * @throw   PreconditionException if @c f is not valid (i.e. the requierements for the contract
 *          are not met).
 * @note    Should not be used in constant methods.
 * @see     PreconditionException
 *
 **************************************************************************************************/
#  define PRECONDITION(f)  \
    if (!(f)) throw PreconditionException(__FILE__, __LINE__, #f);


/***********************************************************************************************//**
 * @def POSTCONDITION(f)
 *
 * Checks the validity of a predicate @c f to determine if the postconditions for the contract
 * are met.
 *
 * This MACRO is usually used as the step(s) coming right after the body of a method
 * implementation, to check wether the contract's postconditions are met.
 *
 * @throw   PreconditionException if "f" is not valid (i.e. the requierements for the contract
 *          are not met).
 * @note    Should not be used in constant methods.
 * @see     PostconditionException
 **************************************************************************************************/
#  define POSTCONDITION(f) \
      if (!(f)) throw PostconditionException(__FILE__, __LINE__, #f);


/***********************************************************************************************//**
 * @def INVARIANT(f)
 *
 * Checks the validity of @a one predicate @c f to determine if an invariant (only one) is valid.
 *
 * This MACRO usually is used in two distinct ways:
 *     @li to check the validity of a unique/specific invariant, i.e. an invariant that cannot
 *         be treated in the @c checkInvariant() method;
 *     @li to implement the @c checkInvariant() method.
 *
 * @throw   InvariantException If @c f is not valid.
 * @see     InvariantException
 **************************************************************************************************/
#  define INVARIANT(f)   \
      if (!(f)) throw InvariantException(__FILE__,__LINE__, #f);


// --- Release mode (all design-by-contract checks are desactivated).
#else

#  define PRECONDITION(f);
#  define POSTCONDITION(f);
#  define INVARIANTS();
#  define INVARIANT(f);
#  define ASSERTION(f);

#endif  // --- if !defined (NDEBUG)
#endif  // --- ifndef CONTRACTEXCEPTION_H_

/***********************************************************************************************//**
 * A classic usage of these design-by-contract exceptions and MACROs can be summarized by these
 * steps:
 *      @li Implement the @c checkInvariant() methods with the following signature: <tt>
 *          void checkInvariant() const </tt>. In the method body, use the @c INVARIANT(f) MACRO
 *          to test <em> for each </em> class invariant. Each class invariant @c f must be
 *          implemented as a predicate (something that evaluates to @c true or @c false). If the
 *          class requires the verification of five (5) class invariants, then use the MACRO five
 *          times, with the 5 respective predicates. Note that sometimes, a class has no invariant.
 *          In this case, do not define the @a checkInvariant() method.
 *
 *      @li For each method that needs to have precondition(s) verified to ensure a correct
 *          behaviour, use the @c PRECONDITION(f) MACRO in the body. Again, Each class invariant
 *          @c f must be implemented as a predicate. The MACRO must be included in the method body
 *          <em> before any other line of code is written </em> for good results. If the method
 *          requires the verification of five (5) preconditions, then use the MACRO five times,
 *          with the 5 respective predicates.
 *
 *      @li Just like for preconditions, add the required number of postconditions MACROs <em> at
 *          the end of the method body. </em> These MACROs must be the last code to be executed
 *          before a @c return statement, or the method's end of scope if no class invariant are
 *          defined. Otherwise, they must be the last code to be executed before the
 *          @c INVARIANTS() MACRO (notice the @a S !).
 *
 *      @li If you have defined class invariant in the first step, add the @c INVARIANTS()
 *          (notice the @a S !) MACRO before the method's @c return statement, or before the method
 *          goes out of scope for void methods.
 *
 * Furthermore, if you have complicated methods, in every step of the method's body, you can add
 * the @c ASSERTION(f) MACRO to test a predicate @c f. The following example shows how all these
 * tools can be combined.
 *
 * @example DesignByContract.h
 *
 **************************************************************************************************/
