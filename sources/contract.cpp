#include "../headers/contract.h"

Contract::Contract(QObject *parent) : QObject(parent)
{

}

void Contract::pushStage(Stage *stage)
{
    _stages.push_back(stage);
}

Stage *Contract::createStage()
{
    Stage *st = new Stage(this);
    pushStage(st);
    connect(st, &Stage::deleteMe, this, &Contract::deleteStageByDelRequest);
    connect(st, &Stage::imChanged, this, &Contract::childChanged);
    //calculateContractPriority();
    emit imChanged();
    return st;
}

int Contract::getNumStages()
{
    int sz = _stages.size();
    return  sz;
}

Stage *Contract::getStage(int stage_num)
{
    if ((stage_num > _stages.size())|(stage_num<0))
    {
        return _stages.last();
    }
    else return _stages[stage_num];
}

bool Contract::deleteStage(int stage_num)
{
    if ((stage_num>=0)&(stage_num < _stages.size()))
    {
        _stages.remove(stage_num);
        return true;
    }
    else
    {
        qDebug() << "Индекс вне границ массива";
        return false;
    }
}

int  Contract::calculateContractPriority()
{
    _priority = 0;
    int num_stages = _stages.size();
    for (int i=0; i< num_stages; i++)
    {
         _priority += _stages.at(i)->calculatePriority();
         qDebug() << "Рассчитан приоретет контракта " << this->getContractName() << " : " << _priority;

    }
    return _priority;
}

//bool Contract::operator<(Contract& a)
//{
//    qDebug() << "Вызван оператор сравнения";
//    return a.calculateContractPriority() < this->calculateContractPriority();
//}
bool Contract::lessThan( Contract* s1, Contract* s2 )
{
     qDebug() << "Вызван оператор сравнения";
    return s1->calculateContractPriority() > s2->calculateContractPriority();

}



void Contract::deleteStageByDelRequest()/*SLOT*/
{

    int i = _stages.indexOf(qobject_cast<Stage*>( sender()) );
    qDebug() << "Попытка удаления этапа номер" << i << " из " << this->getNumStages() << " (имя: " << this->getStage(i)->getStageName() << ") контракта " << this->getContractName() ;

    if (deleteStage(i)){

        delete sender();
        qDebug() << "Этап удален.";
     }
     else
    {
        qDebug() << "Ошибка при удалении этапа";
    }
    //calculateContractPriority();
    emit imChanged();
    //_stages.squeeze();
}

  /*SLOTS*/
void Contract::deleteRequest()
{
    emit this->deleteMe();
}

void Contract::childChanged()
{
    calculateContractPriority();
    emit imChanged();
}


