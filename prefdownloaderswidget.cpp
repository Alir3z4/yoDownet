#include "prefdownloaderswidget.h"
#include "ui_prefdownloaderswidget.h"

PrefDownloadersWidget::PrefDownloadersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDownloadersWidget)
{
    ui->setupUi(this);
}

PrefDownloadersWidget::~PrefDownloadersWidget()
{
    delete ui;
}
