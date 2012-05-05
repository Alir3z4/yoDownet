#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include "plus/messages/constants.h"

class SystemTrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QWidget *parent = 0);

    void setReady(QMenu *menu, const QIcon &icon);
    void showMessage(const QString &title, const QString &msg, MessageConstants::Tag icon, int msec = 7000);

signals:
    void ready();
    void triggered();
    void doubleClicked();
    void middleClicked();

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon *_trayIcon;
};

#endif // SYSTEMTRAYICON_H
