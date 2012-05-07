#include "urlvalidator.h"
#include "plus/messages/constants.h"
#include <QUrl>

UrlValidator::UrlValidator(QObject *parent, const QString &url) :
    BaseValidator(parent)
{
    if(!url.isNull()) setInput(url);
}

void UrlValidator::setUrl(const QString &url)
{
    _input = QUrl(url).toEncoded();
}

bool UrlValidator::isValid()
{
    return QUrl(_input).isValid();
}

MessageConstants::Tag UrlValidator::errorTag() const
{
    return MessageConstants::Critial;
}

QString UrlValidator::errorTitle() const
{
    return tr("Invalid Url");
}

QString UrlValidator::errorMessage() const
{
    if(!_input.isEmpty())
        return tr("%1 is not a valid Url.")
                .arg(_input);
    return QString("");
}
