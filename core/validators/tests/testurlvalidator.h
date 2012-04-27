#ifndef TESTURLVALIDATOR_H
#define TESTURLVALIDATOR_H

#include <QtTest/QtTest>
#include "core/validators/urlvalidator.h"

class TestUrlValidator : public QObject
{
    Q_OBJECT
public:
    explicit TestUrlValidator(QObject *parent = 0);

private slots:
    void plainUrl();
    void noDomainUrl();
    void noProtocol();
    void encodedUrl();
    void withSpaceUrl();
    void ftpUrl();
    void httpUrl();
    void sshUrl();

private:
    UrlValidator *_validator;
};

#endif // TESTURLVALIDATOR_H
