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
    QObject(parent)
{
}

bool Download::newDownload(const QUrl &url, const QUuid &uuid)
{
    if (!uuid)
        uuid = QUuid::createUuid();

    _url = url;
    _uuid = uuid;

    QFileInfo fileInfo(_url.path());
    QString fileName = fileInfo.fileName();
    if(fileName.isEmpty())
        fileName = "yodownet";

    QString savePath = Paths::saveDir();
    QString fileWithPath = savePath.append(fileName);

    _file = new QFile(fileWithPath);
    _status = new Status(this);
    _status->setName(fileName);
    _status->setPath(savePath);

    bool isOpened;
    if(QFile::exists(fileWithPath)){
        isOpened = _file->open(QIODevice::Append);
        _status->setDownloadMode(Status::ResumeDownload);
    }else{
        isOpened = _file->open(QIODevice::WriteOnly);
        _status->setDownloadMode(Status::NewDownload);
    }

    if(!isOpened){
        delete _file;
        _file = 0;
        return false;
    }
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

void Download::setUuid(const QUuid &uuid)
{
    _uuid = uuid;
}

QUuid Download::uuid() const
{
    return _uuid;
}

void Download::setStatus(const Status *status)
{
    _status = status;
}

Status *Download::status() const
{
    return _status;
}
