#ifndef URLVALIDATOR_H
#define URLVALIDATOR_H

#include "core/validators/basevalidator.h"

class UrlValidator : public BaseValidator
{
public:
    UrlValidator(QObject *parent = 0, const QString &url = NULL);

    void setUrl(const QString &url);

    bool isValid();
    MessageConstants::Tag errorTag() const;
    QString errorTitle() const;
    QString errorMessage() const;
};

#endif // URLVALIDATOR_H
