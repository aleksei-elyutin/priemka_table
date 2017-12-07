#include "../headers/stage.h"

//using namespace stage;
Stage::Stage(QObject *parent) : QObject(parent)
{

    _start_date = QDate(QDate::currentDate().year(),1,1);
    _finish_date = QDate(QDate::currentDate().year(),12,31);
    _stage_name = QString("** Новый этап **");

    _is_done = false;
    _is_20_done = false;
    _is_10_done = false;
    priority = calculatePriority();

}

void Stage::setStartDate(QDate startdate)
{
   // if (startdate < _finish_date )
    {
        _start_date = startdate;
        //qDebug() << "stardate:" << start_date; //TODO: use metadata for object name dbg
    }
   // else
//    {
//        _start_date = QDate::currentDate();
//        //qDebug() << "Invalid start_date. StartDate must be < finish_date:" <<  _finish_date.toString("yyyy.MMMM.dddd");
//    }
 //  if (!fileload_status)  emit imChanged();

}
void Stage::setFinishDate(QDate finishdate)
{
//    if (finishdate > _start_date)
     {
        qDebug() << "Date chnged from " << _finish_date.toString("yyyy.MMMM.dddd") << "to" << finishdate.toString("yyyy.MMMM.dddd");
            _finish_date=finishdate;
     }

//    else
//    {
//        _finish_date = QDate::currentDate();
//      // qDebug() << "Invalid start_date. StartDate must be < finish_date:" << _finish_date.toString("yyyy.MMMM.dddd");
//    }
  //  if (!fileload_status) emit imChanged();
}

void Stage::setStageName(QString name)
{
    _stage_name = name;
 //  if (!fileload_status)  emit imChanged();
}

void Stage::setDoneStatus(int status)
{
    if (status == Qt::Checked)
    {
    _is_done = true;
    }
    else _is_done = false;
    calculatePriority();
 //   if (!fileload_status) emit imChanged();
}

void Stage::setLeft10Status(int status)
{
    if (status == Qt::Checked)
    {
         _is_10_done = true;
    }
    else _is_10_done = false;
    calculatePriority();
 //   if (!fileload_status) emit imChanged();
}

void Stage::setLeft20Status(int status)
{
    if (status == Qt::Checked)
    {
        _is_20_done = true;
    }
    else _is_20_done = false;
    calculatePriority();
   // if (!fileload_status) emit imChanged();
}


int Stage::calculatePriority()
{
    int days_left = QDate::currentDate().daysTo(_finish_date);
    if ((days_left == 0)&(!_is_done))
    {
        int exp = _finish_date.daysTo(QDate::currentDate());
        qDebug() << "Этап " << _stage_name <<  " просрочен на " << exp << " дней";
        priority = 10;
    }
    else if ((days_left <= 10)&(!_is_10_done))
    {
        priority = 2;
    }
    else if ((days_left <= 20)&(!_is_20_done))
    {
        priority = 1;
    }
    else priority = 0;
    return priority;
}


void Stage::deleteStageRequestHandler()
{
    if (!fileload_status) emit this->deleteRequested();
}







