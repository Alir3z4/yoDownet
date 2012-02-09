#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include "fileinfo.h"

class Status : public QObject
{
    Q_OBJECT
public:
    explicit Status(QObject *parent = 0);

    QString gid() const;
    QString status() const;
    int totalLength() const;
    int completedLength() const;
    int uploadLength() const;
    //QString bitField() const;
    int downloadSpeed() const;
    int uploadSpeed() const;
    QString infoHash() const;
    int numSeeders() const;
    int pieceLength() const;
    int numPieces() const;
    int connections() const;
    int errorCode() const;
    QString followedBy() const;
    QString belongsTo() const;
    QString dir() const;
    QList<FileInfo*> files() const;

    // Overloaded :D
    QString remainingTime() const;
    QString downloadRate() const;
    int progress() const;

public slots:
    void setGid(const QString &gid);
    void setStatus(const QString &status);
    void setTotalLength(const int totalLength);
    void setCompletedLength(const int completedLength);
    void setUploadLength(const int uploadLength);
    //void setBitField(const QString &bitField);
    void setDownloadSpeed(const int downloadSpeed);
    void setUploadSpeed(const int uploadSpeed);
    void setInfoHash(const QString &infoHash);
    void setNumSeeders(const int numSeeders);
    void setPieceLength(const int pieceLength);
    void setNumPieces(const int numPieces);
    void setConnections(const int connections);
    void setErrorCode(const int errorCode);
    void setFollowedBy(const QString &followedBy);
    void setBelongsTo(const QString &belongsTo);
    void setDir(const QString &dir);
    void setFiles(const QList<FileInfo *> &files);


private:
    QString _gid;
    QString _status;
    int _totalLength;
    int _completedLength;
    int _uploadLength;
    //QString _bitField;
    int _downloadSpeed;
    int _uploadSpeed;
    QString _infoHash;
    int _numSeeders;
    int _pieceLength;
    int _numPieces;
    int _connections;
    int _errorCode;
    QString _followedBy;
    QString _belongsTo;
    QString _dir;
    QList<FileInfo*> _files;
};


#endif // STATUS_H
