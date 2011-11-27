#include "yomessage.h"

void yoMessage::dbError(QString &argDBErrorText, QString &argAction)
{
    critical(0, tr("yoDownet : Database error"),
                          tr("Whoops, we have little error from database on <b>%1</b>.<br />"
                             "See the details below:<br />%2").arg(argAction, argDBErrorText),
                          Ok);
}

void yoMessage::userError(QString &argDetailsText)
{
    information(0, tr("yoDownet : Watch out"), tr("%1").arg(argDetailsText), Ok);
}

int yoMessage::ask(QString &argQuestionTitle, QString &argQuestionBody)
{
    StandardButton ask;
    ask = question(0, tr("yoDownet : %1").arg(argQuestionTitle),
                                           argQuestionBody,
                                           Yes | No);
    return ask;
}
