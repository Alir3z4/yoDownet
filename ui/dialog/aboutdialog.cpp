/****************************************************************************************
** aboutdialog.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "util/paths.h"
#include <QFile>
#include <QTextStream>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QFile licenseFile(Paths::docPath() + "/COPYING");
    licenseFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&licenseFile);

    ui->licenseTextEdit->setPlainText(in.readAll());

    ui->versionLabel->setText(tr("Version %1").arg(qApp->applicationVersion()));
    ui->qtVersionLabel->setText(tr("Based on Qt %1").arg(qVersion()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
