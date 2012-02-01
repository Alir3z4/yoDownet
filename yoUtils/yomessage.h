#ifndef YOMESSAGE_H
#define YOMESSAGE_H

#include <QtGui/QMessageBox>
class QString;

class yoMessage : public QMessageBox
{
    Q_OBJECT
public:
    //explicit yoMessage(QObject *parent = 0);
    void dbError(const QString dbErrorText, const QString action);
    void userError(const QString detailsText);
    void notify(const QString &notif);
    int ask(const QString argQuestionTitle, const QString argQuestionBody);

};

#endif // YOMESSAGE_H
