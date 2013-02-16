/****************************************************************************************
** downloadtablemodel.h is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef DOWNLOADTABLEMODEL_H
#define DOWNLOADTABLEMODEL_H

#include <QAbstractTableModel>
#include "download/download.h"

class DownloadTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DownloadTableModel(QObject *parent = 0);

    enum Downloads {
        Uuid,
        URL,
        SavePath,
        FileName,
        Status,
        Progress,
        RemainingTime,
        Speed,
        Added,
        Downloaded
    };

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

private:
    int const column_count = 10;
    QList<Download*> _downloadList;

    QString downloadStatus(const int status) const;
};

#endif // DOWNLOADTABLEMODEL_H