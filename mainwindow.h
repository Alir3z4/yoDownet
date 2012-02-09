#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "yoUtils/yomessage.h"
#include "yoUtils/yodatabase.h"
#include "yoUtils/yosettings.h"
#include "downloader.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString currentColumn(const int column) const;

signals:
    void rowPaused(const QString &uri);
    void rowUnPaused(const QString &uri);
    void rowRemoved(const QString &uri);
    void rowStopped(const QString &uri);

private slots:
    void on_preferencesAction_triggered();
    void on_aboutQtAction_triggered();
    void on_actionAdd_triggered();
    void on_actionRemove_triggered();
    void on_actionStop_triggered();
    void on_actionPause_triggered();
    void on_actionResume_triggered();
    void on_actionResumeAll_triggered();
    // Create actions on MainWindows
    void createActionsOnMainWindow();
    void saveSettings();
    void loadSettings();
    void closeEvent(QCloseEvent *);
    void askForUpdateUrisTable();
    void updateUrisTable(const Status *status);
    void initUrisTable();
    void addNewDlToUrisTable(const QVariantMap &uri);
    //
    void downloadPaused(const QString &uri);
    void downloadUnPaused(const QString &uri);
    void downloadRemoved(const QString &uri);
    void downloadStopped(const QString &uri);

private:
    Ui::MainWindow *ui;
    yoMessage msg;
    yoDataBase *db;
    Downloader *downloader;
    yoSettings *_settings;

};

#endif // MAINWINDOW_H
