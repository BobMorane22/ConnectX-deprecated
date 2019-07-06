#pragma once

namespace cxcmd
{

class ICommand
{

public:

    virtual ~ICommand() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;
};

} // namespace cxcmd