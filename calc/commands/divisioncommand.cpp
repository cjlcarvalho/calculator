#include "divisioncommand.h"
#include "result.h"

DivisionCommand::DivisionCommand(Result *result, double value) :
    m_result(result),
    m_value(value)
{

}

void DivisionCommand::undo()
{
    m_result->multiply(m_value);
}

void DivisionCommand::redo()
{
    m_result->divide(m_value);
}
