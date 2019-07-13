#include <cxinv/include/assertion.h>

#include "../include/CommandStack.h"


cxcmd::CommandStack::CommandStack(const size_t p_capacity)
 : m_currentPosition{0}
 , m_endPosition{p_capacity - 1}
 , m_allCmdUndoed{false}
{
    PRECONDITION(p_capacity > 1);

    m_commands.reserve(p_capacity);

    POSTCONDITION(m_endPosition > 1);
    INVARIANT(m_endPosition > 1);
}


void cxcmd::CommandStack::add(std::unique_ptr<cxcmd::ICommand>&& p_command)
{
    PRECONDITION(p_command != nullptr);

    if(!p_command)
    {
        return;
    }

    if(isFull() && noCommandUndoed())
    {
        m_commands.erase(m_commands.cbegin());
        m_commands.push_back(std::move(p_command));
    }
    else if(!isFull() && noCommandUndoed())
    {
        m_commands.push_back(std::move(p_command));

        // If this is the first added command, the current position
        // is still 0.
        if(m_commands.size() != 1)
        {
            ++m_currentPosition;
        }
    }
    else
    {
        // Strip all previously undoed commands:
        m_commands.erase(m_commands.cbegin() + m_currentPosition,
                         m_commands.cend());

        m_commands.shrink_to_fit();

        // Add the command:
        m_commands.push_back(std::move(p_command));
        ++m_currentPosition;
    }
}


void cxcmd::CommandStack::clear()
{
    m_commands.clear();
}


void cxcmd::CommandStack::undo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition != 0)
    {
        m_commands[m_currentPosition]->undo();
        --m_currentPosition;
    }
    else if(m_currentPosition == 0 && !m_allCmdUndoed)
    {
        m_commands[m_currentPosition]->undo();
        m_allCmdUndoed = true;
    }
}


void cxcmd::CommandStack::redo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition == 0)
    {
        m_allCmdUndoed = false;
    }

    if(m_currentPosition != m_endPosition)
    {
        m_commands[m_currentPosition]->execute();
        ++m_currentPosition;
    }
}


bool cxcmd::CommandStack::isEmpty() const
{
    return m_commands.empty();
}


bool cxcmd::CommandStack::isFull() const
{
    return m_endPosition == lastCmdPosition();
}


size_t cxcmd::CommandStack::nbCommands() const
{
    return m_commands.size();
}


bool cxcmd::CommandStack::noCommandUndoed() const
{
    if(m_commands.empty())
    {
        return true;
    }

    return m_currentPosition == lastCmdPosition();
}


size_t cxcmd::CommandStack::lastCmdPosition() const
{
    return m_commands.size() - 1;
}
