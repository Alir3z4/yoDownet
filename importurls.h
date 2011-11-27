#ifndef IMPORTURLS_H
#define IMPORTURLS_H

#include <QDialog>

namespace Ui {
class ImportUrls;
}

class ImportUrls : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportUrls(QWidget *parent = 0);
    ~ImportUrls();
    
private:
    Ui::ImportUrls *ui;
};

#endif // IMPORTURLS_H
