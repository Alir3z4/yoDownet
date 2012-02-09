/****************************************************************************************
** peer.h is part of yoDownet
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
