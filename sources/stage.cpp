#include "../headers/stage.h"

//using namespace stage;
Stage::Stage(QObject *parent) : QObject(parent)
{


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
    emit imChanged();

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
    emit imChanged();
}

void Stage::setStageName(QString name)
{
    _stage_name = name;
    emit imChanged();
}

void Stage::deleteRequest()
{
    emit this->deleteMe();
}







