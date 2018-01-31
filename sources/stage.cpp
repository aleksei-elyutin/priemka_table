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

    _priority = 0;
}

void Stage::setStartDate(QDate startdate)
{
    _start_date = startdate;
    if (!fileload_status) emit stageChanged();
    calculatePriority();

}
void Stage::setFinishDate(QDate finishdate)
{
    _finish_date=finishdate;
    if (!fileload_status) emit stageChanged();
    calculatePriority();
}

void Stage::setStageName(QString name)
{
    _stage_name = name;
    if (!fileload_status) emit stageChanged();
}

void Stage::setDoneStatus(int status)
{
    if (status == Qt::Checked)
    {
    _is_done = true;
    }
    else _is_done = false;
    if (!fileload_status) emit stageChanged();
    calculatePriority();
}

void Stage::setLeft10Status(int status)
{
    if (status == Qt::Checked)
    {
         _is_10_done = true;
    }
    else _is_10_done = false;
    if (!fileload_status) emit stageChanged();
    calculatePriority();
}

void Stage::setLeft20Status(int status)
{
    if (status == Qt::Checked)
    {
        _is_20_done = true;
    }
    else _is_20_done = false;
    if (!fileload_status) emit stageChanged();
    calculatePriority();
}


void Stage::calculatePriority()
{
    int new_priority;
    int days_left = QDate::currentDate().daysTo(_finish_date);
    if ((days_left == 0)&(!_is_done))
    {
        int exp = _finish_date.daysTo(QDate::currentDate());
        qDebug() << "Этап " << _stage_name <<  " просрочен на " << exp << " дней";
        new_priority = 10;
    }
    else if ((days_left <= 10)&(!_is_10_done)&(!_is_20_done))
    {
        new_priority = 2;
    }
    else if ((days_left <= 20)&(!_is_20_done))
    {
        new_priority = 1;
    }
    else new_priority = 0;

    _priority = new_priority;
    if (!fileload_status) emit priorityChanged();
}



void Stage::deleteStageRequestHandler()
{
    if (!fileload_status) emit this->deleteRequested();
}







