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

yoDataBase::yoDataBase(QObject *parent) :
    QObject(parent)
{
    // Initialize the Database;
    QSqlError sqlError = initDb();
    if (sqlError.type() != QSqlError::NoError){
        yoMessage msg;
        emit databaseFailed(sqlError.text(), tr("Unable to initialize Database"));
        connect(this, SIGNAL(databaseFailed(QString,QString)), &msg, SLOT(dbError(QString,QString)));
    }
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
