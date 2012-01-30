#ifndef URISTATUS_H
#define URISTATUS_H

#include <QObject>

class UriStatus : public QObject
{
    Q_OBJECT
public:
    explicit UriStatus(QObject *parent = 0);

    void setUri(const QString &uri);
    void setStatus(const QString &status);

    QString uri() const;
    QString status() const;

private:
    QString _uri;
    QString _status;
};

#endif // URISTATUS_H
