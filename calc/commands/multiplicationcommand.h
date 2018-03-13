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

private:
    Result *m_result;
    double m_value;
};

#endif // MULTIPLICATIONCOMMAND_H
