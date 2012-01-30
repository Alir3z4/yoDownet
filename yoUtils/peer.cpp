#include "peer.h"

Peer::Peer(QObject *parent) :
    QObject(parent)
{
}

void Peer::setPeerId(const QString &peerId)
{
    _peerId = peerId;
}

void Peer::setIp(const QString &ip)
{
    _ip = ip;
}

void Peer::setPort(const QString &port)
{
    _port = port;
}

void Peer::setBitField(const QString &bitField)
{
    _bitField = bitField;
}

void Peer::setAmChoking(const QString &amChoking)
{
    _amChoking = amChoking;
}

void Peer::setPeerChoking(const QString &peerChoking)
{
    _peerChoking = peerChoking;
}

void Peer::setDownloaadSpeed(const QString &downloaadSpeed)
{
    _downloaadSpeed = downloaadSpeed;
}

void Peer::setUploadSpeed(const QString &uploadSpeed)
{
    _uploadSpeed = uploadSpeed;
}

void Peer::setSeeder(const QString &seeder)
{
    _seeder = seeder;
}

QString Peer::peerId() const
{
    return _peerId;
}

QString Peer::ip() const
{
    return _ip;
}

QString Peer::port() const
{
    return _port;
}

QString Peer::bitField() const
{
    return _bitField;
}

QString Peer::amChoking() const
{
    return _amChoking;
}

QString Peer::peerChoking() const
{
    return _peerChoking;
}

QString Peer::downloaadSpeed() const
{
    return _downloaadSpeed;
}

QString Peer::uploadSpeed() const
{
    return _uploadSpeed;
}

QString Peer::seeder() const
{
    return _seeder;
}
