#include "multiplicationcommand.h"
#include "result.h"

MultiplicationCommand::MultiplicationCommand(Result *result, double value) :
    Command(result, value)
{

}

void MultiplicationCommand::undo()
{
    result()->divide(value());
}

void MultiplicationCommand::redo()
{
    result()->multiply(value());
}
