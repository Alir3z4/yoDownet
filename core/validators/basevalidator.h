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

    inline void setInput(const QString &input) {
        _input = input;
    }

    virtual bool isValid() = 0;
    virtual MessageConstants::Tag errorTag() const = 0;
    virtual QString errorTitle() const = 0;
    virtual QString errorMessage() const = 0;
};

#endif // REGEXVALIDATOR_H
