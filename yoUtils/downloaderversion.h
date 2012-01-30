#ifndef DOWNLOADERVERSION_H
#define DOWNLOADERVERSION_H

#include <QObject>

class DownloaderVersion : public QObject
{
    Q_OBJECT
public:
    explicit DownloaderVersion(QObject *parent = 0);
    
    void setFaultCode(const int &faultCode);
    void setFaultString(const QString &faultString);

    int faultCode() const;
    QString faultString() const;

private:
    int _faultCode;
    QString _faultString;
    
};

#endif // DOWNLOADERVERSION_H
