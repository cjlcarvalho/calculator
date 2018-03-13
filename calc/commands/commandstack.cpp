#include "commandstack.h"
#include "command.h"

CommandStack::CommandStack()
{
    clear();
}

CommandStack::~CommandStack()
{
    qDeleteAll(m_commands);
}

void CommandStack::addCommand(Command *command)
{   
    while (m_commands.size() > m_top) {
        delete m_commands.last();
        m_commands.removeLast();
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
        m_commands.at(m_top++)->redo();
        return true;
    }
    return false;
}

QList<Command *> CommandStack::commands() const
{
    return m_commands;
}

void CommandStack::clear()
{
    backToStart();
    m_commands.clear();
}

void CommandStack::backToStart()
{
    m_top = 0;
}
