#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "yoUtils/yomessage.h"
#include "yoUtils/yodatabase.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_preferencesAction_triggered();

    void on_aboutQtAction_triggered();

    void on_importUrlsAction_triggered();
    void saveSettings();
    void loadSettings();
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    yoMessage msg;
    yoDataBase db;
};

#endif // MAINWINDOW_H
