#ifndef DOWNLOADERVERSION_H
#define DOWNLOADERVERSION_H

#include <QObject>
#include <QStringList>

class DownloaderVersion : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderVersion(QObject *parent = 0);

    void setVersion(const QString &version);
    void setEnabledFeatures(const QStringList &enabledFeatures);

    QString version() const;
    QStringList enabledFeatures() const;

private:
    QString _version;
    QStringList _enabledFeatures;

    
};

#endif // DOWNLOADERVERSION_H
