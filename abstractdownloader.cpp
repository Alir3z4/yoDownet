#include "abstractdownloader.h"

AbstractDownloader::AbstractDownloader(QObject *parent) :
    QObject(parent)
{
}

// Return Downloader name
QString AbstractDownloader::downloaderName() const
{
    return dlerName;
}
