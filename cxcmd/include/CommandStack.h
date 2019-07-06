#pragma once

#include <memory>
#include <vector>

#include "ICommandStack.h"

namespace cxcmd
{

class CommandStack : public ICommandStack
{

public:

    CommandStack(const size_t p_capacity);

    void add(std::unique_ptr<ICommand>&& p_command) override;
    void clear() override;

    void undo() override;
    void redo() override;

    bool isEmpty() const override;
    bool isFull() const override;
    size_t nbCommands() const override;

private:

    bool noCommandUndoed() const;

    struct State
    {
        const std::size_t m_end;
        std::size_t       m_current;
    };

    State                                  m_state;
    std::vector<std::unique_ptr<ICommand>> m_commands;
};

} // namespace cxcmd