#include "downloader.h"

Downloader::Downloader(QObject *parent) :
    QObject(parent), aria2(QString("http://localhost:6800/rpc").toStdString())
{
}

const QString Downloader::addUri(const QVector<QString> &uris)
{
    return aria2.addUri(uris);
}

const QString Downloader::addUri(const QVector<QString> &uris, QMap<QString, QString> &options)
{
    return aria2.addUri(uris, options);
}
