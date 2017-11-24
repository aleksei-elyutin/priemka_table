#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(255, 255, 255, 255); background-color: rgb(20, 20, 20);");
    resize(500,500);

    l = new QVBoxLayout(this);
    for (int i =0; i<5 ; i++)
    {
        QPushButton *pbtn = new QPushButton(this);
        pbtn->setText("Button"+QString::number(i));
        pbtn->setFixedSize(200,30+i*10);
        pbtn->setStyleSheet("color: rgba(255, 255, 255, 255); background-color: rgb(50, 50, 50);");
        connect (pbtn, &QPushButton::clicked, this, &mywidget::buttonClicked);
        l->addWidget(pbtn);
    }

    pa = new QPropertyAnimation(this);
    pa->setPropertyName("geometry");
    pa->setDuration(200);

   // btn->setGeometry(width()/2, height()/2, 20 ,20);
    //btn->setText("Съебус");



}

void mywidget::buttonClicked()
{



    QWidget *_sender = qobject_cast<QWidget*> (sender());
    QRect current_sender_geometry = _sender->geometry();


    QWidget *dummy = new QWidget(this);
    dummy->setFixedSize(current_sender_geometry.width(),current_sender_geometry.height());
    dummy->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);



    if (l->indexOf(_sender)){

        l->removeWidget(_sender);
        //l->insertWidget(index,&dummy);
        l->insertWidget(0,dummy);

        QRect new_sender_geometry = l->itemAt(1)->geometry();


        pa->setTargetObject(_sender);
        pa->setStartValue(current_sender_geometry);
         qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_sender_geometry);
        qDebug() << "endValue:"<< pa->endValue();

        pa->start();

        l->removeWidget(dummy);
        l->insertWidget(0,_sender);
    }

    delete dummy;

}

//void mywidget::buttonClicked()
//{
//    pa->setDuration(100);

//    QRect current_geometry = btn->geometry();
//    pa->setStartValue(current_geometry);

//    int new_X =  current_geometry.x()+((rand() % 200)-100);
//    int new_Y = current_geometry.y()+((rand() % 200)-100);
//    if (new_X+btn->width() > this->width()) new_X = this->width()-btn->width();
//    if (new_Y+btn->height() > this->height()) new_Y = this->height()-btn->height();
//    QRect new_geometry = QRect (new_X, new_Y, btn->width() ,btn->height());
//    qDebug() << "Btn Current Geometry" << btn->x() << btn->y() << btn->width() << btn->height();
//    pa->setEndValue(new_geometry);

//    qDebug() << "Btn New Geometry" << btn->x() << btn->y() << btn->width() << btn->height();
//    pa->start();
//    pa->finished();

//}


