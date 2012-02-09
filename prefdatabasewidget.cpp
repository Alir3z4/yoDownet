/****************************************************************************************
** prefdatabasewidget.cpp is part of yoDownet
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

#include "prefdatabasewidget.h"
#include "ui_prefdatabasewidget.h"

PrefDataBaseWidget::PrefDataBaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDataBaseWidget)
{
    ui->setupUi(this);
}

PrefDataBaseWidget::~PrefDataBaseWidget()
{
    delete ui;
}
