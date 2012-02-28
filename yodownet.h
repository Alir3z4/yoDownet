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
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>
#include <QUrl>
#include <QHash>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "yoUtils/status.h"

class yoDownet : public QObject
{
    Q_OBJECT
public:
    explicit yoDownet(QObject *parent = 0);
    
signals:
    void downloadInitialed(const Status *_status);
    void downlaodResumed(const Status *_status);
    void downloadUpdated(const Status *_status);
    void downloadRemoved(const QString &url);
    void downloadFinished();

public slots:
    void addDownload(const QString &url);
    void addDownloads(const QStringList &urls);
    void removeDownload(const QString &url);
    void removeDownloads(const QStringList &urls);

private slots:
    void replyMetaDataChanged(QObject *currentReply);
    void startRequest(const QUrl &url);
    void httpReadyRead(QObject *currentReply);
    void httpFinished(QObject *currentReply);

private:
    QNetworkAccessManager manager;
    QNetworkReply *_reply;
    QFile *_file;
    Status *_status;
    QSignalMapper *readyReadSignalMapper;
    QSignalMapper *metaChangedSignalMapper;
    QSignalMapper *finishedSignalMapper;
    QHash<QNetworkReply*, QFile*> *downloads;
    QHash<QUrl, Status*> *statusHash;
};

#endif // YODOWNET_H
