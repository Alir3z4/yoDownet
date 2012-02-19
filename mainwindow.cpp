/****************************************************************************************
** mainwindow.cpp is part of yoDownet
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QSettings>
#include "preferencesdialog.h"
#include "urldialog.h"
#include <QDebug>
#include <QThread>

class QDateTime;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // read/load settings
    loadSettings();

    // Add actions from manuBar to MainWindow
    createActionsOnMainWindow();

    // Initialize urlsTable :|
    initurlsTable();

    // Connect the signals/slot
    connect(this, SIGNAL(downloadRequested(QString)), this, SLOT(initDownload(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::currentColumn(const int column) const
{
}

void MainWindow::on_preferencesAction_triggered()
{
    PreferencesDialog prefDialog;
    if(prefDialog.exec() == QDialog::Accepted) {
        // Doing some
    }
}

void MainWindow::on_aboutQtAction_triggered()
{
    msg.aboutQt(this, tr("yoDownet : About Qt"));
}

void MainWindow::on_actionAdd_triggered()
{
    urlDialog addUrlDialog;
    if(addUrlDialog.exec() == QDialog::Accepted) {
        emit downloadRequested(addUrlDialog.url());
    }

}

void MainWindow::on_actionResume_triggered()
{
}
void MainWindow::closeEvent(QCloseEvent * )
{
    saveSettings();
}

{
}

void MainWindow::addNewDlToUrlsTable(const Status *status)
{
}

void MainWindow::updateUrlsTable(const Status *status)
{

        }
    }
}

void MainWindow::initDownload(const QString &url)
{
    QThread *thread = new QThread;
    yoDownet *downloader = new yoDownet;
    db = new yoDataBase(this, downloader);
    downloader->moveToThread(thread);
    downloader->theDownload(url);
    // connect these guyz
    connect(downloader, SIGNAL(downloadInitialed(const Status*)), this, SLOT(addNewDlToUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downlaodResumed(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downloadUpdated(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
    thread->start();
}

void MainWindow::createActionsOnMainWindow()
{
    addActions(ui->menuBar->actions());
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");

    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("geometry", geometry());
    settings.setValue("fullScreen", isFullScreen());
    settings.setValue("state", saveState());

    settings.beginGroup("menuBar");
    settings.setValue("isHidden", ui->menuBar->isHidden());
    settings.endGroup();

    settings.beginGroup("statusBar");
    settings.setValue("isHidden", ui->statusBar->isHidden());
    settings.endGroup();

    settings.beginGroup("mainToolBar");
    settings.setValue("isHidden", ui->mainToolBar->isHidden());
    settings.setValue("geometry", ui->mainToolBar->geometry());
    settings.endGroup();

    settings.beginGroup("showMenuBarAction");
    settings.setValue("isChecked", ui->showMenuBarAction->isChecked());
    settings.setValue("shortcut", ui->showMenuBarAction->shortcut());
    settings.endGroup();

    settings.beginGroup("showToolBarAction");
    settings.setValue("isChecked", ui->showToolBarAction->isChecked());
    settings.setValue("shortcut", ui->showToolBarAction->shortcut());
    settings.endGroup();

    settings.beginGroup("showStatusBarAction");
    settings.setValue("isChecked", ui->showStatusBarAction->isChecked());
    settings.setValue("shortcut", ui->showStatusBarAction->shortcut());
    settings.endGroup();

    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    resize(settings.value("size", QSize(400, 400)).toSize());
    setGeometry(settings.value("geometry", QRect(49, 331, 670, 445)).toRect());
    if(settings.value("fullscreen").toBool())
        showFullScreen();
    restoreState(settings.value("state", QByteArray()).toByteArray());

    settings.beginGroup("menuBar");
    ui->menuBar->setHidden(settings.value("isHidden", false).toBool());
    settings.endGroup();

    settings.beginGroup("statusBar");
    ui->statusBar->setHidden(settings.value("isHidden", false).toBool());
    settings.endGroup();

    settings.beginGroup("mainToolBar");
    ui->mainToolBar->setHidden(settings.value("isHidden", false).toBool());
    ui->mainToolBar->setGeometry(settings.value("geometry").toRect());
    settings.endGroup();

    settings.beginGroup("showMenuBarAction");
    ui->showMenuBarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showMenuBarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showMenuBarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.beginGroup("showToolBarAction");
    ui->showToolBarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showToolBarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showToolBarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.beginGroup("showStatusBarAction");
    ui->showStatusBarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showStatusBarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showStatusBarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.endGroup();
}
