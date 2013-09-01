/****************************************************************************************
** mainwindow.h is part of yoDownet
**
** Copyright 2011, 2012, 2013 Alireza Savand <alireza.savand@gmail.com>
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
#include <QtWidgets/QTableWidgetItem>
#include <QCloseEvent>
#include "core/logme.h"
#include "download/downloadtablemodel.h"
#include "download/downloadconstants.h"
#include "plus/messages/message.h"
#include "ui/widget/systemtrayicon.h"
#include "downloader/yodownet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList currentColumns(const int &column = DownloadConstants::Attributes::URL) const;

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
    void updateUrlsTable(const Download *download);
    void submitUrlViewChanges();

    void onDownloadRemoved(const QString &fileName);
    void onDownloadResumed(const Download *download);
    void trayIconTriggered();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    SystemTrayIcon *_trayIcon;
    QMenu *_trayMenu;
    DownloadTableModel *model;
    yoDownet *downloader;
    Message *_message;
    LogMe *_logger;

    void prepareTrayIcon();
    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
