#include "status.h"

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

void Status::setTotalLength(const QString &totalLength)
{
    _totalLength = totalLength;
}

void Status::setCompletedLength(const QString &completedLength)
{
    _completedLength = completedLength;
}

void Status::setUploadLength(const QString &uploadLength)
{
    _uploadLength = uploadLength;
}

void Status::setBitField(const QString &bitField)
{
    _bitField = bitField;
}

void Status::setDownloadSpeed(const QString &downloadSpeed)
{
    _downloadSpeed = downloadSpeed;
}

void Status::setInfoHash(const QString &infoHash)
{
    _infoHash = infoHash;
}

void Status::setNumSeeders(const QString &numSeeders)
{
    _numSeeders = numSeeders;
}

void Status::setPieceLength(const QString &pieceLength)
{
    _pieceLength = pieceLength;
}

void Status::setNumPieces(const QString &numPieces)
{
    _numPieces = numPieces;
}

void Status::setConnections(const QString &connections)
{
    _connections = connections;
}

void Status::setErrorCode(const QString &errorCode)
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

void Status::setFiles(const QVector<FileInfo> &files)
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

QString Status::totalLength() const
{
    return _totalLength;
}

QString Status::completedLength() const
{
    return _completedLength;
}

QString Status::uploadLength() const
{
    return _uploadLength;
}

QString Status::bitField() const
{
    return _bitField;
}

QString Status::downloadSpeed() const
{
    return _downloadSpeed;
}

QString Status::infoHash() const
{
    return _infoHash;
}

QString Status::numSeeders() const
{
    return _numSeeders;
}

QString Status::pieceLength() const
{
    return _pieceLength;
}

QString Status::numPieces() const
{
    return _numPieces;
}

QString Status::connections() const
{
    return _connections;
}

QString Status::errorCode() const
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

QVector<FileInfo> Status::files() const
{
    return _files;
}
