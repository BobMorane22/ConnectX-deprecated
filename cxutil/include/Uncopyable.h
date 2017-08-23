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
 * @file    UnCopyable.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Interface to make a class uncopyable.
 *
 **************************************************************************************************/

#ifndef UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E
#define UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E

namespace cxutil
{

/***********************************************************************************************//**
 * @class UnCopyable
 *
 * Inherit from this class to make the child class uncopyable. Since UnCopyable is not meant to
 * be used polymorphically, (i.e. we never want to use a pointer to UnCopyable to represent a 
 * derived class) @c private inheritance can be used (and is recommended).
 * 
 * For example:
 *
 * @code{.cpp}
 *
 *   class Foo : private UnCopyable
 *   {
 *       //...
 *   };
 *   
 *   int main()
 *   {
 *       Foo first;
 *       
 *       Foo second{first}; // Not possible!
 *       
 *       // or:
 *       
 *       Foo second;
 *       
 *       second = first; // Not possible!
 *       return 0;
 *   }
 *   
 * @endcode
 *
 **************************************************************************************************/
class Uncopyable
{
protected:
     Uncopyable() = default;
    ~Uncopyable() = default;

private:
    Uncopyable( const Uncopyable& p_object )            = delete;
    Uncopyable& operator=( const Uncopyable& p_object ) = delete;
};

} // namespace cxutil

#endif /* UNCOPYABLE_H_1DAF4EB3_1243_455D_B4D1_9F7DA136B04E */
