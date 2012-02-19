/****************************************************************************************
** yodownet.h is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef YODOWNET_H
#define YODOWNET_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include "yoUtils/status.h"

class yoDownet : public QObject
{
    Q_OBJECT
public:
    explicit yoDownet(QObject *parent = 0);
    
signals:
    void downloadInitialed(const Status *status);
    void downlaodResumed(const Status *status);
    void downloadUpdated(const Status *status);
    void downloadFinished();

public slots:
    void theDownload(const QString &urlLink);

private slots:
    void replyMetaDataChanged();
    void startRequest(const QUrl &url);
    void httpReadyRead();
    void httpFinished();

private:
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QFile *file;
    Status *status;
};

#endif // YODOWNET_H
