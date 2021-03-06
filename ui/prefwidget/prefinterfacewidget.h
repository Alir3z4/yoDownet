/****************************************************************************************
** prefinterfacewidget.h is part of yoDownet
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

#ifndef PREFINTERFACEWIDGET_H
#define PREFINTERFACEWIDGET_H

#include <QWidget>

namespace Ui {
class PrefInterfaceWidget;
}

class PrefInterfaceWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrefInterfaceWidget(QWidget *parent = 0);
    ~PrefInterfaceWidget();

    QString selectedLanguage() const;
    int languageComboBoxCurrentIndex() const;
    void setLanguageComboBoxCurrentIndex(const int &currentIndex);

private:
    Ui::PrefInterfaceWidget *ui;

    void createLanguageComboBox();


};

#endif // PREFINTERFACEWIDGET_H
