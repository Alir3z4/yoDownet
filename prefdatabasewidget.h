#ifndef PREFDATABASEWIDGET_H
#define PREFDATABASEWIDGET_H

#include <QWidget>

namespace Ui {
class PrefDataBaseWidget;
}

class PrefDataBaseWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrefDataBaseWidget(QWidget *parent = 0);
    ~PrefDataBaseWidget();
    
private:
    Ui::PrefDataBaseWidget *ui;
};

#endif // PREFDATABASEWIDGET_H
