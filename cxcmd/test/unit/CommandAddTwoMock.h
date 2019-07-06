#pragma once

#include <cxcmd/include/ICommand.h>

class CommandAddTwoMock : public cxcmd::ICommand
{

public:

    CommandAddTwoMock(double& p_data) : m_data{p_data} {}

    virtual void execute() override
    {
        m_data += 2.0;
    }

    virtual void undo() override
    {
        m_data -= 2.0;
    }

private:

    double& m_data;
};