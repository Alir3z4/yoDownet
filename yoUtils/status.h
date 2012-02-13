/****************************************************************************************
** status.h is part of yoDownet
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

#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include "yoUtils/fileinfo.h"

class Status : public QObject
{
    Q_OBJECT
public:
    explicit Status(QObject *parent = 0);

    // [inlines]
    inline QString remainingTime() const { return _remainingTime; }
    inline int downloadRate() const { return _downloadRate; }
    inline QString status() const { return _status; }
    inline double progress() const { return _progress; }
    
signals:
    
public slots:
    void setDownloadRate();
    void updateFileSize(qint64 bytesReceived, qint64 bytesTotal);
    inline void setStatus(const QString &status) { _status =  status; }

private:
    QString _status;
    QString _remainingTime;
    int _downloadRate;
    double _progress;
    FileInfo *_fileInfo;

    // [inlines]

    inline void setProgress(const double progress) { _progress = progress; }
    
};

#endif // STATUS_H
