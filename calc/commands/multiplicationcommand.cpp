#include "multiplicationcommand.h"
#include "result.h"

MultiplicationCommand::MultiplicationCommand(Result *result, double value) :
    m_result(result),
    m_value(value)
{

}

void MultiplicationCommand::undo()
{
    m_result->divide(m_value);
}

void MultiplicationCommand::redo()
{
    m_result->multiply(m_value);
}
