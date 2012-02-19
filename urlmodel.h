/****************************************************************************************
** urlmodel.h is part of yoDownet
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

#ifndef URLMODEL_H
#define URLMODEL_H

#include <QSqlTableModel>

class UrlModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit UrlModel(QObject *parent = 0);

    enum Urls {
        id,
        url,
        save_path,
        status,
        progress,
        remaining_time,
        speed,
        created_at,
        updated_at
    };

    QVariant data(const QModelIndex &idx, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QString downloadStatus(const int status) const;
    
};

#endif // URLMODEL_H
