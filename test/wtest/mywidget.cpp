#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    //setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(180, 180, 180, 255);");
    resize(500,500);

    l = new QVBoxLayout(this);
    for (int i =0; i<5 ; i++)
    {
        QPushButton *pbtn = new QPushButton(this);
        pbtn->setText("Button"+QString::number(i));
        connect (pbtn, &QPushButton::clicked, this, &mywidget::buttonClicked);
        l->addWidget(pbtn);
    }


    //pa = new QPropertyAnimation(this);
    //pa->setPropertyName("geometry");

   // btn->setGeometry(width()/2, height()/2, 20 ,20);
    //btn->setText("Съебус");



}

void mywidget::buttonClicked()
{

    l->removeWidget(qobject_cast<QWidget*>(sender()));
    l->insertWidget(0,qobject_cast<QWidget*>(sender()));

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


