#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include "yoDownloaders/aria2c.h"
#include "yoUtils/yodatabase.h"

class Downloader : public Aria2c
{
    Q_OBJECT

public:
    explicit Downloader();
    ~Downloader();

public slots:
    void askForStartAria();
    void askForRefreshStatus(const QString &gid);

signals:
    void uriUpdatedOnDb(const Status *status);
    void uriAddedToDb(const QString &gid);
    void statusAsked(const Status *status);

private slots:
    void askForStatus(const QVariant &gid);
    void addUriToDb(const Status *status);
    void updateUriToDb(const Status *status);

private:

};

#endif // DOWNLOADER_H
