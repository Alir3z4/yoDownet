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

    // set home directory on pathEdit
    ui->pathEdit->setText(QDir::homePath());
}

FileBrowz::~FileBrowz()
{
    delete ui;
}

const QString FileBrowz::caption()
{
    return _caption;
}

const QString FileBrowz::filter()
{
    return _filter;
}

const QString FileBrowz::browzPath()
{
    return ui->pathEdit->text();
}

FileBrowz::BrowzType FileBrowz::browzType() const
{
    return _type;
}

const QFileDialog::Options FileBrowz::options()
{
    return _options;
}

void FileBrowz::setCaption(const QString &caption)
{
    _caption = caption;
}

void FileBrowz::setFilter(const QString &filter)
{
    _filter = filter;
}

void FileBrowz::setBrowzType(FileBrowz::BrowzType type)
{
    _type = type;
}

void FileBrowz::setOptions(QFileDialog::Options options)
{
    _options = options;
}

void FileBrowz::setBrowzPath(const QString &browztPath)
{
    ui->pathEdit->setText(browztPath);
}

void FileBrowz::setPath(const QString &path)
{
    // TODO: is writable or what ?
    ui->pathEdit->setText((path.isEmpty()) ? QDir::homePath() : path);
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
