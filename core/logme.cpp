#include "logme.h"
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

LogMe::LogMe(QObject *parent) :
    QObject(parent)
{
    if (parent == 0) {
        return;
    }

    _className  = parent->metaObject()->className();

}

void LogMe::debug(const QString &debugMessage)
{
    this->logMessage("debug", debugMessage);
}

void LogMe::info(const QString &infoMessage)
{
    this->logMessage("info", infoMessage);
}

void LogMe::success(const QString &successMessage)
{
    this->logMessage("success", successMessage);
}

void LogMe::error(const QString &errorMessage)
{
    this->logMessage("error", errorMessage);
}

void LogMe::setClassName(const QString &className)
{
    _className = className;
}

void LogMe::logMessage(const QString &logLevel, const QString &logMessage) const
{
    qDebug() << QString("%1::%2 %3 %4").arg(_className,
                                            logLevel.toUpper(),
                                            QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz"),
                                            logMessage);
}

