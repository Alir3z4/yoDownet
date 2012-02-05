#ifndef FileBrowz_H
#define FileBrowz_H

#include <QFileDialog>

namespace Ui {
class FileBrowz;
}

class FileBrowz : public QWidget
{
    Q_OBJECT
    
public:
    enum BrowzType {
        GetFileName,
        GetDirectory
    };

    explicit FileBrowz(QWidget *parent = 0);
    ~FileBrowz();

    const QString caption();
    const QString filter();
    const QString browzPath();
    BrowzType browzType() const;
    const QFileDialog::Options options();

public slots:
    void setCaption(const QString &caption);
    void setFilter(const QString &filter);
    void setBrowzType(BrowzType type);
    void setOptions(QFileDialog::Options options);
    void setBrowzPath(const QString &browztPath);
    void setPath(const QString &path);
    
private slots:
    void on_browzButton_clicked();

signals:
    void fileChanged(const QString &newFile);

private:
    Ui::FileBrowz *ui;
    QString _caption;
    QString _filter;
    BrowzType _type;
    QFileDialog::Options _options;
};

#endif // FileBrowz_H
