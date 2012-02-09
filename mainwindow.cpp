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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QSettings>
#include "yoDownloaders/aria2c.h"
#include "preferencesdialog.h"
#include "uridialog.h"

class QDateTime;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    downloader = new Downloader;
    downloader->askForStartAria();

    _settings = new yoSettings(this);

    // read/load settings
    loadSettings();

    // Add actions from manuBar to MainWindow
    createActionsOnMainWindow();

    // Initialize UrisTable :|
    initUrisTable();

    // Hide `id`, `aria2_gid', 'flags' columns
    ui->urisTable->setColumnHidden(0, true);
    ui->urisTable->setColumnHidden(1, true);
    ui->urisTable->setColumnHidden(yoDataBase::flag, true);

    // So connect the signals :|
    // YuHaHaHaHa
    connect(this, SIGNAL(rowRemoved(QString)), this, SLOT(downloadRemoved(QString)));
    connect(this, SIGNAL(rowStopped(QString)), this, SLOT(downloadStopped(QString)));
    connect(this, SIGNAL(rowUnPaused(QString)), this, SLOT(downloadUnPaused(QString)));
    connect(this, SIGNAL(rowPaused(QString)), this, SLOT(downloadPaused(QString)));
    QTimer *updateTableTimer = new QTimer(this);
    connect(updateTableTimer, SIGNAL(timeout()), this, SLOT(askForUpdateUrisTable()));
    connect(downloader, SIGNAL(uriAddedToDb(QVariantMap)), this, SLOT(addNewDlToUrisTable(QVariantMap)));
    connect(downloader, SIGNAL(statusRefreshed(const Status*)), this, SLOT(updateUrisTable(const Status*)));
    updateTableTimer->start(100);

}

MainWindow::~MainWindow()
{
    delete downloader;
    delete ui;
}

QString MainWindow::currentColumn(const int column) const
{
    if(!ui->urisTable->selectedItems().isEmpty())
        return ui->urisTable->item(ui->urisTable->selectedItems().first()->row(), column)->text();
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
  UriDialog addDialog;
    if(addDialog.exec() == QDialog::Accepted) {
        QVariantMap options = _settings->aria2Options();
        QVariantList uris;
        uris.push_back(addDialog.uri());
        downloader->addUri(uris, options);
    }

}

void MainWindow::closeEvent(QCloseEvent * )
{
    saveSettings();
}

void MainWindow::askForUpdateUrisTable()
{
    for (int i = 0; i < ui->urisTable->rowCount(); ++i){
        if(ui->urisTable->item(i, yoDataBase::status)->text() == "active"){
            QString gid = ui->urisTable->item(i, yoDataBase::aria2_gid)->text();
            if(gid.operator !=("0")){
                downloader->askForRefreshStatus(gid);
                ui->urisTable->item(i, yoDataBase::flag)->setText("askedToRefresh");
            }
        }
    }
}

void MainWindow::updateUrisTable(const Status *status)
{
    for (int i = 0; i < ui->urisTable->rowCount(); ++i) {
        if(ui->urisTable->item(i, yoDataBase::aria2_gid)->text() == status->gid() &&
                ui->urisTable->item(i, yoDataBase::flag)->text() == "askedToRefresh"){
            ui->urisTable->item(i, yoDataBase::progress)->setText(QString::number(status->progress()) + "%");
            ui->urisTable->item(i, yoDataBase::remaining_time)->setText(status->remainingTime());
            ui->urisTable->item(i, yoDataBase::remaining_time)->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->item(i, yoDataBase::status)->setText(status->status());
            ui->urisTable->item(i, 10)->setText(status->downloadRate());
            ui->urisTable->item(i, 10)->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->item(i, yoDataBase::flag)->setText("statusRefreshed");
        }
    }
}

