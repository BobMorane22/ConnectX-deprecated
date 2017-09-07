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

namespace cxutil
{
    class IObserver;
}

namespace cxutil
{


/***********************************************************************************************//**
 * @class ISubject
 *
 * Implement this interface to make a class observable by other objects (implementing the 
 * IObserver interface). More precisely, an observable object potentially has registered
 * observer interested in certain aspects of its state. When the observable object's state
 * changes, it may notify its observers that its state has changed. The observers then receive 
 * this notification and update themselves automatically according to this new state.
 *
 * Visually:
 *
 * @verbatim
 *
 *                        ---------
 *                        |Subject|   (notifies upon state change)
 *                        ---------
 *                          / | \
 *                       /    |    \
 *                    /       |       \
 *                 /          |          \
 *              /             |             \
 *           /                |                \
 *     ----+-------      -----+------       -----+------
 *     |Observer 1|      |Observer 2|  ...  |Observer n|
 *     ------------      ------------       ------------
 *      (updates)          (updates)          (updates)
 *
 * @endverbatim
 *
 * @see IObserver
 *
 **************************************************************************************************/
class ISubject
{
public:

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~ISubject() = 0;


    /*******************************************************************************************//**
     * Register a new observer.
     *
     * Register a new observer so that it gets notified on subject update. If the observer is
     * already registered, it is ignored and the previous registration still holds.
     *
     * @param[in] p_observer The address of the observer to register.
     *
     **********************************************************************************************/
    void registerObserver(IObserver* p_observer);


    /*******************************************************************************************//**
     * Remove registered observer.
     *
     * Removes a registered observer from the list of registered observers so that it is not 
     * notified by the subject anymore. If the adress is not that of a registered observer, 
     * nothing is done.
     *
     * @param[in] p_observer The address of the observer to remove.
     *
     **********************************************************************************************/
    void removeObserver(IObserver* p_observer);


    /*******************************************************************************************//**
     * Notify observers.
     *
     * Notify all observers that the subject's state has changed. All registered observers 
     * update themselves according to their implementation.
     *
     **********************************************************************************************/
    void notifyObservers();

private:

    std::list<IObserver* const> m_observers; ///< A collection of all registered observers.
};

} // namespace cxutil

#endif /* ISUBJECT_H_56D25704_804C_4CDF_B21_EAD8AF51BF36 */

/***********************************************************************************************//**
 * @example Observers
 *
 * To observe change of state from an object. The ISubject and IObserver interfaces need to be 
 * implemented. The class you want to be observable needs to implement the ISubject interface:
 *
 *   @include ISubjectImplementation.cpp
 *
 * Implementing the ISubject interface simply means deriving from it. Only the destrutor is 
 * @c virtual. As we see in the above example, the @c Incrementer class will notify its registered 
 * observer each call of the @c increment() method. The class(es) you want to have notified need 
 * to implement the IObserver interface:
 *
 *   @include IObserverImplementation.cpp
 *
 * In the case of the IObserver interface, the method @c IObserver::update() must be implemented
 * for different classes probably want to be updated differently upon changes in their observed 
 * subject:
 *
 *   @include IObserverUpdateImplementation.cpp
 *
 * In the above examples, the classes @c ChecksForIncrement and @c CopiesIncrementerData both have 
 * the possibility to observe (i.e. they are potential observers) changes in the @c Incrementer 
 * class (the subject). To make instances of @c ChecksForIncrement and @c CopiesIncrementerData 
 * observers, we need to register them with @c Incrementer. Now every time the Incrementer calls 
 * @c increment() , the registered observer are notified. If needed, a @c dynamic_cast can give 
 * access to the subject object. For example:
 *
 *   @include ISubjectUsage.cpp
 *
 * Use the method @c Incrementer::removeObserver() if you want a registered observer to stop being 
 * notified.
 *
 * @see ISubject
 * @see IObserver
 *
 **************************************************************************************************/
