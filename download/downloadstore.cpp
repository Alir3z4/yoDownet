/****************************************************************************************
** downloadstore.cpp is part of yoDownet
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

#include "downloadstore.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSettings>
#include "download/downloadconstants.h"

DownloadStore::DownloadStore(QObject *parent) :
    QObject(parent), _logger(new LogMe(this))
{
}

void DownloadStore::loadDownloads()
{

}

void DownloadStore::saveDownloads()
{
    _logger->info("[Saving downloads] to settings.");

    int rowCount = this->downloadModel()->downloadListCount();
    int columnCount = this->downloadModel()->downloadAttributeCount();

    _logger->info(QString("Downloads count: %1").arg(rowCount));

    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonObject jsonObjectItem;

    for (int row = 0; row < rowCount; ++row) {
        _logger->info(QString("Serializing row: #%1 to Json").arg(row));

        jsonObjectItem = QJsonObject();
        for (int column = 0; column < columnCount; ++column) {
            jsonObjectItem[QString::number(column)] = this->downloadModel()->downloadItemValue(row, static_cast<DownloadConstants::Attributes::Attributes>(column)).toJsonObject();
        }
        jsonObject[QString::number(row)] = jsonObjectItem;
    }
    jsonDocument.setObject(jsonObject);

    _logger->info("Writing to settings file.");
    QSettings settings;
    settings.beginGroup("DownloadStore");
    settings.setValue("downloadsJsonString", jsonDocument.toJson());
    settings.endGroup();

    _logger->success("![Saving downloads] to settings.");
}
DownloadTableModel *DownloadStore::downloadModel() const
{
    return _downloadModel;
}

void DownloadStore::setDownloadModel(DownloadTableModel *downloadModel)
{
    _downloadModel = downloadModel;
}

