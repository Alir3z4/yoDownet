#include "regexvalidator.h"

RegexValidator::RegexValidator(QObject *parent) :
    QObject(parent)
{}

RegexValidator::~RegexValidator()
{
    delete _regexValidator;
}
