#include <cxinv/include/assertion.h>

#include "../include/CommandStack.h"


cxcmd::CommandStack::CommandStack(const size_t p_capacity)
 : m_state{p_capacity - 1, 0}
{
    PRECONDITION(p_capacity > 1);

    m_commands.reserve(p_capacity);

    POSTCONDITION(m_state.m_end > 1);
    INVARIANT(m_state.m_end > 1);
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
        return;
    }

    else if(!isFull() && noCommandUndoed())
    {
        m_commands.push_back(std::move(p_command));

        if( !isFull() )
        {
            ++m_state.m_current;
        }
    }
    else
    {
        // Strip all previously undoed commands:
        m_commands.erase(m_commands.cbegin() + m_state.m_current,
                         m_commands.cend());

        m_commands.shrink_to_fit();

        // Add the command:
        m_commands.push_back(std::move(p_command));
        ++m_state.m_current;
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

    if(m_state.m_current != 0)
    {
        m_commands[m_state.m_current - 1]->undo();
        --m_state.m_current;
    }
}


void cxcmd::CommandStack::redo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_state.m_current != m_state.m_end)
    {
        m_commands[m_state.m_current]->execute();
        ++m_state.m_current;
    }
}


bool cxcmd::CommandStack::isEmpty() const
{
    return m_commands.empty();
}


bool cxcmd::CommandStack::isFull() const
{
    return m_state.m_end == m_commands.size() - 1;
}


size_t cxcmd::CommandStack::nbCommands() const
{
    return m_commands.size();
}


bool cxcmd::CommandStack::noCommandUndoed() const
{
    bool areCommandsUndoed{false};

    if(!isFull())
    {
        areCommandsUndoed = m_state.m_current == m_commands.size();
    }
    else
    {
        areCommandsUndoed = m_state.m_current == m_commands.size() - 1;
    }

    return areCommandsUndoed;
}
