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

void Contract::deleteStage(int stage_num)
{
    delete _stages[stage_num];
    _stages.remove(stage_num);
    _stages.squeeze();
}

int Contract::getNumber()
{

}

