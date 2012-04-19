/****************************************************************************************
** filebrowz.h is part of yoDownet
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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef FileBrowz_H
#define FileBrowz_H

#include <QFileDialog>

namespace Ui {
class FileBrowz;
}

class FileBrowz : public QWidget
{
    Q_OBJECT
    
public:
    enum BrowzType {
        GetFileName,
        GetDirectory
    };

    explicit FileBrowz(QWidget *parent = 0);
    ~FileBrowz();

    const QString caption();
    const QString filter();
    const QString browzPath();
    BrowzType browzType() const;
    const QFileDialog::Options options();

public slots:
    void setCaption(const QString &caption);
    void setFilter(const QString &filter);
    void setBrowzType(BrowzType type);
    void setOptions(QFileDialog::Options options);
    void setBrowzPath(const QString &browztPath);
    void setPath(const QString &path);
    
private slots:
    void on_browzButton_clicked();

signals:
    void fileChanged(const QString &newFile);

private:
    Ui::FileBrowz *ui;
    QString _caption;
    QString _filter;
    BrowzType _type;
    QFileDialog::Options _options;
};

#endif // FileBrowz_H
