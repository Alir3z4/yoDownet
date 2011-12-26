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

    inline QString caption() const { return _caption; }
    inline QString filter() const { return _filter; }
    inline BrowzType browzType() const { return _type; }
    inline QFileDialog::Options options() const { return _options; }

public slots:
    inline void setCaption(const QString &caption) { _caption = caption; }
    inline void setFilter(const QString &filter) { _filter = filter; }
    inline void setBrowzType(BrowzType type) { _type = type; }
    inline void setOptions(QFileDialog::Options options) { _options = options; }
    
private slots:
    void on_browzButton_clicked();

signals:
    void fileChanged(QString file);

private:
    Ui::FileBrowz *ui;
    QString _caption;
    QString _filter;
    BrowzType _type;
    QFileDialog::Options _options;
};

#endif // FileBrowz_H
