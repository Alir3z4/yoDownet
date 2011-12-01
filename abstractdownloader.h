#ifndef ABSTRACTDOWNLOADER_H
#define ABSTRACTDOWNLOADER_H

#include <QObject>

class AbstractDownloader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDownloader(QObject *parent = 0);

protected:
    // Holding Url, this one shoulda huged tightly
    // Because the main business is url:x
    QString url;
    // Then shoulda wink File name
    QString fileName;
    // Excusme, Where do you wanna go?
    QString fileDestPath;
    // Okay then, don't be shy my file
    // Just wanna know your size
    int fileSize;
};

#endif // ABSTRACTDOWNLOADER_H