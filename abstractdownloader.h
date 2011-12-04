#ifndef ABSTRACTDOWNLOADER_H
#define ABSTRACTDOWNLOADER_H

#include <QObject>

class AbstractDownloader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDownloader(QObject *parent = 0);

    // Best place to keep inline functions
    // Set file size
    inline void setFileSize(int &argSize) { m_fileSize =  argSize; }
    // Set file destination Path [fileDestPath]
    inline virtual void setFileDestPath(QString &argDestPath) { m_fileDestPath = argDestPath; }

    // Getter functions goes here
    QString downloaderName() const;
    QString url() const;
    QString fileName() const;
    QString fileDestPath() const;
    int fileSize() const;

protected:
    // Yummy! downloader name
    QString m_downloaderName;
    // Holding Url, this one shoulda huged tightly
    // Because the main business is url:x
    QString m_url;
    // Then shoulda wink File name
    QString m_fileName;
    // Excusme, Where do you wanna go?
    QString m_fileDestPath;
    // Okay then, don't be shy my file
    // Just wanna know your size
    int m_fileSize;
};

#endif // ABSTRACTDOWNLOADER_H
