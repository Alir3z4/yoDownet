#include "downloaderversion.h"

DownloaderVersion::DownloaderVersion(QObject *parent) :
    QObject(parent)
{
}

void DownloaderVersion::setVersion(const QString &version)
{
    _version = version;
}

void DownloaderVersion::setEnabledFeatures(const QStringList &enabledFeatures)
{
    _enabledFeatures = enabledFeatures;
}

QString DownloaderVersion::version() const
{
    return _version;
}

QStringList DownloaderVersion::enabledFeatures() const
{
    return _enabledFeatures;
}

