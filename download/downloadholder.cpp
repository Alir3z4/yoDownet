#include "downloadholder.h"
#include <QtCore/QVariant>

DownloadHolder::DownloadHolder(QObject *parent) :
    QObject(parent)
{
}

QString DownloadHolder::uuid() const
{
    return _uuid;
}

void DownloadHolder::setUuid(const QString &uuid)
{
    _uuid = uuid;
}

QString DownloadHolder::url() const
{
    return _url;
}

void DownloadHolder::setUrl(const QString &url)
{
    _url = url;
}

QString DownloadHolder::savePath() const
{
    return _savePath;
}

void DownloadHolder::setSavePath(const QString &savePath)
{
    _savePath = savePath;
}

QString DownloadHolder::fileName() const
{
    return _fileName;
}

void DownloadHolder::setFileName(const QString &fileName)
{
    _fileName = fileName;
}

int DownloadHolder::status() const
{
    return _status;
}

void DownloadHolder::setStatus(const int &status)
{
    _status = status;
}

int DownloadHolder::progress() const
{
    return _progress;
}

void DownloadHolder::setProgress(const int &progress)
{
    _progress = progress;
}

QString DownloadHolder::remainingTime() const
{
    return _remainingTime;
}

void DownloadHolder::setRemainingTime(const QString &remainingTime)
{
    _remainingTime = remainingTime;
}

QString DownloadHolder::speed() const
{
    return _speed;
}

void DownloadHolder::setSpeed(const QString &speed)
{
    _speed = speed;
}

QString DownloadHolder::added() const
{
    return _added;
}

void DownloadHolder::setAdded(const QString &added)
{
    _added = added;
}

QString DownloadHolder::downloaded() const
{
    return _downloaded;
}

void DownloadHolder::setDownloaded(const QString &downloaded)
{
    _downloaded = downloaded;
}

QVariant DownloadHolder::attributeValueById(const DownloadConstants::Attributes::Attributes &attr) const
{
    QVariant value;

    switch (attr) {
    case DownloadConstants::Attributes::Uuid:
        value = this->uuid();
        break;
    case DownloadConstants::Attributes::URL:
        value = this->url();
        break;
    case DownloadConstants::Attributes::SavePath:
        value = this->savePath();
        break;
    case DownloadConstants::Attributes::FileName:
        value = this->fileName();
        break;
    case DownloadConstants::Attributes::Status:
        value = this->status();
        break;
    case DownloadConstants::Attributes::Progress:
        value = this->progress();
        break;
    case DownloadConstants::Attributes::RemainingTime:
        value = this->remainingTime();
        break;
    case DownloadConstants::Attributes::Speed:
        value = this->speed();
        break;
    case DownloadConstants::Attributes::Added:
        value = this->added();
        break;
    case DownloadConstants::Attributes::Downloaded:
        value = this->downloaded();
        break;
    default:
        break;
    }

    return value;
}
