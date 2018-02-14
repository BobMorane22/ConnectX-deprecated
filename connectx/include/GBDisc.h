/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
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
 * @file    GBDisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI gameboard disc utility.
 *
 **************************************************************************************************/

#ifndef GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C
#define GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C

#include <cxbase/include/Disc.h>

#include "CXDisc.h"

namespace cx
{

/***********************************************************************************************//**
 *
 **************************************************************************************************/
class GBDisc : public CXDisc
{

public:

    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    GBDisc();


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    GBDisc(const cxbase::Disc& p_backEndDisc);


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    virtual ~GBDisc();


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    virtual void hide() override;


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    void update(const cxbase::Disc& p_newBackEndDisc);


private:

    cxbase::Disc m_backEndDisc;   ///<
};

} // namespace cx

#endif // GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C
