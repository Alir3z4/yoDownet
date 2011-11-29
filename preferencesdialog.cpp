#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    // Setup buttons
    okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    applyButton = ui->buttonBox->button(QDialogButtonBox::Apply);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}
