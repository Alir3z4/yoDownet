/****************************************************************************************
** fileinfo.cpp is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

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

void FileInfo::setCompletedLength(const QString &completedLength)
{
    _completedLength = completedLength;
}

void FileInfo::setSelected(const QString &selected)
{
    _selected = selected;
}

void FileInfo::setUris(const QList<UriStatus *> &uris)
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

QString FileInfo::completedLength() const
{
    return _completedLength;
}

QString FileInfo::selected() const
{
    return _selected;
}

QList<UriStatus *> FileInfo::uris() const
{
    return _uris;
}
