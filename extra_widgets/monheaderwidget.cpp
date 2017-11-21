#include "monheaderwidget.h"

MonHeaderWidget::MonHeaderWidget(QWidget *parent) :   QWidget(parent)
{

      setMaximumHeight(_wheight);
      setMinimumHeight(_wheight);

      for (int i=1; i <= 12; i++) //12
      {
          QLabel *month = new QLabel(this);

          month->setObjectName("month_" + i);

          month->setStyleSheet("border: 1px solid black;");
          month->setText(QDate::longMonthName(i,QDate::StandaloneFormat));
          qDebug() << QDate::longMonthName(i,QDate::StandaloneFormat);
          mons.push_back(month);
      }
      setMinimumWidth(365*2);

}



void MonHeaderWidget::setYear(int year)
{
    _year = year;
}

void MonHeaderWidget::setNamesVisible(bool v)
{

    for (int i=0; i < 12; i++)
    {
       if (!v) mons.at(i)->setText("");
       else mons.at(i)->setText(QDate::longMonthName(i+1,QDate::StandaloneFormat));
    }
}



void MonHeaderWidget::resizeEvent(QResizeEvent *event)
{

   // lbl->setText(QString::number(this->size().width())+"x" + QString::number(this->size().height()));
    //size_factor
    int total_width = 0;

   // qDebug() << QString::number(event->size().width())+"x" + QString::number(event->size().height());

    _size_factor = event->size().width()/QDate(_year,1,1).daysInYear();


    mons[0]->setGeometry(0, 0, (QDate(_year,1,1).daysInMonth()*event->size().width())/QDate(_year,1,1).daysInYear() ,_wheight);
    total_width += mons[0]->geometry().width();
    for (int i=1; i < 12; i++) //12
    {

        mons[i]->setGeometry(mons[i-1]->geometry().x()+mons[i-1]->geometry().width(), 0, (QDate(_year,i,1).daysInMonth()*event->size().width())/QDate(_year,1,1).daysInYear() ,_wheight);
        total_width += mons[i]->geometry().width();
    }
   // qDebug() << "Total: " << total_width;

    QWidget::resizeEvent(event);
}

