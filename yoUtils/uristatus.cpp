#include "uristatus.h"

UriStatus::UriStatus(QObject *parent) :
    QObject(parent)
{
}

void UriStatus::setUri(const QString &uri)
{
    _uri = uri;
}

void UriStatus::setStatus(const QString &status)
{
    _status = status;
}

QString UriStatus::uri() const
{
    return _uri;
}

QString UriStatus::status() const
{
    return _status;
}
