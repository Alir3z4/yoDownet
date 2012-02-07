#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QSettings>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    // Setup buttons
    okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    applyButton = ui->buttonBox->button(QDialogButtonBox::Apply);

    // Setup widgets
    prefDler = new PrefDownloadersWidget;
    addSection(prefDler);

    prefDb = new PrefDataBaseWidget;
    addSection(prefDb);

    // Connecting Signal/Slot
    connect(applyButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

    // Let's load the settings
    loadSettings();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::addSection(QWidget *w)
{
    QListWidgetItem *i = new QListWidgetItem(w->windowIcon(), w->windowTitle());
    ui->sectionListWidget->addItem(i);
    ui->pages->addWidget(w);
}

void PreferencesDialog::saveSettings()
{
    QSettings settings;

    // Save PreferencesDialog settings
    settings.beginGroup("PreferencesDialog");


    // Save PrefDownloadersWidget
    settings.beginGroup("PrefDownloadersWidget");
    settings.setValue("saveDir", prefDler->saveDir());
    settings.endGroup();

    settings.endGroup();

}

void PreferencesDialog::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.beginGroup("PreferencesDialog");
    settings.setValue("pos", pos());
    settings.setValue("geometry", geometry());
    settings.setValue("fullScreen", isFullScreen());
    settings.setValue("currentRow", ui->sectionListWidget->currentRow());
    settings.endGroup();
}

void PreferencesDialog::loadSettings()
{
    QSettings settings;

    // Save PreferencesDialog settings
    settings.beginGroup("PreferencesDialog");
    move(settings.value("pos", QPoint(62, 341)).toPoint());
    setGeometry(settings.value("geometry", QRect(64, 364, 643, 425)).toRect());
    if(settings.value("fullscreen").toBool())
        showFullScreen();
    ui->sectionListWidget->setCurrentRow(settings.value("currentRow", -1).toInt());

    // Load PrefDownloadersWidget
    settings.beginGroup("PrefDownloadersWidget");
    prefDler->setSaveDir(settings.value("saveDir").toString());
    settings.endGroup();

    settings.endGroup();
}

void PreferencesDialog::on_buttonBox_accepted()
{
    saveSettings();
}
