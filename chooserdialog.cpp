#include "chooserdialog.h"
#include "ui_chooserdialog.h"

ChooserDialog::ChooserDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooserDialog)
{
    ui->setupUi(this);
}

ChooserDialog::~ChooserDialog()
{
    delete ui;
}
