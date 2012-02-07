#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preferencesdialog.h"
#include "yoUtils/yomessage.h"
#include "importurls.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // read/load settings
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_importUrlsAction_triggered()
{
    ImportUrls impUrls;
    if(impUrls.exec() == QDialog::Accepted){
        //TODO: add batch urls to yoDownet

void MainWindow::closeEvent(QCloseEvent * )
{
    saveSettings();
}
    }
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
