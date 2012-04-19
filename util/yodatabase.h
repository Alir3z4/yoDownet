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

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include "util/yomessage.h"
#include "downloader/yodownet.h"

class yoDataBase : public QObject
{
    Q_OBJECT
public:
    explicit yoDataBase(QObject *parent = 0);

    enum Urls {
        id,
        url,
        save_path,
        status,
        progress,
        remaining_time,
        speed,
        created_at,
        updated_at,
        filename
    };

    const QSqlError initDb();
    bool removeDB(const QSqlDatabase &db);

    // [inlines]
    inline int lastInsertedID() const { return _lastInsertedId; }

signals:
    void databaseFailed(const QString &errorMsg, const QString &action);

private:
    int _lastInsertedId;

    // [inlines]
    inline void setLastInsertedId(const int lastId) { _lastInsertedId = lastId; }
    
};

#endif // YODATABASE_H
