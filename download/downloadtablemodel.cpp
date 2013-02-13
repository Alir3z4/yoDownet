/****************************************************************************************
** downloadtablemodel.cpp is part of yoDownet
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

#include "downloadtablemodel.h"

DownloadTableModel::DownloadTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int DownloadTableModel::rowCount(const QModelIndex &parent) const
{
}

int DownloadTableModel::columnCount(const QModelIndex &parent) const
{
}

QVariant DownloadTableModel::data(const QModelIndex &index, int role) const
{
}

QVariant DownloadTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
}

Qt::ItemFlags DownloadTableModel::flags(const QModelIndex &index) const
{
}

bool DownloadTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

bool DownloadTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
}

bool DownloadTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
}
