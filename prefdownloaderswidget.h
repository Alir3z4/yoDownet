#ifndef PREFDOWNLOADERSWIDGET_H
#define PREFDOWNLOADERSWIDGET_H

#include <QWidget>

namespace Ui {
class PrefDownloadersWidget;
}

class PrefDownloadersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrefDownloadersWidget(QWidget *parent = 0);
    ~PrefDownloadersWidget();

    const QString savePath();
    
private:
    Ui::PrefDownloadersWidget *ui;
};

#endif // PREFDOWNLOADERSWIDGET_H
