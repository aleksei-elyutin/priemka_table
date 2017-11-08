#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>
#include <QLayout>
#include <QTableWidget>
#include <QPushButton>

//#include "../../extra_widgets/monheaderwidget.h"
//#include "../../extra_widgets/stageprogresswidget.h"
//#include "../../extra_widgets/tablewidget.h"

//#include "../../headers/contract.h"
//#include "../../headers/stage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    QWidget w;
//    w.setGeometry(0,0,1000,200);
//     = new QScrollArea();
//    QVBoxLayout* layout = new  QVBoxLayout(&w);
//    QPalette *pal = new QPalette(QColor("grey"));
//    QVector <Contract*> contracts;
//     for (int i = 0; i < 5; i++){
//         Contract *tmp_contract  = new Contract(i+1,
//                 QString("Наименование контракта номер ")+QString::number(i+1));
//         for (int k=0; k<=i; k++)
//         {
//             Stage *tmp_stage = new Stage(QDate(2017,5,10),QDate(2017,11,10+k+i));
//             tmp_contract->pushStage(tmp_stage);
//         }
//         contracts.push_back(tmp_contract);
//     }

//     table = new TableWidget(&w,&contracts);

//     layout->addWidget(table);
//     //table->resize(1700, 800);
//     //_scrollArea->setWidget(table); //?????
//    w.setLayout(layout);

//    w.setPalette(*pal);

    QTableWidget *table = new QTableWidget(&w);
    QLayout *layout = new QVBoxLayout(&w);



    layout->addWidget(table);
    //QWidget *btnbar = new QWidget(&w);
    QLayout *hlayout = new QHBoxLayout();
    QPushButton *btn1 = new QPushButton();
    //btn1->setSizePolicy(QSizePolicy());
    QPushButton *btn2 = new QPushButton();
    QSpacerItem *hspacer = new QSpacerItem(500,100);
    layout->addL

    hlayout->addWidget(btn1);
    hlayout->addWidget(btn2);

    //btnbar->layout()->setAlignment(btn1,Qt::AlignLeft);

    //btnbar->setLayout(hlayout);


   // w.setLayout(layout);
    w.show();


   // table->show();
    return a.exec();
}
