#include "fileinfo.h"

FileInfo::FileInfo(QObject *parent) :
    QObject(parent)
{
}

void FileInfo::setIndex(const QString &index)
{
    _index = index;
}

void FileInfo::setPath(const QString &path)
{
    _path = path;
}

void FileInfo::setLength(const QString &length)
{
    _length = length;
}

void FileInfo::setSelected(const QString &selected)
{
    _selected = selected;
}

void FileInfo::setUris(const QVector<UriStatus> &uris)
{
    _uris = uris;
}

QString FileInfo::index() const
{
    return _index;
}

QString FileInfo::path() const
{
    return _path;
}

QString FileInfo::length() const
{
    return _length;
}

QString FileInfo::selected() const
{
    return _selected;
}

QVector<UriStatus> FileInfo::uris() const
{
    return _uris;
}
