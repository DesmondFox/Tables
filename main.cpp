#include "mainwindow.h"
#include "newfiledialog.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.show();


    return a.exec();
}
