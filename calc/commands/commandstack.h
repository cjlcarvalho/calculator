#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <QList>

class Command;

class CommandStack
{
public:
    CommandStack();
    ~CommandStack();
    void addCommand(Command *command);
    bool undoCommand();
    bool redoCommand();
    QList<Command *> commands() const;
    void clear();
    void backToStart();

private:
    QList<Command *> m_commands;
    int m_top;
};

#endif // COMMANDSTACK_H
