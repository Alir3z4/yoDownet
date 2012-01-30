#ifndef PEER_H
#define PEER_H

#include <QObject>

class Peer : public QObject
{
    Q_OBJECT
public:
    explicit Peer(QObject *parent = 0);

    void setPeerId(const QString &peerId);
    void setIp(const QString &ip);
    void setPort(const QString &port);
    void setBitField(const QString &bitField);
    void setAmChoking(const QString &amChoking);
    void setPeerChoking(const QString &peerChoking);
    void setDownloaadSpeed(const QString &downloaadSpeed);
    void setUploadSpeed(const QString &uploadSpeed);
    void setSeeder(const QString &seeder);

    QString peerId() const;
    QString ip() const;
    QString port() const;
    QString bitField() const;
    QString amChoking() const;
    QString peerChoking() const;
    QString downloaadSpeed() const;
    QString uploadSpeed() const;
    QString seeder() const;

private:
    QString _peerId;
    QString _ip;
    QString _port;
    QString _bitField;
    QString _amChoking;
    QString _peerChoking;
    QString _downloaadSpeed;
    QString _uploadSpeed;
    QString _seeder;
};

#endif // PEER_H
