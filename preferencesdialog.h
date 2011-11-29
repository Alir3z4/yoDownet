#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();
    
private:
    Ui::PreferencesDialog *ui;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *applyButton;

    void addSection(QWidget *w);
};

#endif // PREFERENCESDIALOG_H
