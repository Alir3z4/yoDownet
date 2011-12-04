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

// Return correct file name
QString AbstractDownloader::fileName() const
{
    return m_fileName;
}

// Return full file destination path
QString AbstractDownloader::fileDestPath() const
{
    return m_fileDestPath;
}

// Return file size
int AbstractDownloader::fileSize() const
{
    return m_fileSize;
}
