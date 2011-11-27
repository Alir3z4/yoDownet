#include "importurls.h"
#include "ui_importurls.h"

ImportUrls::ImportUrls(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportUrls)
{
    ui->setupUi(this);
}

ImportUrls::~ImportUrls()
{
    delete ui;
}
