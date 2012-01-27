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
    }
}
