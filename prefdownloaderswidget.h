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

    QString saveDir()const;

public slots:
    void setSaveDir(const QString &saveDir);

    
private:
    Ui::PrefDownloadersWidget *ui;
};

#endif // PREFDOWNLOADERSWIDGET_H
