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
#include <QtSql/QSqlQuery>
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

    // Hide `id`, 'flags' columns
    ui->urlsTable->setColumnHidden(0, true);
    ui->urlsTable->setColumnHidden(yoDataBase::flag, true);

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
    if(!ui->urlsTable->selectedItems().isEmpty())
        return ui->urlsTable->item(ui->urlsTable->selectedItems().first()->row(), column)->text();
    return QString();
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
        QThread *thread = new QThread;
        yoDownet *downloader = new yoDownet;
        db = new yoDataBase(this, downloader);
        downloader->moveToThread(thread);
        downloader->theDownload(addUrlDialog.url());
        // connect these guyz
        connect(downloader, SIGNAL(downloadInitialed(const Status*)), this, SLOT(addNewDlToUrlsTable(const Status*)));
        connect(downloader, SIGNAL(downlaodResumed(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
        connect(downloader, SIGNAL(downloadUpdated(const Status*)), this, SLOT(updateUrlsTable(const Status*)));
        thread->start();
    }

}

void MainWindow::closeEvent(QCloseEvent * )
{
    saveSettings();
}

void MainWindow::initurlsTable()
{
    // initialize the database
    QSqlError sqlError = db->initDb();
    if (sqlError.type() != QSqlError::NoError)
        msg.dbError(sqlError.text(), tr("Unable to initialize Database"));

    // Populate database on urlsTable
    QSqlQuery popQuery;
    // Let's check there isn't any problem to gathering urls from database
    if (!popQuery.exec("SELECT * FROM urls"))
        // seems yes, hell let's user know
        // User face :~/
        msg.dbError(popQuery.lastError().text(), tr("Populating 'urls' table"));
    else {
        // Add newItem to urlsTable;
        while (popQuery.next()) {
            int currentRow = ui->urlsTable->rowCount();
            ui->urlsTable->setRowCount(currentRow + 1);
            // [id]
            QTableWidgetItem *idItem =  new QTableWidgetItem(popQuery.value(yoDataBase::id).toString());
            ui->urlsTable->setItem(currentRow, yoDataBase::id, idItem);
            // ![id]

            // [url] => File name
            QTableWidgetItem *urlItem = new QTableWidgetItem(popQuery.value(yoDataBase::url).toString());
            urlItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::url, urlItem);
            // ![url]

            // [save_path]
            QTableWidgetItem *save_pathItem = new QTableWidgetItem(popQuery.value(yoDataBase::save_path).toString());
            save_pathItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::save_path, save_pathItem);
            // ![save_path]

            // [status]
            QTableWidgetItem *statusItem = new QTableWidgetItem(popQuery.value(yoDataBase::status).toString());
            statusItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::status, statusItem);
            // ![status]

            // [progress]
            QTableWidgetItem *progressItem = new QTableWidgetItem(popQuery.value(yoDataBase::progress).toString() + "%");
            progressItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::progress, progressItem);
            // ![progress]

            // [remaining_time]
            QTableWidgetItem *remaining_timeItem = new QTableWidgetItem(popQuery.value(yoDataBase::remaining_time).toString());
            remaining_timeItem->setTextAlignment(Qt::AlignCenter);
            remaining_timeItem->setFlags(Qt::ItemIsEditable);
            ui->urlsTable->setItem(currentRow, yoDataBase::remaining_time, remaining_timeItem);
            // ![remaining_time]

            // [flag]
            QTableWidgetItem *flagItem = new QTableWidgetItem(popQuery.value(yoDataBase::flag).toString());
            flagItem->setFlags(Qt::ItemIsEditable);
            ui->urlsTable->setItem(currentRow, yoDataBase::flag, flagItem);
            // ![flag]

            // [created_at]
            QTableWidgetItem *created_atItem = new QTableWidgetItem(
                        popQuery.value(yoDataBase::created_at).toDateTime().toLocalTime().toString());
            created_atItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::created_at, created_atItem);
            // ![created_at]

            // [updated_at]
            QTableWidgetItem *updated_atItem = new QTableWidgetItem(
                        popQuery.value(yoDataBase::updated_at).toDateTime().toLocalTime().toString());
            updated_atItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, yoDataBase::updated_at, updated_atItem);
            // ![updated_at]

            // [dlSpeed-9]
            QTableWidgetItem *dlSpeedItem = new QTableWidgetItem(tr("n/a"));
            dlSpeedItem->setTextAlignment(Qt::AlignCenter);
            ui->urlsTable->setItem(currentRow, 9 , dlSpeedItem);
            // ![dlSpeed-9]

        }
    }
}

void MainWindow::addNewDlToUrlsTable(const Status *status)
{

    int currentRow = ui->urlsTable->rowCount();
    ui->urlsTable->setRowCount(currentRow + 1);
    // [id]
    QTableWidgetItem *idItem =  new QTableWidgetItem(QString::number(0));
    ui->urlsTable->setItem(currentRow, yoDataBase::id, idItem);
    // ![id]

    // [url] => File name
    QTableWidgetItem *urlItem = new QTableWidgetItem(status->url());
    urlItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::url, urlItem);
    // ![url]

    // [save_path]
    QTableWidgetItem *save_pathItem = new QTableWidgetItem(status->path());
    save_pathItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::save_path, save_pathItem);
    // ![save_path]

    // [status]
    QTableWidgetItem *statusItem = new QTableWidgetItem(status->downloadStatusString());
    statusItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::status, statusItem);
    // ![status]

    // [progress]
    QTableWidgetItem *progressItem = new QTableWidgetItem(status->progress());
    progressItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::progress, progressItem);
    // ![progress]

    // [flag]
    QTableWidgetItem *flagItem = new QTableWidgetItem("init");
    progressItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::flag, flagItem);
    // ![flag]

    // [remaining_time]
    QTableWidgetItem *remaining_timeItem = new QTableWidgetItem(tr("n/a"));
    remaining_timeItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::remaining_time, remaining_timeItem);
    // ![remaining_time]

    // [created_at]
    QTableWidgetItem *created_atItem = new QTableWidgetItem(QDateTime::currentDateTime().toLocalTime().toString());
    created_atItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, yoDataBase::created_at, created_atItem);
    // ![created_at]

    // [updated_at]
    QTableWidgetItem *updated_atItem = new QTableWidgetItem(" ");
    ui->urlsTable->setItem(currentRow, yoDataBase::updated_at, updated_atItem);
    // ![updated_at]

    // [dlSpeed-9]
    QTableWidgetItem *dlSpeedItem = new QTableWidgetItem(tr("n/a"));
    dlSpeedItem->setTextAlignment(Qt::AlignCenter);
    ui->urlsTable->setItem(currentRow, 9 , dlSpeedItem);
    // ![dlSpeed-9]
}

void MainWindow::updateUrlsTable(const Status *status)
{
    for (int i = 0; i < ui->urlsTable->rowCount(); ++i) {
        if(ui->urlsTable->item(i, yoDataBase::url)->text() == status->url()){
            ui->urlsTable->item(i, yoDataBase::status)->setText(status->downloadStatusString());
            ui->urlsTable->item(i, yoDataBase::progress)->setText(QString("%1 %").arg(QString::number(status->progress())));
            ui->urlsTable->item(i, yoDataBase::remaining_time)->setText(status->remainingTime());
            ui->urlsTable->item(i, 9)->setText(status->downloadRate());

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

void MainWindow::on_actionResume_triggered()
{
    if(ui->urlsTable->selectedItems().isEmpty())
        return;
//    downloader->theDownload(currentColumn(yoDataBase::url));
}
