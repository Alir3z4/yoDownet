#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QQueue>
#include "plus/messages/basemessage.h"
#include "ui/widget/systemtrayicon.h"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = 0);
    ~Message();

    void addMessage(const QString &title, const QString &message, const MessageConstants::Tag tag);
    void setSysTrayIcon(SystemTrayIcon *sysTrayIcon);

private slots:
    virtual void showMessage();

private:
    QQueue<BaseMessage> *_messages;
    SystemTrayIcon *_sysTrayIcon;
    QTimer *_checkQueue;
};

#endif // MESSAGE_H
