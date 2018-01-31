#include "../headers/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->resize(1500,1000);
    w->show();
    w->draw();

    return a.exec();
}
