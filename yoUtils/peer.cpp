/****************************************************************************************
** peer.cpp is part of yoDownet
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
