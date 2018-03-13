#ifndef COMMAND_H
#define COMMAND_H

class Result;

class Command
{
public:
    virtual ~Command() { }
    virtual void undo() = 0;
    virtual void redo() = 0;
    Result *result() const;
    double value() const;

protected:
    Command(Result *result, double value);

private:
    Result *m_result;
    double m_value;
};

#endif // COMMAND_H
