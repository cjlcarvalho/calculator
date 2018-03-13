#ifndef DIVISIONCOMMAND_H
#define DIVISIONCOMMAND_H

#include "command.h"

class Result;

class DivisionCommand : public Command
{
public:
    DivisionCommand(Result *result, double value);
    void undo() override;
    void redo() override;

private:
    Result *m_result;
    double m_value;
};

#endif // DIVISIONCOMMAND_H
