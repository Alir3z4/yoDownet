#ifndef DOWNLOADHOLDER_H
#define DOWNLOADHOLDER_H

#include <QObject>
#include "download/downloadconstants.h"

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

    int status() const;
    void setStatus(const int &status);

    int progress() const;
    void setProgress(const int &progress);

    QString remainingTime() const;
    void setRemainingTime(const QString &remainingTime);

    QString speed() const;
    void setSpeed(const QString &speed);

    QString added() const;
    void setAdded(const QString &added);

    QString downloaded() const;
    void setDownloaded(const QString &downloaded);

    QVariant attributeValueById(const DownloadConstants::Attributes::Attributes &attr) const;

private:
    QString _uuid;
    QString _url;
    QString _savePath;
    QString _fileName;
    int _status;
    int _progress;
    QString _remainingTime;
    QString _speed;
    QString _added;
    QString _downloaded;

};

#endif // DOWNLOADHOLDER_H
