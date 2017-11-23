#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QTableWidget>
#include <QDebug>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDate>
#include <iostream>
#include "mywidget.h"

//#include "../../extra_widgets/monheaderwidget.h"
//#include "../../extra_widgets/stageprogresswidget.h"
//#include "../../extra_widgets/tablewidget.h"

//#include "../../headers/contract.h"
//#include "../../headers/stage.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QWidget window;

//    QVBoxLayout *l = new QVBoxLayout(&window);

    mywidget *w = new mywidget();


    w->show();



    return a.exec();
}
