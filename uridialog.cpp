/****************************************************************************************
** uridialog.cpp is part of yoDownet
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

#include "uridialog.h"
#include "ui_uridialog.h"

UriDialog::UriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UriDialog)
{
    ui->setupUi(this);
}

UriDialog::~UriDialog()
{
    delete ui;
}

const QString UriDialog::uri()
{
    return ui->uriEdit->text();
}

void UriDialog::on_uriEdit_textChanged()
{
    if(!ui->uriEdit->text().isEmpty())
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setDisabled(true);
}

void UriDialog::on_uriEdit_returnPressed()
{
    if(ui->buttonBox->isEnabled())
        accepted();
}
