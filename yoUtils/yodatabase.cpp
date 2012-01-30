#include "yodatabase.h"

#include <QtSql/QSqlQuery>
#include <QFile>
#include <QTextStream>

class QObject;
class QString;

// TODO: initialize database and return error if somthing goes wrong :|
QSqlError yoDataBase::initDb()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        msg.dbError(QObject::tr("Unable to load database"), QObject::tr("yoDownet needs the SQLITE driver"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./yodownet.sqlite");

    if (!db.open())
        return db.lastError();

    // TODO: input the db create script and put it in the QString adn executed with QSqlQuery
    // This is gonna be fun :D
    QFile dbInitFile("../yoDownet/sql/yodownet_sqlite_db_000.sql");
    dbInitFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&dbInitFile);
    QString dbInitSqlScript = in.readAll();

    QSqlQuery initDbQuery;
    if(!initDbQuery.exec(dbInitSqlScript))
        return initDbQuery.lastError();

    return QSqlError();
}

bool yoDataBase::removeDB(const QSqlDatabase &removeDb)
{
    removeDb.removeDatabase(removeDb.connectionName());
    return true;
}