void MainWindow::initUrisTable()
{
    // initialize the database
    QSqlError sqlError = db->initDb();
    if (sqlError.type() != QSqlError::NoError)
        msg.dbError(sqlError.text(), tr("Unable to initialize Database"));

    // Populate database on urisTable
    QSqlQuery popQuery;
    // Let's check there isn't any problem to gathering uris from database
    if (!popQuery.exec("SELECT * FROM uris"))
        // seems yes, hell let's user know
        // User face :~/
        msg.dbError(popQuery.lastError().text(), tr("Populating 'uris' table"));
    else {
        // Add newItem to urisTable;
        while (popQuery.next()) {
            int currentRow = ui->urisTable->rowCount();
            ui->urisTable->setRowCount(currentRow + 1);
            // [id]
            QTableWidgetItem *idItem =  new QTableWidgetItem(popQuery.value(yoDataBase::id).toString());
            ui->urisTable->setItem(currentRow, yoDataBase::id, idItem);
            // ![id]

            // [aria2_gid]
            QTableWidgetItem *aria2_gidItem = new QTableWidgetItem("0");
            ui->urisTable->setItem(currentRow, yoDataBase::aria2_gid, aria2_gidItem);
            // ![aria2_gid]

            // [uri] => File name
            QTableWidgetItem *uriItem = new QTableWidgetItem(popQuery.value(yoDataBase::uri).toString());
            uriItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::uri, uriItem);
            // ![uri]

            // [save_path]
            QTableWidgetItem *save_pathItem = new QTableWidgetItem(popQuery.value(yoDataBase::save_path).toString());
            save_pathItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::save_path, save_pathItem);
            // ![save_path]

            // [status]
            QTableWidgetItem *statusItem = new QTableWidgetItem(popQuery.value(yoDataBase::status).toString());
            statusItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::status, statusItem);
            // ![status]

            // [progress]
            QTableWidgetItem *progressItem = new QTableWidgetItem(popQuery.value(yoDataBase::progress).toString() + "%");
            progressItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::progress, progressItem);
            // ![progress]

            // [remaining_time]
            QTableWidgetItem *remaining_timeItem = new QTableWidgetItem(popQuery.value(yoDataBase::remaining_time).toString());
            remaining_timeItem->setTextAlignment(Qt::AlignCenter);
            remaining_timeItem->setFlags(Qt::ItemIsEditable);
            ui->urisTable->setItem(currentRow, yoDataBase::remaining_time, remaining_timeItem);
            // ![remaining_time]

            // [flag]
            QTableWidgetItem *flagItem = new QTableWidgetItem(popQuery.value(yoDataBase::flag).toString());
            flagItem->setFlags(Qt::ItemIsEditable);
            ui->urisTable->setItem(currentRow, yoDataBase::flag, flagItem);
            // ![flag]

            // [created_at]
            QTableWidgetItem *created_atItem = new QTableWidgetItem(
                        popQuery.value(yoDataBase::created_at).toDateTime().toLocalTime().toString());
            created_atItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::created_at, created_atItem);
            // ![created_at]

            // [updated_at]
            QTableWidgetItem *updated_atItem = new QTableWidgetItem(
                        popQuery.value(yoDataBase::updated_at).toDateTime().toLocalTime().toString());
            updated_atItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, yoDataBase::updated_at, updated_atItem);
            // ![updated_at]

            // [dlSpeed-10]
            QTableWidgetItem *dlSpeedItem = new QTableWidgetItem(tr("n/a"));
            dlSpeedItem->setTextAlignment(Qt::AlignCenter);
            ui->urisTable->setItem(currentRow, 10 , dlSpeedItem);
            // ![dlSpeed-10]

        }
    }
}

void MainWindow::addNewDlToUrisTable(const QVariantMap &uri)
{
     qWarning("added");
     int currentRow = ui->urisTable->rowCount();
     ui->urisTable->setRowCount(currentRow + 1);
    // [id]
    QTableWidgetItem *idItem =  new QTableWidgetItem(uri["id"].toString());
    ui->urisTable->setItem(currentRow, yoDataBase::id, idItem);
    // ![id]

    // [aria2_gid]
    QTableWidgetItem *aria2_gidItem = new QTableWidgetItem(uri["gid"].toString());
    ui->urisTable->setItem(currentRow, yoDataBase::aria2_gid, aria2_gidItem);
    // ![aria2_gid]

    // [uri] => File name
    QTableWidgetItem *uriItem = new QTableWidgetItem(uri["uri"].toString());
    uriItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::uri, uriItem);
    // ![uri]

    // [save_path]
    QTableWidgetItem *save_pathItem = new QTableWidgetItem(uri["dir"].toString());
    save_pathItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::save_path, save_pathItem);
    // ![save_path]

    // [status]
    QTableWidgetItem *statusItem = new QTableWidgetItem(uri["status"].toString());
    statusItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::status, statusItem);
    // ![status]

    // [progress]
    QTableWidgetItem *progressItem = new QTableWidgetItem(uri["progress"].toString());
    progressItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::progress, progressItem);
    // ![progress]

    // [flag]
    QTableWidgetItem *flagItem = new QTableWidgetItem("init");
    ui->urisTable->setItem(currentRow, yoDataBase::flag, flagItem);
    // ![flag]

    // [remaining_time]
    QTableWidgetItem *remaining_timeItem = new QTableWidgetItem(tr("n/a"));
    ui->urisTable->setItem(currentRow, yoDataBase::remaining_time, remaining_timeItem);
    // ![remaining_time]

    // [created_at]
    QTableWidgetItem *created_atItem = new QTableWidgetItem(QDateTime::currentDateTime().toLocalTime().toString());
    created_atItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::created_at, created_atItem);
    // ![created_at]

    // [updated_at]
    QTableWidgetItem *updated_atItem = new QTableWidgetItem(
                uri["updated_at"].toDateTime().toLocalTime().toString());
    updated_atItem->setTextAlignment(Qt::AlignCenter);
    ui->urisTable->setItem(currentRow, yoDataBase::updated_at, updated_atItem);
    // ![updated_at]

    // [dlSpeed-10]
    QTableWidgetItem *dlSpeedItem = new QTableWidgetItem(tr("n/a"));
    ui->urisTable->setItem(currentRow, 10 , dlSpeedItem);
    // ![dlSpeed-10]
}

