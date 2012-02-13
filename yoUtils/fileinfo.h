/****************************************************************************************
** fileinfo.h is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = 0);

    inline QString path() const { return _path; }

    // [inlines]
    inline void setPath(const QString &path) { _path = path; }
    inline int length() const { return _length; }
    inline int completedLength() const { return _completedLength; }
    inline void setCompletedLength(const int completedLength) { _completedLength = completedLength; }
    inline void setLength(const int length) { _length = length; }

public slots:

private:
    QString _path;
    int _length;
    int _completedLength;

    // [inlines]

};

#endif // FILEINFO_H
