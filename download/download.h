/****************************************************************************************
** download.h is part of yoDownet
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

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QUuid>
#include <QUrl>
#include "core/logme.h"
#include "download/status.h"

class Download : public QObject
{
    Q_OBJECT

public:
    explicit Download(QObject *parent = 0);

    bool newDownload(const QUrl &url, const QUuid &uuid=QUuid(), const QString &fileName=QString());

    void setFile(QFile *file);
    QFile *file();

    void setUrl(const QUrl &url);
    QUrl url() const;

    void setName(const QString &name);
    QString name() const;

    void setPath(const QString &path);
    QString path() const;

    QString fileAbsolutePath() const;

    void setUuid(const QUuid &uuid=QUuid::createUuid());
    QUuid uuid() const;

    void setStatus(Status *status);
    Status *status() const;

    void setCreated(const QDateTime &created);
    QDateTime created() const;

    QUrl urlRedirectedTo() const;
    void setUrlRedirectedTo(const QUrl &urlRedirectedTo);

private:
    QFile *_file;
    QUrl _url;
    QString _name;
    QString _path;
    QUuid _uuid;
    Status *_status;
    QDateTime _created;

    QUrl _urlRedirectedTo;

    LogMe *_logger;

};

#endif // DOWNLOAD_H
