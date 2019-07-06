#pragma once

#include <cxcmd/include/ICommand.h>

class CommandTimesThreeMock : public cxcmd::ICommand
{

public:

    CommandTimesThreeMock(double& p_data) : m_data{p_data} {}

    virtual void execute() override
    {
        m_data *= 3.0;
    }

    virtual void undo() override
    {
        m_data /= 3.0;
    }

private:

    double& m_data;
};