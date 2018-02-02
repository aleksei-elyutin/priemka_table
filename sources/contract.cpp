 #include "../headers/contract.h"

Contract::Contract(QObject *parent) : QObject(parent)
{
    _contract_name= "Контракт без названия";
    _priority = Stage::Normal;
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
    connect(st, &Stage::priorityChanged, this, &Contract::calculateContractPriority);
    st->calculatePriority();
    calculateContractPriority();
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
    calculateContractPriority();
}

void  Contract::calculateContractPriority()
{
    int new_priority = Stage::Normal;
    int num_stages = _stages.size();
    for (int i=0; i< num_stages; i++)
    {
        if  (_stages.at(i)->getPriority() > new_priority)
        new_priority = _stages.at(i)->getPriority();
    }
    if (_priority != new_priority)
    {
        _priority = new_priority;
    }
 // /*DEBUG*/  _contract_name =  (QString::number(_priority));
}

void Contract::deleteStageRequestHandler()
{
    /** Обработчик сигнала от Stage */
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
}


void Contract::deleteContractRequestHandler()
{
   /** Обработчик события от GUI - Contractwidget */
   //if (!fileload_status)
    int num_stages = _stages.size();
    for (int i=0; i< num_stages; i++)
    {
        delete _stages.at(i);
    }
    _stages.clear();
    emit this->deleteRequested();
}






