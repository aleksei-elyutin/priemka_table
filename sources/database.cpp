#include "./headers/database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

void DataBase::pushContract(Contract *contract)
{
    _contracts_base.push_back(contract);
    emit base_changed();
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
    _contracts_base.push_back(ct);
    connect(ct, &Contract::deleteMe, this, &DataBase::deleteContractByDelRequest);
    connect(ct, &Contract::imChanged, this, &DataBase::childChanged);
    qSort(_contracts_base.begin(), _contracts_base.end(), Contract::lessThan);
    emit base_changed();
    qDebug() << "Сигнал: база изменена createContract";
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

void DataBase::writeToFile(QFile *file)
{
    if(!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка открытия файла для записи";
    }

    /**Запись заголовка базы **/
    /*TODO : добавить magicword */
    qint64 creation_date_Julian = QDate::currentDate().toJulianDay(); //Дата создания
    int creation_time_msecs = QTime::currentTime().msecsSinceStartOfDay(); //Время создания
    file->write((const char*)&creation_date_Julian,sizeof(qint64)); //Запись даты создания
    file->write((const char*)&creation_time_msecs,sizeof(int)); //Запись времени создания
    int size = _contracts_base.size();
    file->write((const char*)&size,sizeof(int)); ,,


    file->close();

}

void DataBase::readFromFile(QFile *file)
{
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия файла для чтения";
    }

    /**Чтение заголовка базы **/
    /*TODO : добавить magicword */
    qint64 creation_date_Julian;
    int creation_time_msecs;
    file->read((char*)&creation_date_Julian,sizeof(qint64)); //Чтение даты создания
    file->read((char*)&creation_time_msecs,sizeof(int)); //Чтение времени создания
    int base_size;
    file->read((char*)&size,sizeof(int)); //Чтение размеры базы (количество контрактов)

    for (int i=0; i< size; i++)
    {

        int contract_size;
        file->read((char*)&size,sizeof(int)); //Чтение размера i-го контракта (количество этапов)
        Contract* tmp_contract = createContract();

            tmp_contract->createStage()
    }

    file->close();

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
    qSort(_contracts_base.begin(), _contracts_base.end(), Contract::lessThan);
    emit base_changed();
    qDebug() << "Сигнал: база изменена deleteContractByDelRequest";
    //_stages.squeeze();
}


void DataBase::childChanged()
{
     qDebug() << "Сигнал: база изменена childChanged";
    qSort(_contracts_base.begin(), _contracts_base.end(), Contract::lessThan);
    emit base_changed();
}

