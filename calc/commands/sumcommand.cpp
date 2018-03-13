#include "sumcommand.h"
#include "result.h"

SumCommand::SumCommand(Result *result, double value) :
    m_result(result),
    m_value(value)
{

}

void SumCommand::undo()
{
    m_result->add(-m_value);
}

void SumCommand::redo()
{
    m_result->add(m_value);
}
