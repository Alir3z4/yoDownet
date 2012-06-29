/****************************************************************************************
** basevalidator.h is part of yoDownet
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

#ifndef REGEXVALIDATOR_H
#define REGEXVALIDATOR_H

#include <QObject>
#include "plus/messages/constants.h"

class BaseValidator : public QObject
{
    Q_OBJECT
public:
    explicit BaseValidator(QObject *parent = 0);
    ~BaseValidator();

protected:
    QString _input;

    void setInput(const QString &input);

    virtual bool isValid() = 0;
    virtual MessageConstants::Tag errorTag() const = 0;
    virtual QString errorTitle() const = 0;
    virtual QString errorMessage() const = 0;
};

#endif // REGEXVALIDATOR_H
