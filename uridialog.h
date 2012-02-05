#ifndef URIDIALOG_H
#define URIDIALOG_H

#include <QDialog>
#include <QVariantList>

namespace Ui {
class UriDialog;
}

class UriDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UriDialog(QWidget *parent = 0);
    ~UriDialog();

    const QString uri();
    
private slots:
    void on_uriEdit_textChanged();

    void on_uriEdit_returnPressed();

private:
    Ui::UriDialog *ui;
};

#endif // URIDIALOG_H
