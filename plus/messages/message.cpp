#include "message.h"
#include <QTimer>

Message::Message(QObject *parent) :
    QObject(parent), _messages(new QQueue<BaseMessage>)
{
}

Message::~Message()
{
    delete _messages;
    delete _checkQueue;
}

void Message::addMessage(const QString &title, const QString &message, const MessageConstants::Tag tag)
{
    BaseMessage baseMessage;
    baseMessage.setMessage(title, message, tag);

    _checkQueue = new QTimer(this);
    connect(_checkQueue, SIGNAL(timeout()), this, SLOT(showMessage()));
    _checkQueue->start(3000);

    _messages->enqueue(baseMessage);
}

void Message::setSysTrayIcon(SystemTrayIcon *sysTrayIcon)
{
    _sysTrayIcon = sysTrayIcon;
}

void Message::showMessage()
{
    if(_messages->count() > 0){
        QString messageTitle = _messages->first().title();
        QString messageBody = _messages->first().body();
        MessageConstants::Tag messageTag = _messages->first().tag();
        _messages->removeFirst();
        _sysTrayIcon->showMessage(messageTitle, messageBody, messageTag);
        if(_messages->count() == 0){
            disconnect(_checkQueue, SIGNAL(timeout()), this, SLOT(showMessage()));
            _checkQueue = 0;
        }
    }
}
