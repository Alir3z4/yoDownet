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
#include <QSettings>
#include "preferencesdialog.h"
#include "urldialog.h"
#include "aboutdialog.h"
#include "reportbugdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(new yoDataBase(parent)), model(new UrlModel(parent)), downloader(new yoDownet(parent))
{
    ui->setupUi(this);

    loadSettings();
    createActionsOnMainWindow();

    // Initialize urlsTable :|
    initUrlsTable();

    // Connect the signals/slot
    connect(downloader, SIGNAL(downloadInitialed(const Status*)), this, SLOT(addNewDlToUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downlaodResumed(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
    connect(downloader, SIGNAL(downloadUpdated(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    msg.aboutQt(this, tr("yoDownet : About Qt"));
}

void MainWindow::on_actionAdd_triggered()
{
    urlDialog addUrlDialog;
    if(addUrlDialog.exec() == QDialog::Accepted)
        downloader->addDownloads(QStringList(addUrlDialog.url()));
}

void MainWindow::on_actionResume_triggered()

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

void MainWindow::closeEvent(QCloseEvent * )
{
    saveSettings();
}

void MainWindow::initUrlsTable()
{
    ui->urlView->setModel(model);
    ui->urlView->hideColumn(model->fieldIndex("id"));
}

void MainWindow::addNewDlToUrlsTable(const Status *status)
{
    ui->urlView->model()->insertRow(ui->urlView->model()->rowCount());
    int row = ui->urlView->model()->rowCount()-1;
    ui->urlView->model()->setData(ui->urlView->model()->index(row, UrlModel::url), status->url());

    model->submitAll();
}

void MainWindow::updateUrlsTable(const Status *status)
{
    QAbstractItemModel *updateModel = ui->urlView->model();
    for (int i = 0; i < ui->urlView->model()->rowCount(); ++i) {
        if(updateModel->data(updateModel->index(i, UrlModel::url)).toString() == status->url()){
            updateModel->setData(updateModel->index(i, UrlModel::save_path), status->path());
            updateModel->setData(updateModel->index(i, UrlModel::status), status->downloadStatus());
            updateModel->setData(updateModel->index(i, UrlModel::progress), status->progress());
            updateModel->setData(updateModel->index(i, UrlModel::remaining_time), status->remainingTime());
            updateModel->setData(updateModel->index(i, UrlModel::speed), status->downloadRate());
        }
    }
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

