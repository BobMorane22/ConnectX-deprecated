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
 * @file    IEnforceContract.h
 * @author  Eric Poirier
 * @date    December 2016
 * @version 0.1
 *
 * Interface for design-by-contract enforcement. Note that all the services defined in this file
 * only have meaning in debug mode, i.e. if the constant @c NDEBUG is @a not defined.
 *
 **************************************************************************************************/

#ifndef IENFORCECONTRACT_H_C97649B0_072C_4320_952D_D6E7DF1D98D0
#define IENFORCECONTRACT_H_C97649B0_072C_4320_952D_D6E7DF1D98D0

#include "ContractException.h"
#include "../src/cxutilInternal.h"

BEGIN_CXUTIL_NAMESPACE

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
     * validation). Only apply if @c NDEBUG is @a not defined.
     *
     **********************************************************************************************/
    virtual void checkInvariant() const = 0;
};

END_CXUTIL_NAMESPACE

#endif /* IENFORCECONTRACT_H_C97649B0_072C_4320_952D_D6E7DF1D98D0 */
