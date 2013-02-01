/****************************************************************************************
** file.h is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QFile>

class File : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFile *file READ file WRITE setFile)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(int completedLength READ completedLength WRITE setCompletedLength)

public:
    explicit File(QObject *parent = 0);

    void setFile(QFile *file);
    QFile *file();

    void setPath(const QString &path);
    QString path() const;

    void setCompletedLength(const int &completedLength);
    int completedLength() const;

private:
    QFile *_file;
    QString _path;
    int _completedLength;
};

#endif // FILE_H
