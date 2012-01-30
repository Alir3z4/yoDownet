#include "downloaderversion.h"

DownloaderVersion::DownloaderVersion(QObject *parent) :
    QObject(parent)
{
}

void DownloaderVersion::setVersion(const QString &version)
{
    _version = version;
}

void DownloaderVersion::setEnabledFeatures(const QVector<QString> &enabledFeatures)
{
    _enabledFeatures = enabledFeatures;
}

QString DownloaderVersion::version() const
{
    return _version;
}

QVector<QString> DownloaderVersion::enabledFeatures() const
{
    return _enabledFeatures;
}

