/****************************************************************************************
** preferencesdialog.cpp  is part of yoDownet
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

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QSettings>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    // Setup buttons
    okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    applyButton = ui->buttonBox->button(QDialogButtonBox::Apply);

    // Setup widgets
    prefDler = new PrefDownloadersWidget;
    addSection(prefDler);

    prefDb = new PrefDataBaseWidget;
    addSection(prefDb);

    // Connecting Signal/Slot
    connect(applyButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

    // Let's load the settings
    loadSettings();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::addSection(QWidget *w)
{
    QListWidgetItem *i = new QListWidgetItem(w->windowIcon(), w->windowTitle());
    ui->sectionListWidget->addItem(i);
    ui->pages->addWidget(w);
}

void PreferencesDialog::saveSettings()
{
    QSettings settings;

    // Save PreferencesDialog settings
    settings.beginGroup("PreferencesDialog");


    // Save PrefDownloadersWidget
    settings.beginGroup("PrefDownloadersWidget");
    settings.setValue("saveDir", prefDler->saveDir());
    settings.setValue("log", prefDler->logFile());
    settings.setValue("max-concurrent-downloads", prefDler->maxDownloads());
    settings.setValue("continue", prefDler->isContinue());
    settings.endGroup();

    settings.endGroup();

}

void PreferencesDialog::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.beginGroup("PreferencesDialog");
    settings.setValue("pos", pos());
    settings.setValue("geometry", geometry());
    settings.setValue("fullScreen", isFullScreen());
    settings.setValue("currentRow", ui->sectionListWidget->currentRow());
    settings.endGroup();
}

void PreferencesDialog::loadSettings()
{
    QSettings settings;

    // Save PreferencesDialog settings
    settings.beginGroup("PreferencesDialog");
    move(settings.value("pos", QPoint(62, 341)).toPoint());
    setGeometry(settings.value("geometry", QRect(64, 364, 643, 425)).toRect());
    if(settings.value("fullscreen").toBool())
        showFullScreen();
    ui->sectionListWidget->setCurrentRow(settings.value("currentRow", -1).toInt());

    // Load PrefDownloadersWidget
    settings.beginGroup("PrefDownloadersWidget");
    prefDler->setSaveDir(settings.value("saveDir").toString());
    prefDler->setLogFile(settings.value("log", "").toString());
    prefDler->setMaxDownloads(settings.value("max-concurrent-downloads", 5).toInt());
    prefDler->setContinue(settings.value("continue", "true").toBool());
    settings.endGroup();

    settings.endGroup();
}

void PreferencesDialog::on_buttonBox_accepted()
{
    saveSettings();
}
