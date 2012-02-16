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
    QObject(parent)
{
    connect(this, SIGNAL(downloadInitialed(const Status*)), status, SLOT(startTime()));
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
}
