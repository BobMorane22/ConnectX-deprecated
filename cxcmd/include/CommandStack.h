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
    size_t lastCmdPosition() const;

    const std::size_t m_endPosition;
    std::size_t       m_currentPosition;
    bool              m_allCmdUndoed;

    std::vector<std::unique_ptr<ICommand>> m_commands;
};

} // namespace cxcmd