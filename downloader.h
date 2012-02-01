#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "yoDownloaders/aria2c.h"
#include "yoUtils/yodatabase.h"

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader();

    // Aria2 connection
    bool ariaAlreadyRunning();
    void startAria(const QStringList &flags);

    // Operations :|
    bool addUri(const QVector<QString> &uris);
    bool addUri(const QVector<QString> &uris, QMap<QString, QString> &options);

    const QString remove(const QString gid);
    const QString forceRemove(const QString gid);

    const QString pause(const QString gid);
    const QString forcePause(const QString gid);
    const QString unPause(const QString gid);

    const Status* tellStatus(const QString gid);

    const QString shutdown();
    const QString forceShutdown();

private:
    Aria2c aria2;
    bool _iStartedAria;
    yoDataBase db;
    yoMessage *msg;

    void setIStartedAria(bool didI);
    bool isIStartedAria2();


};

#endif // DOWNLOADER_H
