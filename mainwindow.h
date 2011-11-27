#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
