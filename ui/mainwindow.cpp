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
#include "ui/dialog/preferencesdialog.h"
#include "ui/dialog/urldialog.h"
#include "ui/dialog/aboutdialog.h"
#include "ui/dialog/reportbugdialog.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),model(new UrlModel(parent)),
    downloader(new yoDownet(parent)), _message(new Message(parent))
{
    ui->setupUi(this);

    loadSettings();
    createActionsOnMainWindow();

    // Initialize urlsTable :|
    initUrlsTable();

    // Connect the signals/slot
    connect(downloader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(updateUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downloadPaused(const Download*)), this, SLOT(submitUrlViewChanges()));
    connect(downloader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(updateUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(onDownloadResumed(const Status*)));
    connect(downloader, SIGNAL(downloadUpdated(const Download*)), this, SLOT(updateUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downloadRemoved(QString)), this, SLOT(onDownloadRemoved(QString)));

    connect(ui->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    prepareTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete downloader;
    delete _trayIcon;
    delete _trayMenu;
}

QStringList MainWindow::currentColumns(const int &column) const
{
    QModelIndexList indexes = ui->urlView->selectionModel()->selectedRows(column);
    QStringList selectedColumns;
    for(int i = 0; i < indexes.count(); ++i){
        QModelIndex index = indexes[i];
        selectedColumns.push_back(index.data().toString());
    }

    return selectedColumns;
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
    qApp->aboutQt();
}

void MainWindow::on_addAction_triggered()
{
    UrlDialog addUrlDialog;
    addUrlDialog.setMessageEcoSystem(_message);
    if(addUrlDialog.exec() == QDialog::Accepted)
        if(!addUrlDialog.urls().isEmpty())
            downloader->addDownloads(addUrlDialog.urls());
}

void MainWindow::on_pauseAction_triggered()
{
    downloader->pauseDownloads(currentColumns());
}

void MainWindow::on_resumeAction_triggered()
{
    downloader->addDownloads(currentColumns());
}

void MainWindow::on_removeAction_triggered()
{
    downloader->removeDownloads(currentColumns(UrlModel::save_path));
}

void MainWindow::on_removeFromListAction_triggered()
{
    QModelIndexList indexes = ui->urlView->selectionModel()->selectedRows();
    foreach(QModelIndex idx, indexes){
        model->removeRow(idx.row());
    }
    submitUrlViewChanges();
}

void MainWindow::on_reportBugAction_triggered()
{
    ReportBugDialog bugDialog;
    bugDialog.exec();
}

void MainWindow::on_aboutyoDownetAction_triggered()
{
   AboutDialog about;
   about.exec();
}

void MainWindow::initUrlsTable()
{
    // FIXME: Move me to the constructor
    ui->urlView->horizontalHeader()->setMovable(true);
    ui->urlView->setModel(model);
    ui->urlView->hideColumn(model->fieldIndex("id"));
    ui->urlView->hideColumn(model->fieldIndex("downloaded_at"));

}

void MainWindow::updateUrlsTable(const Status *status)
{
    bool urlExist = false;
    QAbstractItemModel *updateModel = ui->urlView->model();
    for (int i = 0; i < ui->urlView->model()->rowCount(); ++i) {
        if(updateModel->data(updateModel->index(i, UrlModel::url)).toString() == status->url()){
            updateModel->setData(updateModel->index(i, UrlModel::filename), status->name());
            updateModel->setData(updateModel->index(i, UrlModel::save_path), status->path());
            updateModel->setData(updateModel->index(i, UrlModel::status), status->downloadStatus());
            updateModel->setData(updateModel->index(i, UrlModel::progress), status->progress());
            updateModel->setData(updateModel->index(i, UrlModel::remaining_time), status->remainingTime());
            updateModel->setData(updateModel->index(i, UrlModel::speed), status->downloadRate());
            urlExist = true;
        }
    }
    if(!urlExist){
        ui->urlView->model()->insertRow(ui->urlView->model()->rowCount());
        int row = ui->urlView->model()->rowCount()-1;
        ui->urlView->model()->setData(ui->urlView->model()->index(row, UrlModel::url), status->url());

        _message->addMessage(
                    tr("New Download"),
                    tr("%1 has been successfully added ;)").arg(status->url()),
                    MessageConstants::Success);
        submitUrlViewChanges();
    }
}

void MainWindow::submitUrlViewChanges()
{
    model->submitAll();
}

void MainWindow::onDownloadRemoved(const QString &fileName)
{
    QAbstractItemModel *removeModel = ui->urlView->model();
    for(int i = 0; i < ui->urlView->model()->rowCount(); ++i){
        if(removeModel->data(removeModel->index(i, UrlModel::save_path)).toString() == fileName){
            if(model->removeRow(i)){
                submitUrlViewChanges();
                _message->addMessage(
                            tr("Download removed"),
                            tr("%1 has been successfully removed.").arg(fileName),
                            MessageConstants::Info);
            }
            return;
        }
    }
}

void MainWindow::onDownloadResumed(const Status *status)
{
    _message->addMessage(
                tr("Resume Download"),
                tr("Resuming %1").arg(status->name()),
                MessageConstants::Info);
}

void MainWindow::trayIconTriggered()
{
    if(isHidden()) show(); else hide();
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

    settings.beginGroup("urlView");
    settings.beginGroup("horizontalHeader");
    settings.setValue("state", ui->urlView->horizontalHeader()->saveState());
    settings.setValue("geometry", ui->urlView->horizontalHeader()->saveGeometry());
    settings.endGroup();
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

    settings.beginGroup("urlView");
    settings.beginGroup("horizontalHeader");
    ui->urlView->horizontalHeader()->restoreState(settings.value("state").toByteArray());
    ui->urlView->horizontalHeader()->restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
    settings.endGroup();

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

void MainWindow::prepareTrayIcon()
{
    _trayIcon = new SystemTrayIcon;
    _trayMenu = new QMenu;
    _trayMenu->addAction(ui->addAction);
    _trayMenu->addSeparator();
    _trayMenu->addAction(ui->exitAction);
    _trayIcon->setReady(_trayMenu, windowIcon());

    _message->setSysTrayIcon(_trayIcon);

    connect(_trayIcon, SIGNAL(triggered()), this, SLOT(trayIconTriggered()));
    connect(_trayIcon, SIGNAL(middleClicked()), ui->addAction, SLOT(trigger()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    if(!isHidden()) event->ignore();
    hide();
}
