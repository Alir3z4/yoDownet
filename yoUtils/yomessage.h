#ifndef YOMESSAGE_H
#define YOMESSAGE_H

#include <QtGui/QMessageBox>
class QString;

class yoMessage : public QMessageBox
{
    Q_OBJECT
public:
    //explicit yoMessage(QObject *parent = 0);
    void dbError(QString dbErrorText, QString action);
    void userError(QString detailsText);
    int ask(QString argQuestionTitle, QString argQuestionBody);

};

#endif // YOMESSAGE_H
