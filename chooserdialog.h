#ifndef CHOOSERDIALOG_H
#define CHOOSERDIALOG_H

#include <QWidget>

namespace Ui {
class ChooserDialog;
}

class ChooserDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChooserDialog(QWidget *parent = 0);
    ~ChooserDialog();
    
private:
    Ui::ChooserDialog *ui;
};

#endif // CHOOSERDIALOG_H
