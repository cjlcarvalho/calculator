#include "commandstack.h"
#include "command.h"

CommandStack::CommandStack() :
    m_top(0)
{
    m_commands.clear();
}

void CommandStack::addCommand(Command *command)
{
    if (!m_commands.isEmpty()) {
        while (m_commands.size() > m_top) {
            delete m_commands.last();
            m_commands.removeLast();
        }
    }

    m_commands << command;
    m_top++;
}

bool CommandStack::undoCommand()
{
    if (m_top) {
        m_commands.at(--m_top)->undo();
        return true;
    }
    return false;
}

bool CommandStack::redoCommand()
{
    if (m_top < m_commands.size()) {
        m_commands.at(m_top)->redo();
        m_top++;
        return true;
    }
    return false;
}
