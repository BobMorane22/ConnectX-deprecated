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
 * @file    Assertion.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Assertion framework.
 *
 **************************************************************************************************/

#ifndef ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C
#define ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C

#if !defined(NDEBUG)

#include <cassert>
#include <iostream>

#define CX_ASSERT(__condition__)                                          \
{                                                                         \
    if(!(__condition__))                                                  \
    {                                                                     \
        std::cerr << "Assertion failed!"                 << std::endl;    \
        std::cerr <<   "  Condition : " << #__condition__ << std::endl;   \
        std::cerr <<   "  File      : " << __FILE__       << std::endl;   \
        std::cerr <<   "  Line      : " << __LINE__       << std::endl;   \
        std::cerr <<   "  Function  : " << __FUNCTION__   << std::endl;   \
        abort();                                                          \
    }                                                                     \
}

#define CX_ASSERT_MSG(__condition__, __message__)                         \
{                                                                         \
    if(!(__condition__))                                                  \
    {                                                                     \
        std::cerr << "Assertion failed!"                 << std::endl;    \
        std::cerr <<   "  Condition : " << #__condition__ << std::endl;   \
        std::cerr <<   "  Message   : " << __message__    << std::endl;   \
        std::cerr <<   "  File      : " << __FILE__       << std::endl;   \
        std::cerr <<   "  Line      : " << __LINE__       << std::endl;   \
        std::cerr <<   "  Function  : " << __FUNCTION__   << std::endl;   \
        abort();                                                          \
    }                                                                     \
}                                                                         \

#else

#define CX_ASSERT(__condition__)                                  (__condition__)
#define CX_ASSERT_MSG(__condition__, __message__)                 (__condition__)

#endif

// Source: http://thesoftwarecondition.com/blog/2010/08/01/cc-assertions-and-defining-your-own-assert-macro/

#endif /* ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C */
