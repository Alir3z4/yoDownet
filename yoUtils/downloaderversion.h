#ifndef DOWNLOADERVERSION_H
#define DOWNLOADERVERSION_H

#include <QObject>
#include <QVector>

class DownloaderVersion : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderVersion(QObject *parent = 0);

    void setVersion(const QString &version);
    void setEnabledFeatures(const QVector<QString> &enabledFeatures);

    QString version() const;
    QVector<QString> enabledFeatures() const;

private:
    QString _version;
    QVector<QString> _enabledFeatures;

    
};

#endif // DOWNLOADERVERSION_H
