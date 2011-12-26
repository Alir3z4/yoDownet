#include "filebrowz.h"
#include "ui_filebrowz.h"

FileBrowz::FileBrowz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileBrowz)
{
    ui->setupUi(this);

    // make GetFileName mode to default
    setBrowzType(GetFileName);
    setOptions(0);
}

FileBrowz::~FileBrowz()
{
    delete ui;
}

void FileBrowz::on_browzButton_clicked()
{
    QString result;

    if(browzType() == GetDirectory) {
        result = QFileDialog::getExistingDirectory(
                    this, caption(), ui->pathEdit->text());

    } else if(browzType() == GetFileName) {
        result = QFileDialog::getOpenFileName(this, caption(), ui->pathEdit->text(), filter());
    }

    if(!result.isEmpty()) {
        QString oldFile = ui->pathEdit->text();
        ui->pathEdit->setText(result);
        if (oldFile != result) emit fileChanged(result);
    }
}
