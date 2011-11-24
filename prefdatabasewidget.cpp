#include "prefdatabasewidget.h"
#include "ui_prefdatabasewidget.h"

PrefDataBaseWidget::PrefDataBaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDataBaseWidget)
{
    ui->setupUi(this);
}

PrefDataBaseWidget::~PrefDataBaseWidget()
{
    delete ui;
}
