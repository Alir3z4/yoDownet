#include "message.h"

Message::Message(QObject *parent) :
    QObject(parent)
{
    _baseMessage = new BaseMessage;
    _messages = new QQueue<BaseMessage*>;

    connect(this, SIGNAL(newMessage()), SLOT(showMessage()));
}

Message::~Message()
{
    delete _baseMessage;
    delete _messages;
}

void Message::addMessage(const BaseMessage::Tags &tag, const QString &message)
{
    _baseMessage->setText(message);
    _baseMessage->setTag(tag);

    _messages->enqueue(_baseMessage);
    emit newMessage();
}

void Message::showMessage()
{}
