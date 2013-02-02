/****************************************************************************************
** status.h is part of yoDownet
**
** Copyright 2012, 2013 Alireza Savand <alireza.savand@gmail.com>
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
#include <QTime>
#include <QUuid>
#include "download/file.h"

class Status : public QObject
{
    Q_OBJECT
    Q_ENUMS(DownloadMode)
    Q_ENUMS(DownloadStatus)

public:
    explicit Status(QObject *parent = 0);

    enum DownloadMode{
        NewDownload,
        ResumeDownload
    };

    enum DownloadStatus{
        Idle,
        Starting,
        Downloading,
        Finished,
        Failed,
        Paused
    };

    QString remainingTime() const;
    QString downloadRate() const;
    QString downloadModeString() const;

    QList<File*> files() const;

    void setFileAlreadyBytes(const qint64 fileAlreadyBytes);
    void setBytesTotal(const qint64 totalLength);

    qint64 bytesTotal() const;
    void setBytesReceived(const qint64 completedLength);

    qint64 bytesReceived() const;
    int progress() const;

    void setDownloadMode(const DownloadMode dlMode);
    DownloadMode downloadMode() const;

    void setDownloadStatus(const DownloadStatus dlStatus);
    DownloadStatus downloadStatus() const;

public slots:
    void startTime();
    void updateFileStatus(qint64 bytesReceived, qint64 bytesTotal);

private:
    QString _remainingTime;
    QList<File*> _files;
    qint64 _fileAlreadyBytes;
    qint64 _bytesTotal;
    qint64 _bytesReceived;
    int _downloadRate;
    int _progress;
    QTime *_startTime;
    DownloadMode _dlMode;
    DownloadStatus _dlStatus;

};

#endif // STATUS_H
