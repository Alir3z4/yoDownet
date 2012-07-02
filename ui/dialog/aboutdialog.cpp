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
    ui->descriptionLabel->setText(tr(
                "<b>Version: %1</b>\n"
                "Based on Qt %2\n\n\n"
                "yoDownet, The Previous Generation Graphical Download Manager.\n"
                "yoDownet uses Qt toolkit for both front-end and back-end implementation!\n\n\n"
                "Copyright (C) 2011-2012 by Alireza Savand\nhttp://sourceforge.net/projects/yodownet/\n")
                                 .arg(qApp->applicationVersion())
                                 .arg(qVersion()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
