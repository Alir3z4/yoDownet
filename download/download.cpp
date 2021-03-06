/****************************************************************************************
** download.cpp is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "download.h"
#include <QFileInfo>
#include "util/paths.h"

Download::Download(QObject *parent) :
    QObject(parent), _logger(new LogMe(this))
{
}


bool Download::newDownload(const QUrl &url, const QUuid &uuid, const QString &fileName)
{
    _logger->debug(fileName);
    _logger->info(QString("Initializing new download: %1").arg(url.toString()));

    setUuid(uuid);
    setUrl(url);

    QString fileNewName = fileName;

    if (fileNewName.isEmpty() || fileNewName.isNull()) {
        _logger->info("fileName is not provided, getting file name from URL");
        QFileInfo fileInfo(url.path());
        fileNewName = fileInfo.fileName();
    }

    QString savePath = Paths::saveDir();
    QString fileWithPath = QString(savePath).append(fileNewName);

    _logger->info(QString("FileName: [%1]| FileWithPath: [%2]").arg(fileNewName, fileWithPath));


    _file = new QFile(this);

    this->setFile(new QFile(fileWithPath));
    _status = new Status(this);
    this->setName(fileNewName);
    this->setPath(savePath);

    bool isOpened;
    if (QFile::exists(fileWithPath)) {
        _logger->info("Download file exist on file-system, Going to resume");

        isOpened = _file->open(QIODevice::Append);
        _status->setDownloadMode(Status::ResumeDownload);
    } else {
        _logger->info("New download recognized");

        isOpened = _file->open(QIODevice::WriteOnly);
        _status->setDownloadMode(Status::NewDownload);
    }

    if (!isOpened) {
        _logger->error(QString("Couldn't open file for '%1', adding new download aborted").arg(fileNewName));
        delete _file;
        _file = 0;
        return false;
    }

    this->setCreated(QDateTime::currentDateTime());

    return true;
}

void Download::setFile(QFile *file)
{
    _file = file;
}

QFile *Download::file()
{
    return _file;
}

void Download::setUrl(const QUrl &url)
{
    _url = url;
}

QUrl Download::url() const
{
    return _url;
}

void Download::setName(const QString &name)
{
    _name = name;
}

QString Download::name() const
{
    return _name;
}

void Download::setPath(const QString &path)
{
    _path = path;
}

QString Download::path() const
{
    return _path;
}

QString Download::fileAbsolutePath() const
{
    return QString(path() + name());
}

void Download::setUuid(const QUuid &uuid)
{
    _logger->info("Initializing UUID");
    if (uuid.isNull()) {
        _logger->info("Given UUID is null, Generating new one");
        _uuid = QUuid::createUuid();
        return;
    }

    _uuid = uuid;
}

QUuid Download::uuid() const
{
    return _uuid;
}

void Download::setStatus(Status *status)
{
    _status = status;
}

Status *Download::status() const
{
    return _status;
}

void Download::setCreated(const QDateTime &created)
{
    _created = created;
}

QDateTime Download::created() const
{
    return _created;
}
QUrl Download::urlRedirectedTo() const
{
    return _urlRedirectedTo;
}

void Download::setUrlRedirectedTo(const QUrl &urlRedirectedTo)
{
    _urlRedirectedTo = urlRedirectedTo;
}

