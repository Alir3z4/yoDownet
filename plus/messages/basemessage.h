#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <QString>
#include "plus/messages/constants.h"

class BaseMessage
{
public:
    explicit BaseMessage();

    void setTitle(const QString &title);
    QString title() const;

    void setBody(const QString &message);
    QString body() const;

    void setMessage(const QString &title, const QString &message, const MessageConstants::Tag &tag);

    void setTag(const MessageConstants::Tag &tag);
    MessageConstants::Tag tag() const;

private:
    QString _title;
    QString _message;
    MessageConstants::Tag _tag;
};

#endif // BASEMESSAGE_H
