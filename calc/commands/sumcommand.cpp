#include "sumcommand.h"
#include "result.h"

SumCommand::SumCommand(Result *result, double value) :
    Command(result, value)
{

}

void SumCommand::undo()
{
    result()->add(-value());
}

void SumCommand::redo()
{
    result()->add(value());
}
