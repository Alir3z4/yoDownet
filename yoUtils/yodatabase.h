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
                const QString &uriSavePath, const QString &uriStatus, const int uriProgress = 0);
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
