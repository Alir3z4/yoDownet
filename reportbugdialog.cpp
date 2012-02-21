/****************************************************************************************
** reportbugdialog.cpp is part of yoDownet
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

#include "reportbugdialog.h"
#include "ui_reportbugdialog.h"
#include <QDesktopServices>
#include <QUrl>

ReportBugDialog::ReportBugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportBugDialog)
{
    ui->setupUi(this);
}

ReportBugDialog::~ReportBugDialog()
{
    delete ui;
}

void ReportBugDialog::on_submitButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://sourceforge.net/p/yodownet/tickets/new/"));
}
