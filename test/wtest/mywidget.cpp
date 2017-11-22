#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{


  // QHBoxLayout *wlayout = new QHBoxLayout(this);
  // lbl = new QLabel(this);
  // wlayout->addWidget(lbl);
  // lbl->setText("init");

    setMaximumHeight(_wheight);
    setMinimumHeight(_wheight);

    setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(180, 180, 180, 255);");


    for (int i=1; i <= 12; i++) //12
    {
        QLabel *month = new QLabel(this);


       // qDebug() << "Начало месяца " << i << " ("<< QDate::longMonthName(i,QDate::StandaloneFormat) <<")"<< " - день:" << QDate(_year,i,1).dayOfYear();
       // qDebug() << "Количество дней:" << QDate(_year,i,1).daysInMonth();
        month->setObjectName("month_" + i);

        month->setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(180, 180, 180, 250);");
        //month->setText(QDate::longMonthName(i,QDate::StandaloneFormat));
         qDebug() << QDate::longMonthName(i,QDate::StandaloneFormat);
        //month->setText(this->height()+ "x" + this->width());
        mons.push_back(month);
    }
    setMinimumWidth(365*2);

    _progress_bar = new QProgressBar(this);

     _progress_bar->setStyleSheet("QProgressBar { border: 1px solid grey; background-color: rgba(0, 255, 0, 50); text-align: middle; border-radius: 0px;} \
                              QProgressBar::chunk {background-color: rgba(0, 255, 0, 200); width: 3px; margin: 0px; text-align: middle; }");

    _progress_bar->setMinimum(1);
    _progress_bar->setMaximum(100);
     _progress_bar->setValue(50);

    _progress_bar->setGeometry (100,0,500,_wheight);


}



void mywidget::setYear(int year)
{
    _selected_year = year;

}

void mywidget::resizeEvent(QResizeEvent *event)
{

   // QWidget::resizeEvent(event);
   // lbl->setText(QString::number(this->size().width())+"x" + QString::number(this->size().height()));
    //size_factor
    int total_width = 0;

    qDebug() << QString::number(event->size().width())+"x" + QString::number(event->size().height());

    _size_factor = (double) event->size().width()/ (double) QDate(_selected_year,1,1).daysInYear();


    mons[0]->setGeometry(0, 0, (QDate(_selected_year,1,1).daysInMonth()*event->size().width())/QDate(_selected_year,1,1).daysInYear() ,_wheight);
    total_width += mons[0]->geometry().width();
    for (int i=1; i < 12; i++) //12
    {

        mons[i]->setGeometry(mons[i-1]->geometry().x()+mons[i-1]->geometry().width(), 0, QDate(_selected_year,i,1).daysInMonth()*_size_factor ,_wheight);
        total_width += mons[i]->geometry().width();
    }






    qDebug() << "Total: " << total_width << ". Widget width: " << this->width();
}



