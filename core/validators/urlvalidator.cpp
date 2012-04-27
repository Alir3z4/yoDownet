#include "urlvalidator.h"

UrlValidator::UrlValidator(const QString &url)
{

    setInput(url);
    setErrorMessage(tr("%1 is invalid URL").arg(url));

    // For the Record this code is copied from django.core.validators.URLValidator
    // And Also i want to say thank you to all the django [devs|community|users]
    // Django Rocks!
    QString regexPattern =
            "^(?:http|ftp)s?://"    // http:// or https://
            "(?:(?:[A-Z0-9](?:[A-Z0-9-]{0,61}[A-Z0-9])?\\.)+(?:[A-Z]{2,6}\\.?|[A-Z0-9-]{2,}\\.?)|"    // #domain...
            "localhost|"    // localhost...
            "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})"    // ...or ip
            "(?::\\d+)?"    // optional port
            "(?:/?|[/?]\\S+)$";
    _regexValidator = new QRegExpValidator(QRegExp(regexPattern, Qt::CaseInsensitive), this->parent());
}
}