void MainWindow::downloadPaused(const QString &uri)
{
    qDebug() << QString(tr("Download with #URI=>'%1' paused.").arg(uri));
}

void MainWindow::downloadUnPaused(const QString &uri)
{
    qDebug() << QString(tr("Download with #URI=>'%1' unpaused and will resumed.").arg(uri));
}

void MainWindow::downloadRemoved(const QString &uri)
{
    if(db->deleteUri(uri))
        qDebug() << QString(tr("Download with #URI=>'%1' removed.").arg(uri));
    else
        qDebug() << QString(tr("What da ? something's not right!"));
}

void MainWindow::downloadStopped(const QString &uri)
{
    qDebug() << QString(tr("Download with #URI=>'%1' stopped.").arg(uri));
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

void MainWindow::on_actionRemove_triggered()
{
    const QString uri = currentColumn(yoDataBase::uri);
    const QString gid = currentColumn(yoDataBase::aria2_gid);

    if(!ui->urisTable->selectedItems().isEmpty())
        ui->urisTable->removeRow(ui->urisTable->selectedItems().first()->row());
    else
        return;
    if(gid != "0")
        downloader->remove(QVariant(gid));
    emit downloadRemoved(uri);
}

void MainWindow::on_actionStop_triggered()
{
    const QString uri = currentColumn(yoDataBase::uri);
    const QString gid = currentColumn(yoDataBase::aria2_gid);

    if(!ui->urisTable->selectedItems().isEmpty())
        ui->urisTable->removeRow(ui->urisTable->selectedItems().first()->row());
    else
        return;
    if(gid != "0")
        downloader->stop(QVariant(gid));
    emit downloadStopped(uri);
}

void MainWindow::on_actionPause_triggered()
{
    const QString uri = currentColumn(yoDataBase::uri);
    const QString gid = currentColumn(yoDataBase::aria2_gid);

    if(!ui->urisTable->selectedItems().isEmpty())
        ui->urisTable->removeRow(ui->urisTable->selectedItems().first()->row());
    else
        return;
    if(gid != "0")
        downloader->pause(QVariant(gid));
    emit downloadPaused(uri);
}

void MainWindow::on_actionResume_triggered()
{
    const QString uri = currentColumn(yoDataBase::uri);
    const QString gid = currentColumn(yoDataBase::aria2_gid);

    if(!ui->urisTable->selectedItems().isEmpty())
        ui->urisTable->removeRow(ui->urisTable->selectedItems().first()->row());
    else
        return;
    if(gid != "0")
        downloader->unpause(QVariant(gid));
    emit downloadUnPaused(uri);
}

void MainWindow::on_actionResumeAll_triggered()
{

    for (int i = 0; i < ui->urisTable->rowCount(); ++i){
        QString status = ui->urisTable->item(i, yoDataBase::status)->text();
        QString uri = ui->urisTable->item(i, yoDataBase::uri)->text();
        if(status == "paused"){
            QString gid = ui->urisTable->item(i, yoDataBase::aria2_gid)->text();
            if(gid != "0"){
                downloader->unpause(gid);
            }else if(gid == "0"){
                downloader->resume(uri);
                emit downloadUnPaused(uri);
            }
        }
    }

    downloader->unpauseAll();
}
