#ifndef DOWNLOADHOLDER_H
#define DOWNLOADHOLDER_H

#include <QObject>

class DownloadHolder : public QObject
{
    Q_OBJECT
public:
    explicit DownloadHolder(QObject *parent = 0);

    QString uuid() const;
    void setUuid(const QString &uuid);

    QString url() const;
    void setUrl(const QString &url);

    QString savePath() const;
    void setSavePath(const QString &savePath);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QString status() const;
    void setStatus(const QString &status);

    QString progress() const;
    void setProgress(const QString &progress);

    QString remainingTime() const;
    void setRemainingTime(const QString &remainingTime);

    QString speed() const;
    void setSpeed(const QString &speed);

    QString added() const;
    void setAdded(const QString &added);

    QString downloaded() const;
    void setDownloaded(const QString &downloaded);

private:
    QString _uuid;
    QString _url;
    QString _savePath;
    QString _fileName;
    QString _status;
    QString _progress;
    QString _remainingTime;
    QString _speed;
    QString _added;
    QString _downloaded;

};

#endif // DOWNLOADHOLDER_H
