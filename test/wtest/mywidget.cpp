#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{


  // QHBoxLayout *wlayout = new QHBoxLayout(this);
  // lbl = new QLabel(this);
  // wlayout->addWidget(lbl);
  // lbl->setText("init");

    setMaximumHeight(_wheight);
    setMinimumHeight(_wheight);

    for (int i=0; i < 12; i++) //12
    {
        QLabel *month = new QLabel(this);


       // qDebug() << "Начало месяца " << i << " ("<< QDate::longMonthName(i,QDate::StandaloneFormat) <<")"<< " - день:" << QDate(_year,i,1).dayOfYear();
       // qDebug() << "Количество дней:" << QDate(_year,i,1).daysInMonth();
        month->setObjectName("month_" + i+1);

        month->setStyleSheet("border: 1px solid black;");
        month->setText(QDate::longMonthName(i+1,QDate::StandaloneFormat));
        //month->setText(this->height()+ "x" + this->width());
        mons.push_back(month);
    }

}



void mywidget::setYear(int year)
{
    _year = year;
}

void mywidget::resizeEvent(QResizeEvent *event)
{

   // lbl->setText(QString::number(this->size().width())+"x" + QString::number(this->size().height()));
    //size_factor

    qDebug() << QString::number(event->size().width())+"x" + QString::number(event->size().height());
    mons[0]->setGeometry(0, 0, (QDate(_year,1,1).daysInMonth())*_size_factor ,_wheight);
    for (int i=1; i < 12; i++) //12
    {

        mons[i]->setGeometry(mons[i-1]->geometry().x()+mons[i-1]->geometry().width(), 0, (QDate(_year,i-1,1).daysInMonth())*_size_factor ,_wheight);
    }

    QWidget::resizeEvent(event);
}



