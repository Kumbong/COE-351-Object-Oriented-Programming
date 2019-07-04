#include "Mainwindow/mainwindow.h"
#include <QApplication>
#include "Initialisation/loginscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Kenkey Boutique");
    w.setWindowIcon(QIcon(":/windowIcon.png"));
//    w.show();
    return a.exec();
}
