#ifndef RESULT_H
#define RESULT_H

#include <QString>

class Result
{
public:
    Result(double number);
    void add(double value);
    void multiply(double value);
    void divide(double value);
    QString toString() const;

private:
    double m_number;
};

#endif // RESULT_H
