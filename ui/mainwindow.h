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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include "util/yodatabase.h"
#include "ui/widget/systemtrayicon.h"
#include "downloader/yodownet.h"
#include "util/urlmodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList currentColumns(const int &column = UrlModel::url) const;

private slots:
    void on_preferencesAction_triggered();
    void on_aboutQtAction_triggered();
    void on_addAction_triggered();
    void on_pauseAction_triggered();
    void on_resumeAction_triggered();
    void on_removeAction_triggered();
    void on_removeFromListAction_triggered();
    void on_reportBugAction_triggered();
    void on_aboutyoDownetAction_triggered();
    void createActionsOnMainWindow();
    void saveSettings();
    void loadSettings();
    void initUrlsTable();
    void updateUrlsTable(const Status *status);
    void submitUrlViewChanges();

    void onDownloadRemoved(const QString &fileName);

private:
    Ui::MainWindow *ui;
    yoDataBase *db;
    SystemTrayIcon *_trayIcon;
    QMenu *_trayMenu;
    UrlModel *model;
    yoDownet *downloader;

    void prepareTrayIcon();
    void closeEvent(QCloseEvent * event);

};

#endif // MAINWINDOW_H
