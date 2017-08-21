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
 * Implementation for the interface ISubject.
 *
 * @file    ISubject.cpp
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 **************************************************************************************************/

#include <algorithm>
#include <cassert>

#include "ISubject.h"

using namespace cxutil;

/**************************************************************************************************************//**
 *
 * Destructor.
 *
 *****************************************************************************************************************/
ISubject::~ISubject()
{
    m_observers.clear();
}

/**************************************************************************************************************//**
 *
 * Register a new observer so that it gets notified on subject update.
 *
 *****************************************************************************************************************/
void ISubject::registerObserver( IObserver* p_observer )
{
    assert( p_observer != nullptr );

    std::list< IObserver* const >::const_iterator position;

    // First, we check if the observer is already registered:
    position = std::find( m_observers.begin(), m_observers.end(), p_observer );

    bool observerNotYetRegistered { position == m_observers.end() };

    if( observerNotYetRegistered )
    {
        // Observer not yet registered.
        // We register it:
        m_observers.push_back( p_observer );
    }
}

/**************************************************************************************************************//**
 *
 * Removes a registered observer from the list of registered observers so that it is not notified by the 
 * subject anymore.
 *
 *****************************************************************************************************************/
void ISubject::removeObserver( IObserver* p_observer )
{
    assert( p_observer != nullptr );

    std::list< IObserver* const >::const_iterator position;

    // First, we check if the observer is registered:
    position = std::find( m_observers.begin(), m_observers.end(), p_observer );

    bool observerRegistered { position != m_observers.end() };

    if( observerRegistered )
    {
        m_observers.erase( position );
    }
}

/**************************************************************************************************************//**
 *
 * Notify all observers that the subject's state has changed.
 *
 *****************************************************************************************************************/
void ISubject::notifyObservers()
{
    for ( auto& observer : m_observers )
    {
        observer->update( this );
    }
}
