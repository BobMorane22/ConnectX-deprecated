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
 * @file    NDADisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI next disc area disc utility.
 *
 **************************************************************************************************/

#ifndef NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7
#define NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7

#include <cxbase/include/Disc.h>

#include "CXDisc.h"

namespace cx
{

/***********************************************************************************************//**
 *
 **************************************************************************************************/
class NDADisc : public CXDisc
{

public:

    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    NDADisc();


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    NDADisc(const cxbase::Disc& p_backEndDisc);


    /*******************************************************************************************//**
     *
     *
     **********************************************************************************************/
    virtual ~NDADisc();


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

#endif // NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7
