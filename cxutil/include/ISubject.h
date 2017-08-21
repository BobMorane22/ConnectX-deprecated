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
 *
 * Interface for implementing a subject.
 *
 * @file    ISubject.h
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 **************************************************************************************************/

#ifndef ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36
#define ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36

#include <list>

#include "IObserver.h"

namespace cxutil
{

class ISubject
{
public:
    virtual ~ISubject() = 0;

    void registerObserver( IObserver* p_observer );
    void removeObserver( IObserver* p_observer );
    void notifyObservers();

private:
    std::list< IObserver* const > m_observers; ///< A collection of all registered observers.
};

}; // namespace cxutil

#endif /* ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36 */
