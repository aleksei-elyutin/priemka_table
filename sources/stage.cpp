#include "../headers/stage.h"

//using namespace stage;
Stage::Stage(QObject *parent) : QObject(parent)
{

    _start_date = QDate(QDate::currentDate());
    _finish_date = QDate(QDate::currentDate().year(),12,31);

    _stage_name = QString("Этап без названия");

    _is_done = false;
    _is_20_done = false;
    _is_10_done = false;

    priority = calculatePriority();
}

void Stage::setStartDate(QDate startdate)
{
    _start_date = startdate;
    if (!fileload_status)  emit stageChanged();

}
void Stage::setFinishDate(QDate finishdate)
{
    _finish_date=finishdate;
    if (!fileload_status) emit stageChanged();
}

void Stage::setStageName(QString name)
{
    _stage_name = name;
   if (!fileload_status)  emit stageChanged();
}

void Stage::setDoneStatus(int status)
{
    if (status == Qt::Checked)
    {
    _is_done = true;
    }
    else _is_done = false;
    calculatePriority();
  //  if (!fileload_status) emit stageChanged();
}

void Stage::setLeft10Status(int status)
{
    if (status == Qt::Checked)
    {
         _is_10_done = true;
    }
    else _is_10_done = false;
    calculatePriority();
 //   if (!fileload_status) emit stageChanged();
}

void Stage::setLeft20Status(int status)
{
    if (status == Qt::Checked)
    {
        _is_20_done = true;
    }
    else _is_20_done = false;
    calculatePriority();
  //  if (!fileload_status) emit stageChanged();
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

/*int Stage::calculateDaysToNearestUncheckedCheckPoint()
{
   QDate checkpoint_10 = _finish_date.fromJulianDay(QDate::toJulianDay()-10);
   QDate checkpoint_20 = _finish_date.fromJulianDay(QDate::toJulianDay()-20);

    if (!_is_20_done)
    {
        _days_to_checkpoint = QDate::currentDate().daysTo(checkpoint_20);
    }

    else if (!_is_10_done)
    {
        _days_to_checkpoint = QDate::currentDate().daysTo(checkpoint_10);
    }

    else if (!_is_done)
    {
        _days_to_checkpoint = QDate::currentDate().daysTo(_finish_date);
    }

    return _days_to_checkpoint;
}
*/

void Stage::deleteStageRequestHandler()
{
    if (!fileload_status) emit this->deleteRequested();
}







