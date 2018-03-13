#include "result.h"

Result::Result(double number) :
    m_number(number)
{

}

void Result::add(double value)
{
    m_number += value;
}

void Result::multiply(double value)
{
    m_number *= value;
}

void Result::divide(double value)
{
    m_number /= value;
}

QString Result::toString() const
{
    return QString::number(m_number, 'f');
}

void Result::turnToZero()
{
    m_number = 0;
}
