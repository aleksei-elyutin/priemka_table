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
    int sz = _contracts_base.size();
    return sz;
}

Contract *DataBase::getContract(int contract_num)
{
    return _contracts_base.at(contract_num);
}

Contract *DataBase::createContract()
{
    Contract *ct = new Contract(this);
    pushContract(ct);
    connect(ct, &Contract::deleteMe, this, &DataBase::deleteContractByDelRequest);
    connect(ct, &Contract::imChanged, this, &DataBase::childChanged);
    emit base_changed();
    return ct;
}


bool DataBase::deleteContract(int contract_num)
{
    if ((contract_num>=0)&(contract_num < _contracts_base.size()))
    {
        _contracts_base.remove(contract_num);
        return true;
    }
    else
    {
        qDebug() << "Индекс вне границ массива";
        return false;
    }
}

/*SLOTS*/
void DataBase::deleteContractByDelRequest()
{
    int i = _contracts_base.indexOf(qobject_cast<Contract*>( sender()) );
    qDebug() << "Попытка удаления контракта номер" << i << this->getNumContracts()
             << " (имя: " << this->_contracts_base.at(i)->getContractName()  << " )";

    if (deleteContract(i)){

        delete sender();
        qDebug() << "Контракт удален.";
     }
     else
    {
        qDebug() << "Ошибка при удалении контракта";
    }

    emit base_changed();
    //_stages.squeeze();
}

void DataBase::childChanged()
{
    emit base_changed();
}

