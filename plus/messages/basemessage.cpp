#include "basemessage.h"

BaseMessage::BaseMessage(QObject *parent) :
    QObject(parent)
{
}

void BaseMessage::setText(const QString &message)
{
    _message = message;
}

QString BaseMessage::text() const
{
    return _message;
}

void BaseMessage::setTag(const BaseMessage::Tags &tag)
{
    _tag = tag;
}

BaseMessage::Tags BaseMessage::tag() const
{
    return _tag;
}

