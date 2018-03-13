#ifndef SUMCOMMAND_H
#define SUMCOMMAND_H

#include "command.h"

#include <QtGlobal>

class Result;

class SumCommand : public Command
{
public:
    SumCommand(Result *result, double value);
    void undo() override;
    void redo() override;

private:
    Result *m_result;
    double m_value;
};

#endif // SUMCOMMAND_H
