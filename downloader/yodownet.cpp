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
    QObject(parent), _downloadHash(new QHash<QNetworkReply*, Download*>),
    _statusHash( new QHash<QUrl, Status*>), _logger(new LogMe(this))
{
    connect(this, SIGNAL(fileReadyToRemove(QFile*)), this, SLOT(removeFile(QFile*)));
}

void yoDownet::addDownload(const QString &url)
{
    Download *newDownload = new Download(this);

    if (newDownload->newDownload(QUrl(url))) {
        startRequest(newDownload);
    }
}

void yoDownet::addDownloads(const QStringList &urls)
{
    if(urls.isEmpty()) {
        return;
    }

    for(int i = 0; i < urls.size(); ++i) {
        addDownload(urls[i]);
    }
}

void yoDownet::pauseDownload(const QString &url)
{
    _logger->info(QString("Pausing download '%1'").arg(url));

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->begin();
    while(i != _downloadHash->end()){
        if(i.key()->url().toString() == url){
            _logger->info(QString("Found download '%1' in hash.").arg(url));

            i.value()->file()->write(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);

            _logger->info(QString("Emit 'downloadPaused' signal for '%1'").arg(url));
            emit downloadPaused(i.value());

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
    _logger->info(QString("Start Removing '%1' via download engine").arg(filePath));

    if(_downloadHash->isEmpty()){
        _logger->info(QString("Download hash is empty, emiting `fileReadyToRemove` singal to remove file '%1'").arg(filePath));

        emit fileReadyToRemove(new QFile(filePath));
        return;
    }
    foreach(Download *download, _downloadHash->values()){
        if(download->file()->fileName() == filePath){
            _logger->info(QString("Found download '%1' in hash.").arg(filePath));

            QNetworkReply *reply = _downloadHash->key(download);
            emit pauseDownload(reply->url().toString());
            emit fileReadyToRemove(download->file());
            break;
        }
    }
}

void yoDownet::removeDownloads(const QStringList &files)
{
    if(files.isEmpty()) {
        return;
    }
    for(int i = 0; i < files.size(); ++i) {
        removeDownload(files[i]);
    }
}

void yoDownet::replyMetaDataChanged(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    Status *status = _statusHash->find(i.key()->url()).value();
    status->setBytesTotal(i.key()->header(QNetworkRequest::ContentLengthHeader).toULongLong());
}

void yoDownet::startRequest(Download *newDownload)
{
    _logger->info(QString("Starting request for '%1'").arg(newDownload->url().toString()));

    QNetworkRequest request(newDownload->url().toString());
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(newDownload->file()->size()).toByteArray()));

    newDownload->status()->setFileAlreadyBytes(newDownload->file()->size());

    _reply = _manager.get(request);

    newDownload->status()->setDownloadStatus(Status::Starting);

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->insert(_reply, newDownload);
    QHash<QUrl, Status*>::iterator statusIt = _statusHash->insert(i.key()->url(), newDownload->status());

    if (statusIt.value()->downloadMode() == Status::NewDownload) {
        emit downloadInitialed(i.value());
    } else if (statusIt.value()->downloadMode() == Status::ResumeDownload) {
        emit downlaodResumed(i.value());
    }

    // Initialing `SignalMapper`
    _logger->info(QString("Initialing `SignalMapper`s for `%1`").arg(newDownload->url().toString()));

    _readyReadSignalMapper = new QSignalMapper(this);
    _metaChangedSignalMapper = new QSignalMapper(this);
    _finishedSignalMapper = new QSignalMapper(this);

    // Setup mapping on `SignalMapper`
    _logger->info(QString("Setup mapping on signal mappers for `%1`").arg(newDownload->url().toString()));

    _readyReadSignalMapper->setMapping(i.key(), i.key());
    _metaChangedSignalMapper->setMapping(i.key(), i.key());
    _finishedSignalMapper->setMapping(i.key(), i.key());

    // Connecting signals to the `receivers` via `SignalMapper`
    _logger->info(QString("Connecting signals to receivers via signals mappers for `%1`").arg(newDownload->url().toString()));

    connect(i.key(), SIGNAL(readyRead()), _readyReadSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(metaDataChanged()), _metaChangedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(finished()), _finishedSignalMapper, SLOT(map()));
    connect(i.key(), SIGNAL(downloadProgress(qint64,qint64)), statusIt.value(), SLOT(updateFileStatus(qint64, qint64)));

    connect(_readyReadSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpReadyRead(QObject*)));
    connect(_metaChangedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(replyMetaDataChanged(QObject*)));
    connect(_finishedSignalMapper, SIGNAL(mapped(QObject*)), this, SLOT(httpFinished(QObject*)));
}

void yoDownet::httpReadyRead(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    if (i.value()->file()) {
        Status *status = _statusHash->find(i.key()->url()).value();
        if (i.value()->file()->size() == status->bytesTotal()) {
            i.key()->close();
        } else if (i.value()->file()->size() < status->bytesTotal()) {
            i.value()->file()->write(i.key()->readAll());
            status->setDownloadStatus(Status::Downloading);
            emit downloadUpdated(i.value());
        }
    }
}

void yoDownet::httpFinished(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    Status *status = _statusHash->find(i.key()->url()).value();

    _logger->info(QString("HTTP request has finished for '%1'").arg(i.value()->url().toString()));

    i.value()->file()->flush();
    i.value()->file()->close();
    i.value()->setFile(0);
    i.key()->deleteLater();

    _downloadHash->remove(i.key());

    if(status->downloadStatus() != Status::Paused) {
        _logger->info("HTTP request has finished, I'm done with downloading.");
        status->setDownloadStatus(Status::Finished);
    }

    // Oh let's emit this mother fucker!
    emit downloadUpdated(i.value());
}

void yoDownet::removeFile(QFile *file)
{
    const QString fileName = file->fileName();
    if(!file->remove()) {
        return;
    }
    file = 0;
    emit downloadRemoved(fileName);
}
