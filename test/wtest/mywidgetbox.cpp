#include "mywidgetbox.h"

mywidgetBox::mywidgetBox(QWidget *parent) : QWidget(parent)
{
    QWidget *wdgt = new QWidget(this);
    QHBoxLayout *wdgt_layout = new QHBoxLayout(wdgt);

    QLCDNumber *num = new QLCDNumber(wdgt);
    num->display(QString::number(i));
    num->setMinimumHeight(50);
    num->setMinimumWidth(50);
    num->setMaximumHeight(50);
    num->setMaximumWidth(50);
    num->setDigitCount(3);
    num->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    wdgt_layout->addWidget(num);
    num->setObjectName("number");


    QPushButton *pbtn = new QPushButton(wdgt);
    wdgt_layout->addWidget(pbtn);
    pbtn->setText("Pop");
    pbtn->setFixedSize(200,50+i*10);
    pbtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    pbtn->setStyleSheet("color: rgba(255, 255, 255, 255); background-color: rgb(50, 50, 50);");
    connect (pbtn, &QPushButton::clicked, this, &mywidget::buttonClicked);




    QLabel *name = new QLabel(wdgt);
    name->setText("Виджет номер"+QString::number(i));
    wdgt_layout->addWidget(name);
}

