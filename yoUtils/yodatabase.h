#ifndef YODATABASE_H
#define YODATABASE_H

#include <QtSql/QSqlDatabase>

class QSqlDatabase;

class yoDataBase
{
public:
    QSqlError initDb();
    bool removeDB();

private:
    QSqlDatabase db;
};

#endif // YODATABASE_H
