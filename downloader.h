#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include "yoDownloaders/aria2c.h"

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

    // Operations :|
    const QString addUri(const QVector<QString> &uris);
    const QString addUri(const QVector<QString> &uris, QMap<QString, QString> &options);

private:
    Aria2c aria2;


};

#endif // DOWNLOADER_H
