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

    void setReady(const QList<QAction *> &actions, const QIcon &icon);

signals:
    void ready();

private slots:
    void showTryIcon();

private:
    QSystemTrayIcon *_tryIcon;
    QMenu *_tryIconMenu;

};

#endif // SYSTEMTRAYICON_H
