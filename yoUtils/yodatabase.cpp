/****************************************************************************************
** yodatabase.cpp is part of yoDownet
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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "yodatabase.h"
#include <QSqlQuery>
#include <QPushButton>
#include <QDir>
#include <QDesktopServices>
#include <QDebug>

yoDataBase::yoDataBase(QObject *parent, yoDownet *dler) :
    QObject(parent), msg(new yoMessage), downloader(dler)
{
    connect(this, SIGNAL(databaseFailed(QString,QString)), msg, SLOT(dbError(QString,QString)));
    connect(downloader, SIGNAL(downloadInitialed(const Status*)), this, SLOT(addUrl(const Status*)));
    connect(downloader, SIGNAL(downlaodResumed(const Status*)), this, SLOT(updateUrl(const Status*)));
    connect(downloader, SIGNAL(downloadFinished(const Status*)), this, SLOT(updateUrl(const Status*)));
}

const QSqlError yoDataBase::initDb()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        emit databaseFailed(tr("Unable to load database"), tr("yoDownet needs the SQLITE driver"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dataDir;
    if(dataDir.mkpath(dbFile))
        db.setDatabaseName(dataDir.toNativeSeparators(dbFile + "/yoDownet.sqlite"));
    if (!db.open())
        return db.lastError();

    QString sqliteCreator = "CREATE TABLE IF NOT EXISTS \"urls\" ("
            "\"id\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,"
            "\"url\" TEXT,"
            "\"save_path\" TEXT,"
            "\"status\" INTEGER,"
            "\"progress\" INTEGER,"
            "\"remaining_time\" VARCHAR(75) DEFAULT \"n/a\","
            "\"speed\" VARCHAR(75),"
            "\"created_at\" TIMESTAMP NOT NULL  DEFAULT CURRENT_TIMESTAMP,"
            "\"updated_at\" TIMESTAMP);";

    QSqlQuery initDbQuery;
    if(!initDbQuery.exec(sqliteCreator))
        return initDbQuery.lastError();

    return QSqlError();
}

bool yoDataBase::removeDB(const QSqlDatabase &removeDb)
{
    removeDb.removeDatabase(removeDb.connectionName());
    return true;
}

bool yoDataBase::isExist(const QString &urlUrl)
{
    QSqlQuery isExist;
    isExist.prepare("SELECT id, url FROM urls WHERE url=:url LIMIT 1");
    isExist.bindValue(":url", urlUrl);
    if(!isExist.exec()){
        emit databaseFailed(isExist.lastError().text(), tr("Checking is entered download exist"));
    }
    if(isExist.isActive()){
        while(isExist.next()){
            if(isExist.value(1).toString() == urlUrl){
                return true;
            }
        }
    }
    return false;
}

void yoDataBase::addUrl(const Status *status)
{
    if(!isExist(status->url())){
        QSqlQuery addQuery;
        addQuery.prepare("INSERT INTO urls (url, save_path, status, progress)"
                         " VALUES(:url, :save_path, :status, :progress)");
        addQuery.bindValue(":url", status->url());
        addQuery.bindValue(":save_path", status->path());
        addQuery.bindValue(":status", status->downloadMode());
        addQuery.bindValue(":progress", 0);
        if(!addQuery.exec()){
            emit databaseFailed(addQuery.lastError().text(), tr("Adding new download"));
            return;
        }
        setLastInsertedId(addQuery.lastInsertId().toInt());
    }else{
        updateUrl(status);
    }
}

void yoDataBase::updateUrl(const Status *status)
{
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE urls SET save_path=:save_path, status=:status, progress=:progress WHERE url=:url");
    updateQuery.bindValue(":url", status->url());
    updateQuery.bindValue(":save_path", status->path());
    updateQuery.bindValue(":status", status->downloadMode());
    updateQuery.bindValue(":progress", status->progress());
    if(!updateQuery.exec()){
        emit databaseFailed(updateQuery.lastError().text(), tr("Updating existing download"));
        return;
    }
}

void yoDataBase::deleteUrl(const QString &urlUrl)
{
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM urls WHERE url=:url");
    deleteQuery.bindValue(":url", urlUrl);
    if(!deleteQuery.exec()){
        emit databaseFailed(deleteQuery.lastError().text(), tr("Deleting the download from database"));
        return;
    }
}
