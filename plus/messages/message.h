#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QQueue>
#include "plus/messages/basemessage.h"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = 0);
    ~Message();
    
    void addMessage(const BaseMessage::Tags &tag, const QString &message);

signals:
    void newMessage();

private slots:
    void showMessage();

private:
    BaseMessage *_baseMessage;
    QQueue<BaseMessage*> *_messages;
};

#endif // MESSAGE_H
