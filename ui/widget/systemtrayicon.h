#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTrayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QWidget *parent = 0);

    void setReady(QMenu *menu, const QIcon &icon);

signals:
    void ready();


private:
    QSystemTrayIcon *_tryIcon;
};

#endif // SYSTEMTRAYICON_H
