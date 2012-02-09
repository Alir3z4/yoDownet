/****************************************************************************************
** downloader.cpp is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "downloader.h"

Downloader::Downloader()
{
    // Connecting SIGNALS/SLOTS =)))))
    connect(this, SIGNAL(uriAdded(QVariant)), this, SLOT(askForStatus(QVariant)));
    connect(this, SIGNAL(statusTold(const Status*)), this, SLOT(addUriToDb(const Status*)));
    connect(this, SIGNAL(uriAddedToDb(QString)), this, SLOT(askForRefreshStatus(QString)));
    connect(this, SIGNAL(statusRefreshed(const Status*)), this, SLOT(updateUriToDb(const Status*)));

    startAria();

}

Downloader::~Downloader()
{
    shutdown();
}

void Downloader::resume(const QString &uri)
{
    QVariantMap options;
    addUri(QVariant(uri), options);
}

void Downloader::askForStartAria()
{
    getVersion();
}
void Downloader::askForStatus(const QVariant &gid)
{
    tellStatus(gid, QVariantList());
}

void Downloader::askForRefreshStatus(const QString &gid)
{
    refreshStatus(QVariant(gid), QVariantList());
}

void Downloader::addUriToDb(const Status *status)
{
    yoDataBase db;
    QVariantMap uriMap;
    uriMap["gid"] = status->gid();
    uriMap["uri"] = status->files().first()->uris().first()->uri();
    uriMap["dir"] = status->dir();
    uriMap["status"] = status->status();
    uriMap["progress"] = status->progress();
    uriMap["dir"] = status->dir();
    uriMap["remaining_time"] = status->remainingTime();

    if(db.addUri(uriMap["gid"].toString(), uriMap["uri"].toString(), uriMap["dir"].toString(), uriMap["status"].toString(), uriMap["progress"].toInt())){
        uriMap["id"] = db.lastInsertedID();
        emit uriAddedToDb(uriMap["gid"].toString());
        emit uriAddedToDb(uriMap);
        // TODO: Some notify can be good here abour success ;)
    }
    // TODO: Some notify can be good here about failure ;?
}

void Downloader::updateUriToDb(const Status *status)
{
    yoDataBase db;
    if(db.updateUri(status->gid(), status->files().first()->uris().first()->uri(), status->dir(), status->status(), status->progress())){
        emit uriUpdatedOnDb(status);
    }
}
