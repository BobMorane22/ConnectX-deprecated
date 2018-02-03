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
 * @file    Incrementer.h
 * @author  Eric Poirier
 * @date    September 2017
 * @version 1.0
 *
 * Implementations of the ISubject and the IObserver interfaces for testing.
 *
 * @see test_ISubject.cpp
 *
 **************************************************************************************************/

#ifndef INCREMENTER_H_5270186B_C2DA_4DAA_AD38_51A070927F8B
#define INCREMENTER_H_5270186B_C2DA_4DAA_AD38_51A070927F8B


#include <cxutil/include/IObserver.h>
#include <cxutil/include/ISubject.h>

/***********************************************************************************************//**
 * @class Incrementer
 *
 * Implementations of the ISubject interface. When the @c increment() method is called, the 
 * object's data member is incremented and all the registered observers are notified.
 *
 * @see ISubject
 *
 **************************************************************************************************/
class Incrementer : public cxutil::ISubject
{
public:

    Incrementer(){}
    ~Incrementer() = default;

    void increment()
    {
        ++m_data;
        notifyObservers();
    }

    int data() const {return m_data;}

private:

    int m_data{0};
};


/***********************************************************************************************//**
 * @class ChecksForIncrement
 *
 * Implementations of the IObserver interface. The class is designed to test if an Incrementer 
 * object has incremented its data member (in testing). A ChecksForIncrement object does not need 
 * access to the observed Subject object.
 *
 * @see ISubject
 * @see IObserver
 * @see Incrementer
 *
 **************************************************************************************************/
class ChecksForIncrement : public cxutil::IObserver
{
public:

    ChecksForIncrement(){}
    ~ChecksForIncrement() = default;

    void update(cxutil::ISubject* p_subject)
    {
        (void)p_subject;
        m_hasBeenIncremented = true;
    }

    bool hasBeenIncremented() const {return m_hasBeenIncremented;}

private:

    bool m_hasBeenIncremented{false};
};


/***********************************************************************************************//**
 * @class CopiesIncrementerData
 *
 * Implementations of the IObserver interface. The class is designed to test if an Incrementer 
 * object has incremented its data member (in testing). A ChecksForIncrement object needs 
 * access to the observed Subject object for it makes a copy of its incremented data member.
 *
 * @see ISubject
 * @see IObserver
 * @see Incrementer
 *
 **************************************************************************************************/
class CopiesIncrementerData : public cxutil::IObserver
{
public:

    CopiesIncrementerData(){}
    ~CopiesIncrementerData() = default;

    void update(cxutil::ISubject* p_subject)
    {
        Incrementer* incrementer {dynamic_cast<Incrementer*>(p_subject)};
        CX_ASSERT(incrementer != nullptr);

        m_data = incrementer->data();
    }

    int data() const {return m_data;}

private:

    int m_data{0};
};

#endif // INCREMENTER_H_5270186B_C2DA_4DAA_AD38_51A070927F8B
