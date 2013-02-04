/****************************************************************************************
** yodownet.cpp is part of yoDownet
**
** Copyright 2012, 2013 Alireza Savand <alireza.savand@gmail.com>
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
#include "util/paths.h"

yoDownet::yoDownet(QObject *parent) :
    QObject(parent), _downloads(new QHash<QNetworkReply*, QFile*>),
    _statusHash( new QHash<QUrl, Status*>)
{
    connect(this, SIGNAL(fileReadyToRemove(QFile*)), this, SLOT(removeFile(QFile*)));
}
void yoDownet::addDownload(const QString &url)
{
    if (_download->newDownload(QUrl(url)))
        startRequest(_download->url());
}

void yoDownet::addDownloads(const QStringList &urls)
{
    if(urls.isEmpty()) return;
    for(int i = 0; i < urls.size(); ++i)
        addDownload(urls[i]);
}

void yoDownet::pauseDownload(const QString &url)
{
    QHash<QNetworkReply*, QFile*>::iterator i = _downloads->begin();
    while(i != _downloads->end()){
        if(i.key()->url().toString() == url){
            i.value()->write(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);
            emit downloadPaused(status);
            i.key()->close();
            break;
        }
    }
}

void yoDownet::pauseDownloads(const QStringList &urls)
{
    if(urls.isEmpty()) return;
    for(int i = 0; i < urls.size(); ++i)
        pauseDownload(urls[i]);
}

void yoDownet::removeDownload(const QString &filePath)
{
    if(_downloads->isEmpty()){
        emit fileReadyToRemove(new QFile(filePath));
        return;
    }
    // FIXME: file pointer doesn't exist here, Value is Download pointer
        if(file->fileName() == filePath){
            QNetworkReply *reply = _downloads->key(file);
            emit pauseDownload(reply->url().toString());
            emit fileReadyToRemove(file);
            break;
        }
    }
}

void yoDownet::removeDownloads(const QStringList &files)
{
    if(files.isEmpty()) return;
    for(int i = 0; i < files.size(); ++i)
        removeDownload(files[i]);
}

void yoDownet::replyMetaDataChanged(QObject *currentReply)
{
    QHash<QNetworkReply*, QFile*>::iterator i = _downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    Status *status = _statusHash->find(i.key()->url()).value();
    status->setBytesTotal(i.key()->header(QNetworkRequest::ContentLengthHeader).toULongLong());
}

void yoDownet::startRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(_file->size()).toByteArray()));

    _status->setFileAlreadyBytes(_file->size());

    _reply = _manager.get(request);

    _status->setUrl(url.toString());
    _status->setDownloadStatus(Status::Starting);

    QHash<QNetworkReply*, QFile*>::iterator i = _downloads->insert( _reply, _file);
    QHash<QUrl, Status*>::iterator statusIt = _statusHash->insert(i.key()->url(), _status);

    if(statusIt.value()->downloadMode() == Status::NewDownload){
        emit downloadInitialed(statusIt.value());
    }
    else if(statusIt.value()->downloadMode() == Status::ResumeDownload){
        emit downlaodResumed(statusIt.value());
    }

    _readyReadSignalMapper = new QSignalMapper(this);
    _metaChangedSignalMapper = new QSignalMapper(this);
    _finishedSignalMapper = new QSignalMapper(this);

    _readyReadSignalMapper->setMapping(i.key(), i.key());
    _metaChangedSignalMapper->setMapping(i.key(), i.key());
    _finishedSignalMapper->setMapping(i.key(), i.key());

    connect(i.key(), SIGNAL(readyRead()), _readyReadSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(metaDataChanged()), _metaChangedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(finished()), _finishedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(downloadProgress(qint64,qint64)), statusIt.value(),  SLOT(updateFileStatus(qint64,qint64)));

    connect(_readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpReadyRead(QObject*)));
    connect(_metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(replyMetaDataChanged(QObject*)));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpFinished(QObject*)));
}

void yoDownet::httpReadyRead(QObject *currentReply)
{
    QHash<QNetworkReply*, QFile*>::iterator i = _downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    Status *status = _statusHash->find(i.key()->url()).value();
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
    QHash<QNetworkReply*, QFile*>::iterator i = _downloads->find(qobject_cast<QNetworkReply*>(currentReply));
    Status *status = _statusHash->find(i.key()->url()).value();

    i.value()->flush();
    i.value()->close();
    i.value() = 0;
    i.key()->deleteLater();
    _downloads->remove(i.key());

    if(status->downloadStatus() != Status::Paused)
        status->setDownloadStatus(Status::Finished);

    // Oh let's emit this mother fucker!
    emit downloadUpdated(status);
}

void yoDownet::removeFile(QFile *file)
{
    const QString fileName = file->fileName();
    if(!file->remove())
        return;
    file = 0;
    emit downloadRemoved(fileName);
}
