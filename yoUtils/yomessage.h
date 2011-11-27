#ifndef YOMESSAGE_H
#define YOMESSAGE_H

#include <QtGui/QMessageBox>
#include <QtCore/QString>

class yoMessage : public QMessageBox
{
    Q_OBJECT
public:
    //explicit yoMessage(QObject *parent = 0);
    void dbError(QString &argDBErrorText, QString &argAction);
    void userError(QString &argDetailsText);
    int ask(QString &argQuestionTitle, QString &argQuestionBody);

};

#endif // YOMESSAGE_H
