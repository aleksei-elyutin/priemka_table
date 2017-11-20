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
    QWidget window;

    QVBoxLayout *l = new QVBoxLayout(&window);

    mywidget *year_dock = new mywidget(&window);
    l->addWidget(year_dock);

    year_dock->setYear(2017);

   // qDebug() << QDate::isLeapYear(QDate::currentDate().year());
    window.show();



//    mywidget *lbl = new mywidget(&window);
//    QPushButton *btn = new QPushButton(&window);
//    l->addWidget(lbl);
//    l->addWidget(btn);
//    lbl->setLinkedWidget(&window);
//    QObject::connect(btn, &QPushButton::clicked , lbl, &mywidget::updateText);
//    //tbl->set

//    window.show();

    return a.exec();
}
