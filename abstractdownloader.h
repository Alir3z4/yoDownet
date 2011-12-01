#ifndef ABSTRACTDOWNLOADER_H
#define ABSTRACTDOWNLOADER_H

#include <QObject>

class AbstractDownloader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDownloader(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ABSTRACTDOWNLOADER_H
