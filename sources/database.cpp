#include "./headers/database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

void DataBase::pushContract(Contract *contract)
{
    _contracts_base.push_back(contract);
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

Contract *DataBase::createContract()
{
    Contract *ct = new Contract(this);
    ct->setParentBase(this);
    return ct;
}

void DataBase::deleteContract(Contract *contract)
{
    _contracts_base.remove(_contracts_base.indexOf(contract));
    delete contract;
   // _contracts_base.squeeze();
}

