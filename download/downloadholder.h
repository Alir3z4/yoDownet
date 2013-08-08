#ifndef DOWNLOADHOLDER_H
#define DOWNLOADHOLDER_H

#include <QObject>

class DownloadHolder : public QObject
{
    Q_OBJECT
public:
    explicit DownloadHolder(QObject *parent = 0);

};

#endif // DOWNLOADHOLDER_H
