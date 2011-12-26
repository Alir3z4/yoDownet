#ifndef FileBrowz_H
#define FileBrowz_H

#include <QWidget>

namespace Ui {
class FileBrowz;
}

class FileBrowz : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileBrowz(QWidget *parent = 0);
    ~FileBrowz();
    
private:
    Ui::FileBrowz *ui;
};

#endif // FileBrowz_H
