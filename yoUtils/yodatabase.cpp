#include "yodatabase.h"

#include <QtSql/QSqlQuery>
#include <QFile>
#include <QTextStream>

class QObject;
class QString;

// TODO: initialize database and return error if somthing goes wrong :|
const QSqlError yoDataBase::initDb()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        msg.dbError(QObject::tr("Unable to load database"), QObject::tr("yoDownet needs the SQLITE driver"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./yodownet.sqlite");

    if (!db.open())
        return db.lastError();

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

bool yoDataBase::addUri(const QString &uriAria2Gid, const QString &uriUri, const QString &uriSavePath, const QString &uriStatus)
{
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO uris(aria2_gid, uri, save_path, status) VALUES(:aria2_gid, :uri, :save_path, :status)");
    addQuery.bindValue(":aria2_gid", uriAria2Gid);
    addQuery.bindValue(":uri", uriUri);
    addQuery.bindValue(":save_path", uriSavePath);
    addQuery.bindValue(":status", uriStatus);
    if(!addQuery.exec()){
        msg.dbError(addQuery.lastError().text(), "Adding new download");
        return false;
    }

    return true;
}
