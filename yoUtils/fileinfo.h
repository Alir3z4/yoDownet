/****************************************************************************************
** fileinfo.h is part of yoDownet
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

#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QString>
#include <QVector>
#include "uristatus.h"

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = 0);

    void setIndex(const QString &index);
    void setPath(const QString &path);
    void setLength(const QString &length);
    void setCompletedLength(const QString &completedLength);
    void setSelected(const QString &selected);
    void setUris(const QList<UriStatus*> &uris);

    QString index() const;
    QString path() const;
    QString length() const;
    QString completedLength() const;
    QString selected() const;
    QList<UriStatus*> uris() const;

private:
    QString _index;
    QString _path;
    QString _length;
    QString _completedLength;
    QString _selected;
    QList<UriStatus*> _uris;
};

#endif // FILEINFO_H
