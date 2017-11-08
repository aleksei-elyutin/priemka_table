#include "./headers/database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

void DataBase::pushContract(Stage *stage)
{
    _contracts_base.push_back(stage);
}


int DataBase::getNumContracts()
{
    int sz = _stages.size();
    return sz;
}

Contract *DataBase::getContract(int contract_num)
{
    return _contracts_base.at(contract_num);
}

void DataBase::deleteContract(int contract_num)
{
    delete _contracts_base[contract_num];
    _contracts_base.remove(contract_num);
    _contracts_base.squeeze();
}

