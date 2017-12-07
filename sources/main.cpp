#include "../headers/mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QWidget>
#include "./extra_widgets/dletedialog.h"

#include "extra_widgets/tablewidget.h"
#include "headers/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1500,1000);
    w.show();
    return a.exec();
}
