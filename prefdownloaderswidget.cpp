#include "prefdownloaderswidget.h"
#include "ui_prefdownloaderswidget.h"

PrefDownloadersWidget::PrefDownloadersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDownloadersWidget)
{
    ui->setupUi(this);

    ui->saveDirEdit->setCaption(tr("Select a directory to save downloaded files"));
    ui->saveDirEdit->setBrowzType(FileBrowz::GetDirectory);
}

PrefDownloadersWidget::~PrefDownloadersWidget()
{
    delete ui;
}

QString PrefDownloadersWidget::saveDir()const
{
    return ui->saveDirEdit->browzPath();
}

void PrefDownloadersWidget::setSaveDir(const QString &saveDir)
{
    ui->saveDirEdit->setPath(saveDir);
}
