 #include "../headers/contract.h"

Contract::Contract(QObject *parent) : QObject(parent)
{
    _priority = 0;
}

void Contract::setContractName(QString name)
{
    _contract_name = name;
    if (!fileload_status)  emit contractChanged();
}

Stage *Contract::createStage()
{
    Stage *st = new Stage(this);
    _stages.push_back(st);
    connect(st, &Stage::deleteRequested, this, &Contract::deleteStageRequestHandler);
    connect(st, &Stage::stageChanged, this, &Contract::stageChangeHandler);
    calculateContractPriority();
    if (!fileload_status) emit contractChanged();
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

void  Contract::calculateContractPriority()
{
    int new_priority = 0;
    int num_stages = _stages.size();
    for (int i=0; i< num_stages; i++)
    {
         new_priority += _stages.at(i)->getPriority();
    }
    if (new_priority != _priority)
    {
        _priority = new_priority;
        if (!fileload_status) emit contractChanged();
    }
}


/*bool Contract::lessThan( Contract* s1, Contract* s2 )
{
    // qDebug() << "Вызван оператор сравнения";
    return s1->calculateContractPriority() > s2->calculateContractPriority();

}*/

void Contract::deleteStageRequestHandler()/*SLOT*/
{

    int i = _stages.indexOf(qobject_cast<Stage*>( sender()) );
    if (deleteStage(i))
    {
        delete sender();
    }
    else
    {
        qDebug() << "Ошибка при удалении этапа";
    }
   calculateContractPriority();
   if (!fileload_status)  emit contractChanged();
}

  /*SLOTS*/
void Contract::deleteContractRequestHandler()
{
   if (!fileload_status) emit this->deleteRequested();
}

void Contract::stageChangeHandler()
{
    calculateContractPriority();
}


