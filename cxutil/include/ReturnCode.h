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
 * @file    ReturnCode.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Interface for a return code utility.
 *
 **************************************************************************************************/

#ifndef RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F
#define RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F

#include <string>


namespace cxutil
{

class ReturnCode final
{
public:

    static const std::string NO_MESSAGE;

    enum class Code : int
    {
        OK,       /* Action executes as expected.                                        */
        WARNING,  /* Action does NOT execute as expected. Executable may not be unstable */
        ERROR,    /* Action does NOT execute as expected. Executable is unstable.        */
        CANCEL    /* Action is canceled.                                                 */
    };

     ReturnCode(Code p_code = Code::ERROR, const std::string p_message = NO_MESSAGE);
    ~ReturnCode();

    bool        isOk();
    bool        isWarning();
    bool        isError();
    bool        isCancelled();

    bool        holdsMessage() const;
    bool        isTested() const;

    std::string message() const;
    Code        code() const;

private:

    bool        m_tested   {false      };
    Code        m_code     {Code::ERROR};
    std::string m_message;
};

} // cxutil

#endif /* RETURNCODE_H_98A72660_A669_42ED_8459_55193BA7032F */
