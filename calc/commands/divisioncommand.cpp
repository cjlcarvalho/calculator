#include "divisioncommand.h"
#include "result.h"

DivisionCommand::DivisionCommand(Result *result, double value) :
    Command(result, value)
{

}

void DivisionCommand::undo()
{
    result()->multiply(value());
}

void DivisionCommand::redo()
{
    result()->divide(value());
}
