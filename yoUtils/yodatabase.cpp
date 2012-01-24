#include "yodatabase.h"

// TODO: initialize database and return error if somthing goes wrong :|
QSqlError yoDataBase::initDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("yodownet.db");

    if (!db.open())
        return db.lastError();

    // TODO: input the db create script and put it in the QString adn executed with QSqlQuery
    // This is gonna be fun :D
}

bool yoDataBase::removeDB()
{
    db.removeDatabase(db.connectionName());
    return true;
}
