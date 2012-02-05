#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QString>
#include <QVector>
#include "uristatus.h"

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = 0);

    void setIndex(const QString &index);
    void setPath(const QString &path);
    void setLength(const QString &length);
    void setCompletedLength(const QString &completedLength);
    void setSelected(const QString &selected);
    void setUris(const QList<UriStatus*> &uris);

    QString index() const;
    QString path() const;
    QString length() const;
    QString completedLength() const;
    QString selected() const;
    QList<UriStatus*> uris() const;

private:
    QString _index;
    QString _path;
    QString _length;
    QString _completedLength;
    QString _selected;
    QList<UriStatus*> _uris;
};

#endif // FILEINFO_H
