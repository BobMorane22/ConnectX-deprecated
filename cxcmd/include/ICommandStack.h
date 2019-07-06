#pragma once

#include <memory>

#include "ICommand.h"

namespace cxcmd
{

class ICommandStack
{

public:

    virtual ~ICommandStack() = default;

    virtual void add(std::unique_ptr<ICommand>&& p_command) = 0;
    virtual void clear() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual size_t nbCommands() const = 0;
};

} // namespace cxcmd
