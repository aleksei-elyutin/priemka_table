#include "../headers/contract.h"

Contract::Contract(int number,  QString name)
{
    //_number = number;
    _contract_name = name;
}

void Contract::pushStage(Stage *stage)
{
    _stages.push_back(stage);
}

Stage *Contract::getStage(int stage_num)
{
    if ((stage_num > _stages.size())|(stage_num<0))
    {
        return _stages.last();
    }
    else return _stages[stage_num];
}

int Contract::getNumber()
{
    int sz = _stages.size();
    return  sz;
}

