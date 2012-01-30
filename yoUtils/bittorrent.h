#ifndef BITTORRENT_H
#define BITTORRENT_H

#include <QObject>

class BitTorrent : public QObject
{
    Q_OBJECT
public:
    explicit BitTorrent(QObject *parent = 0);

    void setComment(const QString &comment);
    void setCreationDate(const int &creationDate);
    void setMode(const QString &mode);

    QString comment() const;
    int creationDate() const;
    QString mode() const;
    
private:
    QString _comment;
    int _creationDate;
    QString _mode;
    
};

#endif // BITTORRENT_H
