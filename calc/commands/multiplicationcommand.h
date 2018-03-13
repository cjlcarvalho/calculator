#ifndef MULTIPLICATIONCOMMAND_H
#define MULTIPLICATIONCOMMAND_H

#include "command.h"

class Result;

class MultiplicationCommand : public Command
{
public:
    MultiplicationCommand(Result *result, double value);
    void undo() override;
    void redo() override;
};

#endif // MULTIPLICATIONCOMMAND_H
