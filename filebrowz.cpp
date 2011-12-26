#include "filebrowz.h"
#include "ui_filebrowz.h"

FileBrowz::FileBrowz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileBrowz)
{
    ui->setupUi(this);
}

FileBrowz::~FileBrowz()
{
    delete ui;
}
