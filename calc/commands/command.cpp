#include "command.h"
#include "../result.h"

Command::Command(Result *result, double value) :
    m_result(result), m_value(value)
{

}

Result *Command::result() const
{
    return m_result;
}

double Command::value() const
{
    return m_value;
}
