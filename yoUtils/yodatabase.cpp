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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "yodatabase.h"
#include <QStringList>
#include <QFileInfo>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QPushButton>
#include <QDir>
#include <QDesktopServices>
#include <QDebug>

// TODO: initialize database and return error if somthing goes wrong :|
const QSqlError yoDataBase::initDb()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        yoMessage msg;
        msg.dbError(QObject::tr("Unable to load database"), QObject::tr("yoDownet needs the SQLITE driver"));
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dataDir;
    if(dataDir.mkpath(dbFile))
        db.setDatabaseName(dataDir.toNativeSeparators(dbFile + "/yoDownet.sqlite"));
    if (!db.open())
        return db.lastError();

    // This is gonna be fun :D
    //    QFile dbInitFile(QDir::toNativeSeparators("../yoDownet/sql/yodownet_sqlite_db.sql"));
    //    dbInitFile.open(QIODevice::ReadOnly | QIODevice::Text);
    //    QTextStream in(&dbInitFile);
    QString sqliteCreator = "CREATE TABLE IF NOT EXISTS \"uris\" ("
            "\"id\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,"
            "\"uri\" TEXT,"
            "\"save_path\" TEXT,"
            "\"status\" VARCHAR(25),"
            "\"progress\" INTEGER,"
            "\"remaining_time\" VARCHAR(75) DEFAULT \"n/a\","
            "\"flag\" VARCHAR(15) DEFAULT \"init\","
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

bool yoDataBase::addUri(const QString &argUri, const QString &savePath, const QString &argStatus, const int argProgress)
{
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO uris uri, save_path, status, progress)"
                     " VALUES(:uri, :save_path, :status, :progress)");
    addQuery.bindValue(":uri", argUri);
    addQuery.bindValue(":save_path", savePath);
    addQuery.bindValue(":status", argStatus);
    addQuery.bindValue(":progress", argProgress);
    if(!addQuery.exec()){
        yoMessage msg;
        msg.dbError(addQuery.lastError().text(), QObject::tr("Adding new download"));
        return false;
    }
    setLastInsertedId(addQuery.lastInsertId().toInt());
    return true;
}

bool yoDataBase::updateUri(const QString &argUri, const QString &savePath, const QString &status, const int progress)
{
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE uris SET save_path=:save_path, status=:status, progress=:progress WHERE uri=:uri");
    updateQuery.bindValue(":uri", argUri);
    updateQuery.bindValue(":save_path", savePath);
    updateQuery.bindValue(":status", status);
    updateQuery.bindValue(":progress", progress);
    if(!updateQuery.exec()){
        yoMessage msg;
        msg.dbError(updateQuery.lastError().text(), QObject::tr("Updating existing download"));
        return false;
    }
    return true;
}

bool yoDataBase::deleteUri(const QString &uriUri)
{
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM uris WHERE uri=:uri");
    deleteQuery.bindValue(":uri", uriUri);
    if(!deleteQuery.exec()){
        yoMessage msg;
        msg.dbError(deleteQuery.lastError().text(), QObject::tr("Deleting the download from database"));
        return false;
    }else
        return true;
}

void yoDataBase::setLastInsertedId(const int &id)
{
    _lastInsertedId = id;
}


int yoDataBase::lastInsertedID() const
{
    return _lastInsertedId;
}
