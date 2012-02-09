#include "downloader.h"

Downloader::Downloader()
{
    // Connecting SIGNALS/SLOTS =)))))
    connect(this, SIGNAL(uriAdded(QVariant)), this, SLOT(askForStatus(QVariant)));
    connect(this, SIGNAL(statusTold(const Status*)), this, SLOT(addUriToDb(const Status*)));
    connect(this, SIGNAL(uriAddedToDb(QString)), this, SLOT(askForRefreshStatus(QString)));
    connect(this, SIGNAL(statusRefreshed(const Status*)), this, SLOT(updateUriToDb(const Status*)));

    startAria();

}

Downloader::~Downloader()
{
    shutdown();
}

void Downloader::resume(const QString &uri)
{
    QVariantMap options;
    addUri(QVariant(uri), options);
}

void Downloader::askForStartAria()
{
    getVersion();
}
void Downloader::askForStatus(const QVariant &gid)
{
    tellStatus(gid, QVariantList());
}

void Downloader::askForRefreshStatus(const QString &gid)
{
    refreshStatus(QVariant(gid), QVariantList());
}

void Downloader::addUriToDb(const Status *status)
{
    yoDataBase db;
    QVariantMap uriMap;
    uriMap["gid"] = status->gid();
    uriMap["uri"] = status->files().first()->uris().first()->uri();
    uriMap["dir"] = status->dir();
    uriMap["status"] = status->status();
    uriMap["progress"] = status->progress();
    uriMap["dir"] = status->dir();
    uriMap["remaining_time"] = status->remainingTime();

    if(db.addUri(uriMap["gid"].toString(), uriMap["uri"].toString(), uriMap["dir"].toString(), uriMap["status"].toString(), uriMap["progress"].toInt())){
        uriMap["id"] = db.lastInsertedID();
        emit uriAddedToDb(uriMap["gid"].toString());
        emit uriAddedToDb(uriMap);
        // TODO: Some notify can be good here abour success ;)
    }
    // TODO: Some notify can be good here about failure ;?
}

void Downloader::updateUriToDb(const Status *status)
{
    yoDataBase db;
    if(db.updateUri(status->gid(), status->files().first()->uris().first()->uri(), status->dir(), status->status(), status->progress())){
        emit uriUpdatedOnDb(status);
    }
}
