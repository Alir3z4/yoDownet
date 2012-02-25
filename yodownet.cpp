/****************************************************************************************
** yodownet.cpp is part of yoDownet
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

#include "yodownet.h"
#include <QSettings>

yoDownet::yoDownet(QObject *parent) :
    QObject(parent), downloads(new QHash<QNetworkReply*, QFile*>),
    statusHash( new QHash<QUrl, Status*>)
{}
void yoDownet::theDownload(const QString &urlLink)
{
    QUrl url(urlLink);
    QFileInfo fInfo(url.path());
    QString fileName = fInfo.fileName();
    if(fileName.isEmpty())
        fileName  = "yodownet";

    // FIXME: move these setting mess to separate class
    QSettings settings;
    settings.beginGroup("PreferencesDialog");
    settings.beginGroup("PrefDownloadersWidget");
    QString savePath = settings.value("saveDir", QDir::homePath()).toString() + QDir::toNativeSeparators("/");
    settings.endGroup();
    settings.endGroup();
    /*********************/

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
        return;
    }
    startRequest(url);
}

void yoDownet::replyMetaDataChanged(QObject *currentReply)
{
    auto i = downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    auto status = statusHash->find(i.key()->url()).value();
    status->setBytesTotal(i.key()->header(QNetworkRequest::ContentLengthHeader).toULongLong());
}

void yoDownet::startRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(_file->size()).toByteArray()));

    _reply = manager.get(request);

    _status->setUrl(url.toString());
    _status->setDownloadStatus(Status::Starting);

    auto i = downloads->insert( _reply, _file);
    auto statusIt = statusHash->insert(i.key()->url(), _status);

    connect(this, SIGNAL(downloadInitialed(const Status*)), statusIt.value(), SLOT(startTime()));
    connect(this, SIGNAL(downlaodResumed(const Status*)), statusIt.value(), SLOT(startTime()));

    if(statusIt.value()->downloadMode() == Status::NewDownload){
        emit downloadInitialed(statusIt.value());
    }
    else if(statusIt.value()->downloadMode() == Status::ResumeDownload){
        emit downlaodResumed(statusIt.value());
    }

    readyReadSignalMapper = new QSignalMapper(this);
    metaChangedSignalMapper = new QSignalMapper(this);
    finishedSignalMapper = new QSignalMapper(this);

    readyReadSignalMapper->setMapping(i.key(), i.key());
    metaChangedSignalMapper->setMapping(i.key(), i.key());
    finishedSignalMapper->setMapping(i.key(), i.key());

    connect(i.key(), SIGNAL(readyRead()), readyReadSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(metaDataChanged()), metaChangedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(finished()), finishedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(downloadProgress(qint64,qint64)), statusIt.value(),  SLOT(updateFileStatus(qint64,qint64)));

    connect(readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpReadyRead(QObject*)));
    connect(metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(replyMetaDataChanged(QObject*)));
    connect(finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpFinished(QObject*)));
}

void yoDownet::httpReadyRead(QObject *currentReply)
{
    auto i = downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    auto status = statusHash->find(i.key()->url()).value();
    if(i.value()){
        if(i.value()->size() == status->bytesTotal()){
            i.key()->close();
        }else if(i.value()->size() < status->bytesTotal()){
            i.value()->write(i.key()->readAll());
            status->setDownloadStatus(Status::Downloading);
            emit downloadUpdated(status);
        }
    }
}

void yoDownet::httpFinished(QObject *currentReply)
{
    auto i = downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    auto status = statusHash->find(i.key()->url()).value();

    i.value()->flush();
    i.value()->close();
    i.value() = 0;
    i.key()->deleteLater();
    downloads->remove(i.key());

    status->setDownloadStatus(Status::Finished);

    emit downloadUpdated(status);
    emit downloadFinished();
}
