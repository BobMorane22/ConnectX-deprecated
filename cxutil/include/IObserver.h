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
 * Interface for implementing an observer.
 *
 * @file    IObserver.h
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 **************************************************************************************************/

#ifndef IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2
#define IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2


namespace cxutil
{
    class ISubject;
}

namespace cxutil
{

/***********************************************************************************************//**
 * @interface IObserver
 *
 * Implement this interface to make a class an observer. Implementing this interface means 
 * implementing the @c update() method, which describles how an observer is updated when 
 * notified by the subject.
 *
 * @see ISubject
 *
 **************************************************************************************************/
class IObserver
{
public:

    virtual ~IObserver() = default;

    /*******************************************************************************************//**
     * Update observer.
     *
     * This method is automatically called when the ISubject to which the observer has been 
     * registered notifies its observer(s).
     *
     * @param[in] p_subject The subject notifying (hence observed).
     *
     **********************************************************************************************/
    virtual void update(ISubject* p_subject) = 0;
};

} // namespace cxutil

#endif /* IOBSERVER_H_516B2B88_CC83_49D3_8D69_D7AC6A4F72E2 */
