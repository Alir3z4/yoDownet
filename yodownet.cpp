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

yoDownet::yoDownet(QObject *parent) :
    QObject(parent), status(new Status(this))
{
    connect(this, SIGNAL(downloadInitialed(const Status*)), status, SLOT(startTime()));
    connect(this, SIGNAL(downlaodResumed(const Status*)), status, SLOT(startTime()));
}

void yoDownet::theDownload(const QString &urlLink)
{
    QUrl url(urlLink);
    QFileInfo fInfo(url.path());
    QString fileName = fInfo.fileName();
    if(fileName.isEmpty())
        fileName  = "yodownet";

    file = new QFile(fileName);
    status->setName(fileName);
    status->setPath(QDir::currentPath());

    bool isOpened;
    if(QFile::exists(fileName)){
        isOpened = file->open(QIODevice::Append);
        status->setDownloadMode(Status::ResumeDownload);
    }else{
        isOpened = file->open(QIODevice::WriteOnly);
        status->setDownloadMode(Status::NewDownload);
    }
    if(!isOpened){
        delete file;
        file = 0;
        return;
    }

    startRequest(url);
}

void yoDownet::replyMetaDataChanged()
{
    status->setBytesTotal(reply->header(QNetworkRequest::ContentLengthHeader).toULongLong());
}

void yoDownet::startRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader("Range", QByteArray("bytes=SIZE-").replace("SIZE", QVariant(file->size()).toByteArray()));

    reply = manager.get(request);

    // set the url
    status->setUrl(url.toString());
    status->setDownloadStatus(Status::Starting);
    if(status->downloadMode() == Status::NewDownload){
        emit downloadInitialed(status);
    }
    else if(status->downloadMode() == Status::ResumeDownload){
        emit downlaodResumed(status);
    }
    // conncet signals
    connect(reply, SIGNAL(metaDataChanged()), this, SLOT(replyMetaDataChanged()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), status, SLOT(updateFileStatus(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void yoDownet::httpReadyRead()
{
    if(file){
        if(file->size() == status->bytesTotal()){
            status->setDownloadStatus(Status::Downloading);
            emit downloadUpdated(status);
            reply->close();
        }else if(file->size() < status->bytesTotal()){
            file->write(reply->readAll());
            status->setDownloadStatus(Status::Downloading);
            emit downloadUpdated(status);
        }
    }
}

void yoDownet::httpFinished()
{
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;

    status->setDownloadStatus(Status::Finished);

    emit downloadUpdated(status);
    emit downloadFinished();
}
