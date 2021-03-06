/****************************************************************************************
** yodownet.cpp is part of yoDownet
**
** Copyright 2012, 2013, 2014 Alireza Savand <alireza.savand@gmail.com>
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

void yoDownet::addDownload(const QString &url, const QUuid &uuid, const QString &fileName)
{
    Download *newDownload = new Download(this);

    if (newDownload->newDownload(QUrl(url), uuid, fileName)) {
        this->startRequest(newDownload);
    }
}

// TODO: emit signal when download hash is empty OR no download has been found
void yoDownet::pauseDownload(const QUuid &uuid)
{
    _logger->info(QString("Pausing download [%1]").arg(uuid.toString()));

    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->begin();
    while(i != _downloadHash->end()){
        if(i.value()->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));

            i.value()->file()->write(i.key()->readAll());
            Status *status = _statusHash->find(i.key()->url()).value();
            status->setDownloadStatus(Status::Paused);

            _logger->info(QString("Emit 'downloadPaused' signal for [%1]").arg(uuid.toString()));
            emit downloadPaused(i.value());

            i.key()->abort();
            i.key()->close();
            break;
        }
    }
}

void yoDownet::removeDownload(const QUuid &uuid)
{
    _logger->info(QString("Start Removing [%1] via downloader engine").arg(uuid.toString()));

    if(_downloadHash->isEmpty()){
        _logger->info(QString("Download hash is empty, emiting `fileReadyToRemove` singal to remove download with UUID: [%1]").arg(uuid.toString()));

        emit this->downloadDoesNotExistToRemove(uuid);
        return;
    }
    foreach(Download *download, _downloadHash->values()){
        if(download->uuid() == uuid){
            _logger->info(QString("Found download [%1] in hash.").arg(uuid.toString()));

            QNetworkReply *reply = _downloadHash->key(download);
            emit pauseDownload(reply->url().toString());
            emit fileReadyToRemove(download->file());
            break;
        }
    }
}

void yoDownet::replyMetaDataChanged(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    QNetworkReply *reply = i.key();
    Status *status = _statusHash->find(reply->url()).value();

    status->setBytesTotal(reply->header(QNetworkRequest::ContentLengthHeader).toULongLong());
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
    QNetworkReply *reply = i.key();
    Download *download = i.value();

    if (download->file()) {
        Status *status = download->status();
        download->file()->write(reply->readAll());
        status->setDownloadStatus(Status::Downloading);

        emit downloadUpdated(download);

    }
}

void yoDownet::httpFinished(QObject *currentReply)
{
    QHash<QNetworkReply*, Download*>::iterator i = _downloadHash->find(qobject_cast<QNetworkReply*>(currentReply));
    Download *download = i.value();
    QNetworkReply *reply = i.key();
    Status *status = _statusHash->find(reply->url()).value();

    _logger->info(QString("HTTP request has finished for '%1'").arg(download->url().toString()));


    QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    // We'll deduct if the redirection is valid in the redirectUrl function
    download->setUrlRedirectedTo(possibleRedirectUrl.toUrl());

    if (!download->urlRedirectedTo().isEmpty()) {
        _logger->info(QString("[%1] redirected to %2").arg(
                          download->uuid().toString(),
                          download->urlRedirectedTo().toString())
                      );
        download->setUrl(download->urlRedirectedTo());
        QString fileName = download->name();
        this->removeFile(download->file());
        this->addDownload(download->url().toString(), download->uuid(), fileName);
    } else {
        /*
         * We weren't redirected anymore
         * so we arrived to the final destination...
         */
        download->urlRedirectedTo().clear();

    }


    download->file()->flush();
    download->file()->close();
    download->setFile(0);

    reply->deleteLater();

    if(status->downloadStatus() != Status::Paused) {
        _logger->info("HTTP request has finished, I'm done with downloading.");
        status->setDownloadStatus(Status::Finished);
    }

    // Oh let's emit this mother fucker!
    emit downloadUpdated(download);

    _downloadHash->remove(reply);
}

void yoDownet::removeFile(QFile *file)
{
    _logger->info(QString("Removing file: [%1]").arg(file->fileName()));

    const QString fileName = file->fileName();
    if(!file->remove()) {
        _logger->error(QString("Couldn't remove [%1]. Error: %2").arg(file->fileName(), file->errorString()));
        return;
    }
    file = 0;
    emit downloadRemoved(fileName);
}

QUrl yoDownet::redirectUrl(const QUrl &possibleRedirectUrl, const QUrl &oldRedirectUrl) const
{
    QUrl redirectUrl;
    /*
     * Check if the URL is empty and
     * that we aren't being fooled into infinite redirect loop.
     * We could also keep track of how many redirects we have been to
     * and set a limit to it, but we'll leave that for now.
     */
    if (!possibleRedirectUrl.isEmpty() && possibleRedirectUrl != oldRedirectUrl) {
        redirectUrl = possibleRedirectUrl;
    }

    return redirectUrl;
}
