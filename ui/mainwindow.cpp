/****************************************************************************************
** mainwindow.cpp is part of yoDownet
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/dialog/preferencesdialog.h"
#include "ui/dialog/urldialog.h"
#include "ui/dialog/aboutdialog.h"
#include "ui/dialog/reportbugdialog.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), model(new DownloadTableModel(parent)),
    downloader(new yoDownet(parent)), _message(new Message(parent)), _logger(new LogMe(this))
{
    _logger->info("Initializing MainWindow");

    ui->setupUi(this);

    createActionsOnMainWindow();

    initUrlsTable();
    loadSettings();

    connect(downloader, SIGNAL(downloadInitialed(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(downloader, SIGNAL(downloadPaused(const Download*)), this, SLOT(submitUrlViewChanges()));
    connect(downloader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(downloader, SIGNAL(downlaodResumed(const Download*)), this, SLOT(onDownloadResumed(const Download*)));
    connect(downloader, SIGNAL(downloadUpdated(const Download*)), this, SLOT(updateUrlsTable(const Download*)));
    connect(downloader, SIGNAL(downloadRemoved(QString)), this, SLOT(onDownloadRemoved(QString)));
    connect(downloader, SIGNAL(downloadDoesNotExistToRemove(QUuid)), this, SLOT(onDownloadDoesNotExistToRemove(QUuid)));
    connect(this, SIGNAL(downloadRemoved(QString)), this, SLOT(onDownloadRemoved(QString)));

    connect(ui->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    prepareTrayIcon();
}

MainWindow::~MainWindow()
{
    _logger->info("Destroying main window resources");
    _logger->info("Memory you're free now, free!");

    delete ui;
    delete model;
    delete downloader;
    delete _trayIcon;
    delete _trayMenu;
    delete _logger;
}

QStringList MainWindow::currentColumns(const int &column) const
{
    QModelIndexList indexes = ui->urlView->selectionModel()->selectedRows(column);
    QStringList selectedColumns;

    for (int i = 0; i < indexes.count(); ++i) {
        QModelIndex index = indexes[i];
        selectedColumns.push_back(index.data().toString());
    }

    return selectedColumns;
}

void MainWindow::on_preferencesAction_triggered()
{
    PreferencesDialog prefDialog(this);
    prefDialog.exec();
}

void MainWindow::on_aboutQtAction_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_addAction_triggered()
{
    UrlDialog addUrlDialog;
    addUrlDialog.setMessageEcoSystem(_message);

    if (addUrlDialog.exec() == QDialog::Accepted) {
        if (!addUrlDialog.urls().isEmpty()) {
            QStringList urls = addUrlDialog.urls();
            for (int i = 0; i < urls.size(); ++i) {
                downloader->addDownload(urls[i]);
            }
        }
    }
}

void MainWindow::on_pauseAction_triggered()
{
    QStringList urls = this->currentColumns();
    if(urls.isEmpty()) {
        return;
    }

    for (int i = 0; i < urls.size(); ++i) {
        downloader->pauseDownload(QUuid(urls[i]));
    }
}

void MainWindow::on_resumeAction_triggered()
{
    QStringList urls = this->currentColumns();

    if (urls.isEmpty()) {
        return;
    }

    for (int i = 0; i < urls.size(); ++i) {
        downloader->addDownload(urls[i]);
    }
}

void MainWindow::on_removeAction_triggered()
{
    QStringList uuids = this->currentColumns(DownloadConstants::Attributes::Uuid);
    if (uuids.isEmpty()) {
        return;
    }

    for (int i = 0; i < uuids.size(); ++i) {
        downloader->removeDownload(QUuid(uuids[i]));
    }
}

void MainWindow::on_removeFromListAction_triggered()
{
    QModelIndexList indexes = ui->urlView->selectionModel()->selectedRows();

    foreach (QModelIndex idx, indexes) {
        model->removeRow(idx.row());
    }

    submitUrlViewChanges();
}

void MainWindow::on_reportBugAction_triggered()
{
    ReportBugDialog bugDialog(this);
    bugDialog.exec();
}

void MainWindow::on_aboutyoDownetAction_triggered()
{
   AboutDialog about(this);
   about.exec();
}

void MainWindow::initUrlsTable()
{
    // FIXME: Move me to the constructor
//    ui->urlView->horizontalHeader()->setMovable(true);
    ui->urlView->setModel(model);
    ui->urlView->hideColumn(DownloadConstants::Attributes::Uuid);
}

void MainWindow::updateUrlsTable(const Download *download)
{
    bool urlExist = false;
    QAbstractItemModel *updateModel = ui->urlView->model();

    for (int i = 0; i < ui->urlView->model()->rowCount(); ++i) {
        if (updateModel->data(updateModel->index(i, DownloadConstants::Attributes::URL)).toString() == download->url().toString()) {
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::Uuid), download->uuid());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::FileName), download->name());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::SavePath), download->path());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::Status), download->status()->downloadStatus());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::Progress), download->status()->progress());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::RemainingTime), download->status()->remainingTime());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::Speed), download->status()->downloadRate());
            updateModel->setData(updateModel->index(i, DownloadConstants::Attributes::Added), download->created());
            urlExist = true;
        }
    }

    if (!urlExist) {
        ui->urlView->model()->insertRow(ui->urlView->model()->rowCount());
        int row = ui->urlView->model()->rowCount()-1;
        ui->urlView->model()->setData(ui->urlView->model()->index(row, DownloadConstants::Attributes::URL), download->url());

        _message->addMessage(
                    tr("New Download"),
                    tr("%1 has been successfully added ;)").arg(download->url().toString()),
                    MessageConstants::Success);
        submitUrlViewChanges();
    }
}

void MainWindow::submitUrlViewChanges()
{
//    model->submitAll();
    return;
}

void MainWindow::onDownloadRemoved(const QString &fileName)
{
    QAbstractItemModel *removeModel = ui->urlView->model();

    for (int i = 0; i < ui->urlView->model()->rowCount(); ++i) {
        if (removeModel->data(removeModel->index(i, DownloadConstants::Attributes::SavePath)).toString() == fileName) {
            if (model->removeRow(i)) {
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

void MainWindow::onDownloadResumed(const Download *download)
{
    _message->addMessage(
                tr("Resume Download"),
                tr("Resuming %1").arg(download->name()),
                MessageConstants::Info);
}

void MainWindow::onDownloadDoesNotExistToRemove(const QUuid &uuid)
{
    for (int row = 0; row < ui->urlView->model()->rowCount(); ++row) {
        QModelIndex index = ui->urlView->model()->index(row, DownloadConstants::Attributes::Uuid);
        if (index.data().toUuid() == uuid) {
            QString savePath = ui->urlView->model()->index(row, DownloadConstants::Attributes::SavePath).data().toString();
            QString fileName = ui->urlView->model()->index(row, DownloadConstants::Attributes::FileName).data().toString();
            QString filePath = QString("%1%2%3").arg(savePath, QDir::toNativeSeparators("/"), fileName);

            QFile file(filePath);
            if (!file.remove()) {
                _logger->error(file.errorString());
                return;
            }
            emit this->downloadRemoved(fileName);
        }

        if (ui->urlView->model()->data(ui->urlView->model()->index(row, DownloadConstants::Attributes::Uuid)).toUuid() == uuid) {
        }
    }
}
void MainWindow::trayIconTriggered()
{
    if (isHidden()) {
        _logger->info("Showing MainWindow");
        show();
    } else {
        _logger->info("Hiding MainWindow");
        hide();
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::createActionsOnMainWindow()
{
    addActions(ui->menubar->actions());
}

void MainWindow::saveSettings()
{
    _logger->info("Saving settings");

    QSettings settings;
    settings.beginGroup("MainWindow");

    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("geometry", geometry());
    settings.setValue("fullScreen", isFullScreen());
    settings.setValue("state", saveState());

    settings.beginGroup("menubar");
    settings.setValue("isHidden", ui->menubar->isHidden());
    settings.endGroup();

    settings.beginGroup("urlView");
    settings.setValue("downloadHash", this->downloadHash());
    settings.beginGroup("horizontalHeader");
    settings.setValue("state", ui->urlView->horizontalHeader()->saveState());
    settings.setValue("geometry", ui->urlView->horizontalHeader()->saveGeometry());
    settings.endGroup();
    settings.endGroup();

    settings.beginGroup("statusbar");
    settings.setValue("isHidden", ui->statusbar->isHidden());
    settings.endGroup();

    settings.beginGroup("toolbar");
    settings.setValue("isHidden", ui->toolbar->isHidden());
    settings.setValue("geometry", ui->toolbar->geometry());
    settings.endGroup();

    settings.beginGroup("showMenubarAction");
    settings.setValue("isChecked", ui->showMenubarAction->isChecked());
    settings.setValue("shortcut", ui->showMenubarAction->shortcut());
    settings.endGroup();

    settings.beginGroup("showToolbarAction");
    settings.setValue("isChecked", ui->showToolbarAction->isChecked());
    settings.setValue("shortcut", ui->showToolbarAction->shortcut());
    settings.endGroup();

    settings.beginGroup("showStatusbarAction");
    settings.setValue("isChecked", ui->showStatusbarAction->isChecked());
    settings.setValue("shortcut", ui->showStatusbarAction->shortcut());
    settings.endGroup();

    settings.endGroup();

    _logger->info("Settings saved");
}

void MainWindow::loadSettings()
{
    _logger->info("Loading settings");

    QSettings settings;
    settings.beginGroup("MainWindow");
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    resize(settings.value("size", QSize(400, 400)).toSize());
    setGeometry(settings.value("geometry", QRect(49, 331, 670, 445)).toRect());
    if(settings.value("fullscreen").toBool())
        showFullScreen();
    restoreState(settings.value("state", QByteArray()).toByteArray());

    settings.beginGroup("urlView");
    this->populateUrlView(settings.value("downloadHash"));
    settings.beginGroup("horizontalHeader");
    ui->urlView->horizontalHeader()->restoreState(settings.value("state").toByteArray());
    ui->urlView->horizontalHeader()->restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
    settings.endGroup();

    settings.beginGroup("menubar");
    ui->menubar->setHidden(settings.value("isHidden", false).toBool());
    settings.endGroup();

    settings.beginGroup("statusbar");
    ui->statusbar->setHidden(settings.value("isHidden", false).toBool());
    settings.endGroup();

    settings.beginGroup("toolbar");
    ui->toolbar->setHidden(settings.value("isHidden", false).toBool());
    ui->toolbar->setGeometry(settings.value("geometry").toRect());
    settings.endGroup();

    settings.beginGroup("showMenubarAction");
    ui->showMenubarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showMenubarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showMenubarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.beginGroup("showToolbarAction");
    ui->showToolbarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showToolbarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showToolbarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.beginGroup("showStatusbarAction");
    ui->showStatusbarAction->setChecked(settings.value("isChecked", true).toBool());
    ui->showStatusbarAction->setShortcut(
                QKeySequence(settings.value("shortcut", ui->showStatusbarAction->shortcut().toString()).toString()));
    settings.endGroup();

    settings.endGroup();

    _logger->success("Settings loaded");
}

void MainWindow::prepareTrayIcon()
{
    _logger->info("Preparing system tray icon");

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
    if (!isHidden()) {
        event->ignore();
    }
    hide();
}

QHash<QString, QVariant> MainWindow::downloadHash() const
{
    _logger->info("Getting downloadHash");

    QHash<QString, QVariant> dlHash;

    for (int i = 0; i < ui->urlView->model()->rowCount(); ++i) {
        QHash<QString, QVariant> downloadAttributeHash;
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::URL),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::URL))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::FileName),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::FileName))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::SavePath),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::SavePath))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::Status),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::Status))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::Progress),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::Progress))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::RemainingTime),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::RemainingTime))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::Speed),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::Speed))
        );
        downloadAttributeHash.insert(
                    QString::number(DownloadConstants::Attributes::Added),
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::Added))
        );

        dlHash.insert(
                    ui->urlView->model()->data(ui->urlView->model()->index(i, DownloadConstants::Attributes::Uuid)).toString(),
                    QVariant::fromValue(downloadAttributeHash)
        );
    }

    _logger->info("downloadHash populated");

    return dlHash;
}

void MainWindow::populateUrlView(const QVariant downloadVariant)
{
    QHash<QString, QVariant> dlHash = downloadVariant.toHash();
    QHashIterator<QString, QVariant> i(dlHash);
    while (i.hasNext()) {
        i.next();
        QHash<QString, QVariant> downloadAttributeHash = i.value().toHash();
        ui->urlView->model()->insertRow(ui->urlView->model()->rowCount());
        int row = ui->urlView->model()->rowCount() - 1;
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::Uuid),
                    i.key()
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::URL),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::URL))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::FileName),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::FileName))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::SavePath),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::SavePath))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::Status),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::Status))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::Progress),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::Progress))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::RemainingTime),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::RemainingTime))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::Speed),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::Speed))
        );
        ui->urlView->model()->setData(
                    ui->urlView->model()->index(row, DownloadConstants::Attributes::Added),
                    downloadAttributeHash.value(QString::number(DownloadConstants::Attributes::Added))
        );
    }

}
