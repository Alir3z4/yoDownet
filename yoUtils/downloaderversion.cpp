#include "downloaderversion.h"

DownloaderVersion::DownloaderVersion(QObject *parent) :
    QObject(parent)
{
}

void DownloaderVersion::setFaultCode(const int &faultCode)
{
    _faultCode = faultCode;
}

void DownloaderVersion::setFaultString(const QString &faultString)
{
   _faultString = faultString;
}

int DownloaderVersion::faultCode() const
{
    return _faultCode;
}

QString DownloaderVersion::faultString() const
{
    return _faultString;
}
