#include "monheaderwidget.h"

MonHeaderWidget::MonHeaderWidget(QWidget *parent) :   QWidget(parent)
{

      //setMaximumHeight(_wheight);
      setMinimumHeight(_wheight);
      /*setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px; "
                              "color: rgb(255, 255, 255); border: 0px solid black;");*/

      for (int i=1; i <= 12; i++) //12
      {
          QLabel *month = new QLabel(this);

          month->setObjectName("month_" + i);

          month->setStyleSheet("qproperty-alignment: AlignCenter;");
          month->setText(QDate::longMonthName(i,QDate::StandaloneFormat));
          //qDebug() << QDate::longMonthName(i,QDate::StandaloneFormat);
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


void MonHeaderWidget::setVerticalSize(int vs)
{
      _wheight = vs;
     // this->resize(this->width(),_wheight );
      setMinimumHeight(_wheight);
      setMaximumHeight(_wheight);
//    for (int i=0; i < 12; i++)
//    {
//       mons.at(i)->setText("");
//       else mons.at(i)->setText(QDate::longMonthName(i+1,QDate::StandaloneFormat));
//    }
}


void MonHeaderWidget::resizeEvent(QResizeEvent *event)
{

    _grid_width = 0;
   // qDebug() << "Event size: " <<(double) event->size().width() << "Days: "  << (double) QDate(_year,1,1).daysInYear();
    _size_factor = (double) event->size().width()/ (double) QDate(_year,1,1).daysInYear();
  //  qDebug() << "Size factor " << _size_factor;

    mons[0]->setGeometry(0, 0, (QDate(_year,1,1).daysInMonth()*event->size().width())/QDate(_year,1,1).daysInYear() ,_wheight);
    _grid_width += mons[0]->geometry().width();
    for (int i=1; i < 12; i++) //12
    {

        mons[i]->setGeometry(mons[i-1]->geometry().x()+mons[i-1]->geometry().width(), 0, QDate(_year,i,1).daysInMonth()*_size_factor ,_wheight);
        _grid_width += mons[i]->geometry().width();
    }
   // qDebug() << "Total: " << total_width;

    QWidget::resizeEvent(event);
}

double MonHeaderWidget::getSizeFactor()
{
    return _size_factor;
}

int MonHeaderWidget::getGridWidth()
{
    return _grid_width;
}

