#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include "prefdownloaderswidget.h"
#include "prefdatabasewidget.h"
#include <QPushButton>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();
    
private slots:
    void on_buttonBox_accepted();
    void saveSettings();
    void closeEvent(QCloseEvent *);

private:
    Ui::PreferencesDialog *ui;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *applyButton;

    PrefDownloadersWidget *prefDler;
    PrefDataBaseWidget *prefDb;

    void addSection(QWidget *w);

    // Load settings
    void loadSettings();
};

#endif // PREFERENCESDIALOG_H
