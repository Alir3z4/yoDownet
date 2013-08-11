#ifndef LOGME_H
#define LOGME_H

#include <QObject>

class LogMe : public QObject
{
    Q_OBJECT
public:
    explicit LogMe(QObject *parent = 0);

    void debug(const QString &debugMessage);
    void info(const QString &infoMessage);
    void success(const QString &successMessage);
    void error(const QString &errorMessage);

    void setClassName(const QString &className);

private:
    QString _className;

    void logMessage(const QString &logLevel, const QString &logMessage) const;
};

#endif // LOGME_H
