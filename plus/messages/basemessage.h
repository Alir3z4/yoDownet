#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <QObject>

class BaseMessage : public QObject
{
    Q_OBJECT
public:
    explicit BaseMessage(QObject *parent = 0);

    enum Tags{
        Debug,
        Info,
        Success,
        Warning,
        Error
    };

    void setText(const QString &message);
    QString text() const;

    void setTag(const Tags &tag);
    Tags tag() const;

private:
    QString _message;
    Tags _tag;
};

#endif // BASEMESSAGE_H
