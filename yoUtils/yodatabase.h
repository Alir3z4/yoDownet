#ifndef YODATABASE_H
#define YODATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include "yoUtils/yomessage.h"

class yoDataBase
{
public:
    QSqlError initDb();
    bool removeDB(QSqlDatabase &db);

private:
    yoMessage msg;
};

#endif // YODATABASE_H
