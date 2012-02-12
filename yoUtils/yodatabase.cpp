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
            "\"aria2_gid\" INTEGER NOT NULL ,"
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

bool yoDataBase::addUri(const QString &uriAria2Gid, const QString &uriUri, const QString &uriSavePath, const QString &uriStatus, const int uriProgress, WhatNow what)
{
    if(what == Add){
        if(CheckPlease(uriUri) == Add){
            QSqlQuery addQuery;
            addQuery.prepare("INSERT INTO uris(aria2_gid, uri, save_path, status, progress)"
                             " VALUES(:aria2_gid, :uri, :save_path, :status, :progress)");
            addQuery.bindValue(":aria2_gid", uriAria2Gid);
            addQuery.bindValue(":uri", uriUri);
            addQuery.bindValue(":save_path", uriSavePath);
            addQuery.bindValue(":status", uriStatus);
            addQuery.bindValue(":progress", uriProgress);
            if(!addQuery.exec()){
                yoMessage msg;
                msg.dbError(addQuery.lastError().text(), QObject::tr("Adding new download"));
                return false;
            }
            setLastInsertedId(addQuery.lastInsertId().toInt());
        }
        return true;
    }else if(what == Resume){
        return true;
    }
}

bool yoDataBase::updateUri(const QString &uriAria2Gid, const QString &uriUri, const QString &uriSavePath, const QString &uriStatus, const int uriProgress)
{
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE uris SET save_path=:save_path, status=:status, progress=:progress WHERE aria2_gid=:aria2_gid AND uri=:uri");
    updateQuery.bindValue(":uri", uriUri);
    updateQuery.bindValue(":save_path", uriSavePath);
    updateQuery.bindValue(":status", uriStatus);
    updateQuery.bindValue(":aria2_gid", uriAria2Gid);
    updateQuery.bindValue(":progress", uriProgress);
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

yoDataBase::WhatNow yoDataBase::CheckPlease(const QString &uriUri)
{
    QSqlQuery isExist;
    isExist.prepare("SELECT id, uri FROM uris WHERE uri=:uri LIMIT 1");
    isExist.bindValue(":uri", uriUri);
    if(!isExist.exec()){
        yoMessage msg;
        msg.dbError(isExist.lastError().text(), QObject::tr("Checking is entered download exist"));
    }
    if(isExist.isActive()){
        while (isExist.next()) {
            if(isExist.value(1).toString() == uriUri){
                QMessageBox msgBox;
                QPushButton *resumeButton = msgBox.addButton(QObject::tr("Resume"), QMessageBox::ActionRole);
                //QPushButton *reDownloadButton = msgBox.addButton(QObject::tr("ReDownload"), QMessageBox::ActionRole);
                QPushButton *doNotn = msgBox.addButton(QObject::tr("Do Not'n"), QMessageBox::RejectRole);
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setWindowTitle(QObject::tr("yoDownet : You already have it"));
                msgBox.setText(QObject::tr("The entered download is already exist in the database, It's time to get decision."));
                msgBox.exec();

                if(msgBox.clickedButton() == resumeButton){
                    // TODO: resume the download
                    return Resume;
                }/*else if(msgBox.clickedButton() == reDownloadButton){
                    if(deleteUri(uriUri))
                        return Delete;
                    else
                        return true;
                }*/else if(msgBox.clickedButton() == doNotn){
                    return Notn;
                }
            }
        }
    }
    return Add;
}

void yoDataBase::setLastInsertedId(const int &id)
{
    _lastInsertedId = id;
}


int yoDataBase::lastInsertedID() const
{
    return _lastInsertedId;
}
