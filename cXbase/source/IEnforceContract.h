/***********************************************************************************************//**
 * @file    IEnforceContract.h
 * @author  Eric Poirier
 * @date    December 2016
 * @version 0.1
 *
 * Interface for design-by-contract enforcement.
 *
 **************************************************************************************************/

#ifndef IENFORCECONTRACT_H_
#define IENFORCECONTRACT_H_

#include "ContractException.h"
#include "cXbaseInternal.h"

BEGIN_CXBASE_NAMESPACE

/***********************************************************************************************//**
 * class IEnforceContract
 *
 * Interface for design-by-contract enforcement.
 *
 * Once inherited from, this interface forces the user to implement the @c checkInvariant() method
 * neccessary for the class invariant checks.
 *
 * @see ContractException.h
 *
 **************************************************************************************************/
class IEnforceContract
{

public:

    virtual ~IEnforceContract() {};


protected:

    /*******************************************************************************************//**
     * Mandatory method for design-by-contract implementation (most precisely, for class invariants
     * validation).
     *
     **********************************************************************************************/
    virtual void checkInvariant() const = 0;
};

END_CXBASE_NAMESPACE

#endif /* IENFORCECONTRACT_H_ */
