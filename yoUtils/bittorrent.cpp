#include "bittorrent.h"

BitTorrent::BitTorrent(QObject *parent) :
    QObject(parent)
{
}

void BitTorrent::setComment(const QString &comment)
{
    _comment = comment;
}

void BitTorrent::setCreationDate(const int &creationDate)
{
    _creationDate = creationDate;
}

void BitTorrent::setMode(const QString &mode)
{
    _mode = mode;
}

QString BitTorrent::comment() const
{
    return _comment;
}

int BitTorrent::creationDate() const
{
    return _creationDate;
}

QString BitTorrent::mode() const
{
    return _mode;
}
