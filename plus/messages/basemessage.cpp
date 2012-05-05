#include "basemessage.h"

BaseMessage::BaseMessage()
{
    return;
}

void BaseMessage::setText(const QString &message)
{
    _message = message;
}

QString BaseMessage::text() const
{
    return _message;
}

void BaseMessage::setTag(const MessageConstants::Tag &tag)
{
    _tag = tag;
}

MessageConstants::Tag BaseMessage::tag() const
{
    return _tag;
}

