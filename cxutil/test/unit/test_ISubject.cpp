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
 * @file    test_ISubject.cpp
 * @author  Eric Poirier
 * @date    September 2017
 * @version 1.0
 *
 * Unit tests for a the ISubject and the IObserver interfaces.
 *
 **************************************************************************************************/


#include <gtest/gtest.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/IObserver.h>
#include <cxutil/include/ISubject.h>

#include "Incrementer.h"

using namespace cxutil;


TEST(ISubject, RegisterObserver_ObserverRegisteredTwice_RegistrationIgnored)
{
    Incrementer t_subject;

    ChecksForIncrement t_observer;

    t_subject.registerObserver(&t_observer);
    t_subject.registerObserver(&t_observer);

    t_subject.increment();

    ASSERT_TRUE(t_observer.hasBeenIncremented());
}


TEST(ISubject, RemoveObserver_ObserverRegisteredTwice_RegistrationIgnored)
{
    Incrementer t_subject;

    ChecksForIncrement t_observer;

    t_subject.registerObserver(&t_observer);
    t_subject.removeObserver(&t_observer);
    t_subject.removeObserver(&t_observer);

    t_subject.increment();

    ASSERT_FALSE(t_observer.hasBeenIncremented());
}


TEST(ISubject, NotifyObservers_TwoObserversNoAccess_ObserversNotified)
{
    Incrementer t_subject;

    ChecksForIncrement t_observer1;
    ChecksForIncrement t_observer2;

    t_subject.registerObserver(&t_observer1);
    t_subject.registerObserver(&t_observer2);

    t_subject.increment();

    ASSERT_TRUE(t_observer1.hasBeenIncremented() && t_observer2.hasBeenIncremented());
}


TEST(ISubject, NotifyObservers_TwoObserversWithAccess_ObserversNotified)
{
    Incrementer t_subject;

    CopiesIncrementerData t_observer1;
    CopiesIncrementerData t_observer2;

    t_subject.registerObserver(&t_observer1);
    t_subject.registerObserver(&t_observer2);

    t_subject.increment();

    ASSERT_TRUE(t_observer1.data() == 1 && t_observer2.data() == 1);
}

TEST(ISubject, NotifyObservers_TwoObserversOneUnregisteredNoAccess_RegisteredObserverNotifiedOnly)
{
    Incrementer t_subject;

    ChecksForIncrement t_observer1;
    ChecksForIncrement t_observer2;

    t_subject.registerObserver(&t_observer1);

    t_subject.increment();

    ASSERT_TRUE(t_observer1.hasBeenIncremented() && !t_observer2.hasBeenIncremented());
}


TEST(ISubject, NotifyObservers_TwoObserversOneUnregisteredWithAccess_RegisteredObserverNotifiedOnly)
{
    Incrementer t_subject;

    CopiesIncrementerData t_observer1;
    CopiesIncrementerData t_observer2;

    t_subject.registerObserver(&t_observer1);

    t_subject.increment();

    ASSERT_TRUE(t_observer1.data() == 1 && t_observer2.data() == 0);
}


TEST(ISubject, NotifyObservers_TwoObserversTwoKinds_ObserversNotified)
{
    Incrementer t_subject;

    ChecksForIncrement    t_observer1;
    CopiesIncrementerData t_observer2;

    t_subject.registerObserver(&t_observer1);
    t_subject.registerObserver(&t_observer2);

    t_subject.increment();

    ASSERT_TRUE(t_observer1.hasBeenIncremented() && t_observer2.data() == 1);
}
