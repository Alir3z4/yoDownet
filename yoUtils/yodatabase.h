/****************************************************************************************
** yodatabase.h is part of yoDownet
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

#ifndef YODATABASE_H
#define YODATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include "yoUtils/yomessage.h"

class yoDataBase
{

public:
    enum URIs {
        id,
        aria2_gid,
        uri,
        save_path,
        status,
        progress,
        remaining_time,
        flag,
        created_at,
        updated_at
    };

    enum WhatNow {
        Add,
        Resume,
        ReDownload,
        Delete,
        Notn
    };

    const QSqlError initDb();
    bool removeDB(const QSqlDatabase &db);
    bool addUri(const QString &uriAria2Gid, const QString &uriUri,
                const QString &uriSavePath, const QString &uriStatus, const int uriProgress = 0, enum WhatNow what = Add);
    bool updateUri(const QString &uriAria2Gid, const QString &uriUri,
                   const QString &uriSavePath, const QString &uriStatus, const int uriProgress);
    bool deleteUri(const QString &uriUri);
    int lastInsertedID() const;

private:
    int _lastInsertedId;
    void setLastInsertedId(const int &id);
    WhatNow CheckPlease(const QString &uriUri);
    
};

#endif // YODATABASE_H
