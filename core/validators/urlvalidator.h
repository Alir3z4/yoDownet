#ifndef URLVALIDATOR_H
#define URLVALIDATOR_H

#include "regexvalidator.h"

class UrlValidator : public RegexValidator
{
public:
    UrlValidator(const QString &url = NULL);

    inline void setUrl(const QString &url) {
        setInput(url);
    }

    bool isValid();
};

#endif // URLVALIDATOR_H
