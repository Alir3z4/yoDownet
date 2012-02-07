#include "downloader.h"

Downloader::Downloader()
{
    // Connecting SIGNALS/SLOTS =)))))
    connect(this, SIGNAL(uriAdded(QVariant)), this, SLOT(askForStatus(QVariant)));
    connect(this, SIGNAL(statusTold(const Status*)), this, SLOT(addUriToDb(const Status*)));
    connect(this, SIGNAL(uriAddedToDb(QString)), this, SLOT(askForRefreshStatus(QString)));
    connect(this, SIGNAL(statusRefreshed(const Status*)), this, SLOT(updateUriToDb(const Status*)));

}

Downloader::~Downloader()
{
    shutdown();
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


void Downloader::updateUriToDb(const Status *status)
{
    yoDataBase db;
    if(db.updateUri(status->gid(), status->files().first()->uris().first()->uri(), status->dir(), status->status(), status->bitField().toInt())){
        emit uriUpdatedOnDb(status);
    }
}
