#ifndef REGEXVALIDATOR_H
#define REGEXVALIDATOR_H

#include <QObject>
#include <QRegExpValidator>
#include "plus/messages/constants.h"

class RegexValidator : public QObject
{
    Q_OBJECT
public:
    explicit RegexValidator(QObject *parent = 0);
    ~RegexValidator();

protected:
    QRegExpValidator *_regexValidator;
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
