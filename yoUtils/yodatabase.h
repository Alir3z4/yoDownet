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
        aria2_gid,
        uri,
        save_path,
        status,
        created_at,
        updated_at
    };

    const QSqlError initDb();
    bool removeDB(const QSqlDatabase &db);

    // Actions
    bool addUri(const QString &uriAria2Gid, const QString &uriUri, const QString &uriSavePath, const QString &uriStatus);

private:
    yoMessage msg;
};

#endif // YODATABASE_H
