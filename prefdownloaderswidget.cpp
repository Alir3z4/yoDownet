/****************************************************************************************
** prefdownloaderswidget.cpp is part of yoDownet
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

#include "prefdownloaderswidget.h"
#include "ui_prefdownloaderswidget.h"

PrefDownloadersWidget::PrefDownloadersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDownloadersWidget)
{
    ui->setupUi(this);

    ui->saveDirEdit->setCaption(tr("Select a directory to save downloaded files"));
    ui->saveDirEdit->setBrowzType(FileBrowz::GetDirectory);

    ui->logFileEdit->setCaption(tr("Select a file to write log file into it"));
    ui->logFileEdit->setBrowzType(FileBrowz::GetFileName);
    ui->logFileEdit->setBrowzPath(QString());
}

PrefDownloadersWidget::~PrefDownloadersWidget()
{
    delete ui;
}

QString PrefDownloadersWidget::saveDir()const
{
    return ui->saveDirEdit->browzPath();
}

QString PrefDownloadersWidget::logFile() const
{
    return ui->logFileEdit->browzPath();
}

int PrefDownloadersWidget::maxDownloads() const
{
    return ui->maxDownloadSpinBox->text().toInt();
}

bool PrefDownloadersWidget::isContinue() const
{
    return ui->continueCheckBox->isChecked();
}

void PrefDownloadersWidget::setSaveDir(const QString &saveDir)
{
    ui->saveDirEdit->setBrowzPath(saveDir);
}

void PrefDownloadersWidget::setLogFile(const QString &logFile)
{
    ui->logFileEdit->setPath(logFile);
}

void PrefDownloadersWidget::setMaxDownloads(const int maxDownloads)
{
    ui->maxDownloadSpinBox->setValue(maxDownloads);
}

void PrefDownloadersWidget::setContinue(bool isContinue)
{
    ui->continueCheckBox->setChecked(isContinue);
}
