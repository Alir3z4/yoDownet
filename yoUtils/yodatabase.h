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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
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
        uri,
        save_path,
        status,
        progress,
        remaining_time,
        flag,
        created_at,
        updated_at
    };

    const QSqlError initDb();
    bool removeDB(const QSqlDatabase &db);
    bool addUri(const QString &argUri, const QString &savePath, const QString &argStatus, const int argProgress = 0);
    bool updateUri(const QString &argUri, const QString &savePath,const QString &argStatus, const int argProgress);
    bool deleteUri(const QString &uriUri);
    int lastInsertedID() const;

    // [inlines]
    inline int lastInsertedID() const { return _lastInsertedId; }

    void addUrl(const Status *status);
    void updateUrl(const Status *status);
private:
    int _lastInsertedId;
    void setLastInsertedId(const int &id);

    // [inlines]
    inline void setLastInsertedId(const int lastId) { _lastInsertedId = lastId; }
    
};

#endif // YODATABASE_H
