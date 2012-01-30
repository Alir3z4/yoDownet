#ifndef YODATABASE_H
#define YODATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include "yoUtils/yomessage.h"

class QSqlQuery;

class yoDataBase
{
public:
    enum URIs {
        id,
        uri,
        aria2_gid,
        save_path,
        created_at,
        updated_at
    };

    QSqlError initDb();
    bool removeDB(const QSqlDatabase &db);

private:
    yoMessage msg;
};

#endif // YODATABASE_H
