#include "message.h"
#include <QTimer>
#include <QDebug>

Message::Message(QObject *parent) :
    QObject(parent), _messages(new QQueue<BaseMessage>)
{
    QTimer *checkQueue = new QTimer(this);
    connect(checkQueue, SIGNAL(timeout()), this, SLOT(showMessage()));
    checkQueue->start(5000);
}

Message::~Message()
{
    delete _messages;
}

void Message::addMessage(const QString &title, const QString &message, const MessageConstants::Tag tag)
{
    BaseMessage baseMessage;
    baseMessage.setMessage(title, message, tag);

    _messages->enqueue(baseMessage);
}

void Message::setSysTrayIcon(SystemTrayIcon *sysTrayIcon)
{
    _sysTrayIcon = sysTrayIcon;
}

void Message::showMessage()
{
    qDebug() << _messages->count();
    if(_messages->count() > 0){
        QString messageTitle = _messages->first().title();
        QString messageBody = _messages->first().body();
        MessageConstants::Tag messageTag = _messages->first().tag();
        _messages->removeFirst();
        _sysTrayIcon->showMessage(messageTitle, messageBody, messageTag);
        qDebug() << messageTitle << "\n" << messageBody << " ~ " << messageTag;
    }
}
