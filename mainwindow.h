/****************************************************************************************
** mainwindow.h is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

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
