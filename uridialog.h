/****************************************************************************************
** uridialog.h is part of yoDownet
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

#ifndef URIDIALOG_H
#define URIDIALOG_H

#include <QDialog>
#include <QVariantList>

namespace Ui {
class UriDialog;
}

class UriDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UriDialog(QWidget *parent = 0);
    ~UriDialog();

    const QString uri();
    
private slots:
    void on_uriEdit_textChanged();

    void on_uriEdit_returnPressed();

private:
    Ui::UriDialog *ui;
};

#endif // URIDIALOG_H
