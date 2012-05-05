#include "basemessage.h"

BaseMessage::BaseMessage()
{
    return;
}

void BaseMessage::setTitle(const QString &title)
{
    _title = title;
}

QString BaseMessage::title() const
{
    return _title;
}

void BaseMessage::setBody(const QString &message)
{
    _message = message;
}

void BaseMessage::setMessage(const QString &title, const QString &message, const MessageConstants::Tag &tag)
{
    _title = title;
    _message = message;
    _tag = tag;
}

void BaseMessage::setTag(const MessageConstants::Tag &tag)
{
    _tag = tag;
}

MessageConstants::Tag BaseMessage::tag() const
{
    return _tag;
}

QString BaseMessage::body() const
{
    return _message;
}

