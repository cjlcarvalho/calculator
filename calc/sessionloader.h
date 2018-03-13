#ifndef SESSIONLOADER_H
#define SESSIONLOADER_H

#include <QList>
#include <QString>

class Command;
class CommandStack;
class Result;

class SessionLoader
{
public:
    SessionLoader(const QString &fileName);
    bool isSessionAvailable() const;
    void loadSession(Result *result, CommandStack *commandStack);
    void saveSession(CommandStack *commandStack);

private:
    QString m_fileName;
    bool m_loaded;
};

#endif // SESSIONLOADER_H
