#include "uridialog.h"
#include "ui_uridialog.h"

UriDialog::UriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UriDialog)
{
    ui->setupUi(this);
}

UriDialog::~UriDialog()
{
    delete ui;
}

const QVector<QString> UriDialog::uris()
{
    QVector<QString> uris;
    uris.push_back(ui->uriEdit->text());
    return uris;
}

void UriDialog::on_uriEdit_textChanged()
{
    if(!ui->uriEdit->text().isEmpty())
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setDisabled(true);
}

void UriDialog::on_uriEdit_returnPressed()
{
    if(ui->buttonBox->isEnabled())
        accepted();
}
