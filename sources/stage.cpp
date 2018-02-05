#include "../headers/stage.h"

//using namespace stage;
Stage::Stage(QObject *parent) : QObject(parent)
{

    _start_date = QDate(QDate::currentDate());
    _finish_date = QDate(QDate::currentDate().year(),12,31);
    //_finish_date= QDate(QDate::currentDate().year(),);
    _stage_name = QString("Этап без названия");

    _is_done = false;
    _is_20_done = false;
    _is_10_done = false;

    _priority = Normal;
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


bool Stage::setDoneStatus(int status)
{
    int days_left = QDate::currentDate().daysTo(_finish_date);
    if (((_is_20_done & _is_10_done) & (days_left <= 0)) | (fileload_status))
    {
        if (status == Qt::Checked)
        {
            _is_done = true;
        }
        else _is_done = false;
        return true;
        calculatePriority();
    }
    else
    {
     qDebug() << "Недопустимая попытка поменять статус DoneStatus этапа " << _stage_name;
     qDebug() << "(_is_20_done & _is_10_done):" << (_is_20_done & _is_10_done) << "    (days_left <= 0):" << (days_left <= 0);
     return false;
    }
}

bool Stage::setLeft10Status(int status)
{
    int days_left = QDate::currentDate().daysTo(_finish_date);
    if (((_is_20_done) & (days_left <= 10)) | (fileload_status))
    {
        if (status == Qt::Checked)
        {
             _is_10_done = true;
        }
        else
        {
            _is_done = false;
            _is_10_done = false;
        }
        return true;
        calculatePriority();
    }
    else
    {
        qDebug() << "Недопустимая попытка поменять статус 10_DoneStatus этапа " << _stage_name;
        qDebug() << "(_is_20_done):" << (_is_20_done & _is_10_done) << "    (days_left <= 10):" << (days_left <= 0);
        return false;
    }
  //  if (!fileload_status) emit stageChanged();

}

bool Stage::setLeft20Status(int status)
{
    int days_left = QDate::currentDate().daysTo(_finish_date);
    if ((days_left <= 20) | (fileload_status))
    {
        if (status == Qt::Checked)
        {
            _is_20_done = true;
        }
        else
        {
            _is_done = false;
            _is_10_done = false;
            _is_20_done = false;
        }
        calculatePriority();
        return true;
    }
    else
    {
        qDebug() << "Недопустимая попытка поменять статус 20_DoneStatus этапа " << _stage_name;
        qDebug() << "(days_left <= 20):" << (days_left <= 20);
        return false;
    }
}


void Stage::calculatePriority()
{
    int new_priority = 0;
    int days_left = QDate::currentDate().daysTo(_finish_date);

    if (days_left > 20) new_priority = Normal;
    if ((days_left <= 20)&(!_is_20_done)) new_priority = Overdude_20;
    if ((days_left <= 10)&(!_is_10_done)) new_priority = Overdude_10;
    if ((days_left < 0)&(!_is_done)) new_priority = Overdude;
    if ((days_left < 0)&(_is_done)) new_priority = Normal;



    if (new_priority != _priority)
    {
        _priority = new_priority;
       // if (!fileload_status) emit priorityChanged();
    }
   // /*DEBUG*/ _stage_name= (QString::number(_priority));    
}



void Stage::deleteStageRequestHandler()
{
    emit this->deleteRequested();
}







