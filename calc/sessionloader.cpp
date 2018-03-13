#include "sessionloader.h"
#include "result.h"
#include "commands/command.h"
#include "commands/commandstack.h"
#include "commands/sumcommand.h"
#include "commands/multiplicationcommand.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

SessionLoader::SessionLoader(const QString &fileName) :
    m_fileName(fileName),
    m_loaded(false)
{

}

bool SessionLoader::isSessionAvailable() const
{
    QDir applicationDir = QDir(QCoreApplication::applicationDirPath());

    return QFile::exists(applicationDir.absoluteFilePath(m_fileName))
            && !m_loaded;
}

void SessionLoader::loadSession(Result *result, CommandStack *commandStack)
{
    if (!isSessionAvailable())
        return;

    result->turnToZero();
    commandStack->clear();

    QDir applicationDir = QDir(QCoreApplication::applicationDirPath());

    QFile file(applicationDir.absoluteFilePath(m_fileName));

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString fileOutput = file.readAll();

    qDebug() << fileOutput;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileOutput.toLocal8Bit());

    QJsonArray jsonArray = jsonDocument.array();

    for (QJsonValue jsonValue : jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();

        Command *command = nullptr;

        if (jsonObject["command"].toString() == "SumCommand")
            command = new SumCommand(result, jsonObject["value"].toDouble());
        else if (jsonObject["command"].toString() == "MultiplicationCommand")
            command = new MultiplicationCommand(result, jsonObject["value"].toDouble());

        if (command)
            commandStack->addCommand(command);
    }

    commandStack->backToStart();

    file.close();

    m_loaded = true;
}

void SessionLoader::saveSession(CommandStack *commandStack)
{
    QDir applicationDir = QDir(QCoreApplication::applicationDirPath());

    QFile file(applicationDir.absoluteFilePath(m_fileName));

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QJsonArray jsonArray;

    for (Command *command : commandStack->commands()) {
        QJsonObject jsonObject;

        if (dynamic_cast<SumCommand *>(command))
            jsonObject.insert("command", QJsonValue("SumCommand"));
        else if (dynamic_cast<MultiplicationCommand *>(command))
            jsonObject.insert("command", QJsonValue("MultiplicationCommand"));

        jsonObject.insert("value", QJsonValue(command->value()));

        jsonArray.append(QJsonValue(jsonObject));
    }

    QJsonDocument jsonDocument(jsonArray);

    if (jsonArray.isEmpty() || jsonDocument.isEmpty()) {
        applicationDir.remove(m_fileName);
        file.close();
        return;
    }

    file.write(jsonDocument.toJson());

    file.close();
}
