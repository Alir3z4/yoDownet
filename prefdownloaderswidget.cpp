#include "prefdownloaderswidget.h"
#include "ui_prefdownloaderswidget.h"

PrefDownloadersWidget::PrefDownloadersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefDownloadersWidget)
{
    ui->setupUi(this);

    // TODO: get set last selected save to directory path from saved setting [INI files] with QSettings
    ui->savePathEdit->setCaption(tr("Select a directory to save downloaded files"));
    ui->savePathEdit->setBrowzType(FileBrowz::GetDirectory);
}

PrefDownloadersWidget::~PrefDownloadersWidget()
{
    delete ui;
}

const QString PrefDownloadersWidget::savePath()
{
    return ui->savePathEdit->browzPath();
}
