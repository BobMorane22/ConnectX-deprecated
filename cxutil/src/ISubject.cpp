/**************************************************************************************************************//**
 *
 * Implementation for the interface ISubject.
 *
 * @file    ISubject.cpp
 * @author  Éric Poirier
 * @version 1.0
 * @date    August, 2017
 *
 ******************************************************************************************************************/

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