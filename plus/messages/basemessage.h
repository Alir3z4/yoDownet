#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <QString>
#include "plus/messages/constants.h"

class BaseMessage
{
public:
    explicit BaseMessage();


    void setText(const QString &message);
    QString text() const;

    void setTag(const Tags &tag);
    Tags tag() const;

private:
    QString _message;
    MessageConstants::Tag _tag;
};

#endif // BASEMESSAGE_H
