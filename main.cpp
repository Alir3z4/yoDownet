#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("yoDownet");
    QCoreApplication::setOrganizationName("Alir3z4");
    QCoreApplication::setOrganizationDomain("yodownet.sourceforge.net");
    MainWindow w;
    w.show();

    return a.exec();
}
