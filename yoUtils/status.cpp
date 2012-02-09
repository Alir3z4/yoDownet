/****************************************************************************************
** status.cpp is part of yoDownet
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

#include "status.h"
#include <QtCore/QTime>

Status::Status(QObject *parent) :
    QObject(parent)
{
}

void Status::setGid(const QString &gid)
{
    _gid = gid;
}

void Status::setStatus(const QString &status)
{
    _status = status;
}

void Status::setTotalLength(const int totalLength)
{
    _totalLength = totalLength;
}

void Status::setCompletedLength(const int completedLength)
{
    _completedLength = completedLength;
}

void Status::setUploadLength(const int uploadLength)
{
    _uploadLength = uploadLength;
}
//void Status::setBitField(const QString &bitField)
//{
//    _bitField = bitField;
//}

void Status::setDownloadSpeed(const int downloadSpeed)
{
    _downloadSpeed = downloadSpeed;
}

void Status::setUploadSpeed(const int uploadSpeed)
{
    _uploadSpeed = uploadSpeed;
}

void Status::setInfoHash(const QString &infoHash)
{
    _infoHash = infoHash;
}

void Status::setNumSeeders(const int numSeeders)
{
    _numSeeders = numSeeders;
}

void Status::setPieceLength(const int pieceLength)
{
    _pieceLength = pieceLength;
}

void Status::setNumPieces(const int numPieces)
{
    _numPieces = numPieces;
}

void Status::setConnections(const int connections)
{
    _connections = connections;
}

void Status::setErrorCode(const int errorCode)
{
    _errorCode = errorCode;
}

void Status::setFollowedBy(const QString &followedBy)
{
    _followedBy = followedBy;
}

void Status::setBelongsTo(const QString &belongsTo)
{
    _belongsTo = belongsTo;
}

void Status::setDir(const QString &dir)
{
    _dir = dir;
}

void Status::setFiles(const QList<FileInfo *> &files)
{
    _files = files;
}

QString Status::gid() const
{
    return _gid;
}

QString Status::status() const
{
    return _status;
}

int Status::totalLength() const
{
    return _totalLength;
}

int Status::completedLength() const
{
    return _completedLength;
}

int Status::uploadLength() const
{
    return _uploadLength;
}

int Status::progress() const
{
    if(totalLength() > 0)
        return completedLength()*100/totalLength();
    else
        return 0;
}
//QString Status::bitField() const
//{
//    return _bitField;
//}

int Status::downloadSpeed() const
{
    return _downloadSpeed;
}

int Status::uploadSpeed() const
{
    return _uploadSpeed;
}

QString Status::infoHash() const
{
    return _infoHash;
}

int Status::numSeeders() const
{
    return _numSeeders;
}

int Status::pieceLength() const
{
    return _pieceLength;
}

int Status::numPieces() const
{
    return _numPieces;
}

int Status::connections() const
{
    return _connections;
}

int Status::errorCode() const
{
    return _errorCode;
}

QString Status::followedBy() const
{
    return _followedBy;
}

QString Status::belongsTo() const
{
    return _belongsTo;
}

QString Status::dir() const
{
    return _dir;
}

QList<FileInfo *> Status::files() const
{
    return _files;
}

QString Status::remainingTime() const
{
    if(downloadSpeed() > 0){
        int speed = downloadSpeed();
        int remLength = totalLength() - completedLength();
        int remSecond = remLength/speed;
        int hour = remSecond/3600;
        remSecond = remSecond%3600;
        int minute = remSecond/60;
        remSecond = remSecond%60;
        return QTime(hour, minute, remSecond).toString();
    }

    return QString("n/a");

}

QString Status::downloadRate() const
{
    if(downloadSpeed() > 0){
        return QString("%1Kb/s").arg((double)downloadSpeed()/1024.0);
    }
    return QString(tr("n/a"));
}
