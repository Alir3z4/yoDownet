#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include "fileinfo.h"

class Status : public QObject
{
    Q_OBJECT
public:
    explicit Status(QObject *parent = 0);

    void setGid(const QString &gid);
    void setStatus(const QString &status);
    void setTotalLength(const QString &totalLength);
    void setCompletedLength(const QString &completedLength);
    void setUploadLength(const QString &uploadLength);
    void setBitField(const QString &bitField);
    void setDownloadSpeed(const QString &downloadSpeed);
    void setUploadSpeed(const QString &uploadSpeed);
    void setInfoHash(const QString &infoHash);
    void setNumSeeders(const QString &numSeeders);
    void setPieceLength(const QString &pieceLength);
    void setNumPieces(const QString &numPieces);
    void setConnections(const QString &connections);
    void setErrorCode(const QString &errorCode);
    void setFollowedBy(const QString &followedBy);
    void setBelongsTo(const QString &belongsTo);
    void setDir(const QString &dir);
    void setFiles(const QVector<FileInfo *> &files);

    QString gid() const;
    QString status() const;
    QString totalLength() const;
    QString completedLength() const;
    QString uploadLength() const;
    QString bitField() const;
    QString downloadSpeed() const;
    QString uploadSpeed() const;
    QString infoHash() const;
    QString numSeeders() const;
    QString pieceLength() const;
    QString numPieces() const;
    QString connections() const;
    QString errorCode() const;
    QString followedBy() const;
    QString belongsTo() const;
    QString dir() const;
    QVector<FileInfo*> files() const;

private:
    QString _gid;
    QString _status;
    QString _totalLength;
    QString _completedLength;
    QString _uploadLength;
    QString _bitField;
    QString _downloadSpeed;
    QString _uploadSpeed;
    QString _infoHash;
    QString _numSeeders;
    QString _pieceLength;
    QString _numPieces;
    QString _connections;
    QString _errorCode;
    QString _followedBy;
    QString _belongsTo;
    QString _dir;
    QVector<FileInfo*> _files;
};


#endif // STATUS_H
