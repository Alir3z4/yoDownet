#include "addurldialog.h"
#include "ui_addurldialog.h"

AddUrlDialog::AddUrlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUrlDialog)
{
    ui->setupUi(this);
}

AddUrlDialog::~AddUrlDialog()
{
    delete ui;
}
