#ifndef ADDURLDIALOG_H
#define ADDURLDIALOG_H

#include <QDialog>

namespace Ui {
class AddUrlDialog;
}

class AddUrlDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddUrlDialog(QWidget *parent = 0);
    ~AddUrlDialog();
    
private:
    Ui::AddUrlDialog *ui;
};

#endif // ADDURLDIALOG_H
