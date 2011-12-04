#include "abstractdownloader.h"

AbstractDownloader::AbstractDownloader(QObject *parent) :
    QObject(parent)
{
}

// Return Downloader name
QString AbstractDownloader::downloaderName() const
{
    return m_downloaderName;
}

// Return url
QString AbstractDownloader::url() const
{
    return m_url;
}
