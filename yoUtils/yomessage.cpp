#include "yomessage.h"

void yoMessage::dbError(const QString dbErrorText, const QString action)
{
    critical(0, tr("yoDownet : Database error"),
                          tr("Whoops, we have little error from database on <b>%1</b>.<br />"
                             "See the details below:<br />%2").arg(action, dbErrorText),
                          Ok);
}

void yoMessage::userError(const QString detailsText)
{
    critical(0, tr("yoDownet : Watch out"), QString("%1").arg(detailsText), Ok);
}

void yoMessage::notify(const QString &notif)
{
    information(0, tr("yoDownet : Just for information sake ;)"),
                notif, Ok);
}

int yoMessage::ask(const QString argQuestionTitle, const QString argQuestionBody)
{
    StandardButton ask;
    ask = question(0, tr("yoDownet : %1").arg(argQuestionTitle),
                                           argQuestionBody,
                                           Yes | No);
    return ask;
}
