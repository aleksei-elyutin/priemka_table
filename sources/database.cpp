#include "./headers/database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

void DataBase::pushContract(Contract *contract)
{
    _contracts_base.push_back(contract);
    if (!fileload_status) emit base_changed();

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
    if (!fileload_status) emit base_changed();
   // qDebug() << "Сигнал: база изменена createContract";
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

void DataBase::writeToFile()
{
    if(!_file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка открытия файла для записи";
    }

    /**Запись заголовка базы **/
    /*TODO : добавить magicword */
    qint64 creation_date_Julian = QDate::currentDate().toJulianDay(); //Дата создания
    int creation_time_msecs = QTime::currentTime().msecsSinceStartOfDay(); //Время создания
    _file->write((const char*)&creation_date_Julian,sizeof(qint64)); //Запись даты создания
    _file->write((const char*)&creation_time_msecs,sizeof(int)); //Запись времени создания
    int base_size = _contracts_base.size();
    _file->write((const char*)&base_size,sizeof(int)); //Запись размера базы (количество контрактов)

    for (int c  =0; c < base_size; c++)
    {
        Contract* tmp_contract_pointer = _contracts_base.at(c);
        QByteArray contract_text =tmp_contract_pointer->getContractName().toLocal8Bit();
        int contract_name_length = contract_text.size()+1;
        _file->write((char*)&contract_name_length,sizeof(int)); //Запись размера имени контракта

        char *contract_name = new char[contract_name_length];
        strcpy(contract_name, contract_text.data());
        _file->write((const char*)contract_name,contract_name_length);
        delete [] contract_name;
        contract_name = NULL;

        int contract_size=tmp_contract_pointer->getNumStages();
        _file->write((char*)&contract_size,sizeof(int)); //Запись размера i-го контракта (количество этапов)

        for (int st=0; st<contract_size; st++)
        {
            Stage* tmp_stage_pointer = tmp_contract_pointer->getStage(st);
            QByteArray stage_text =tmp_stage_pointer->getStageName().toLocal8Bit();
            int stage_name_length = stage_text.size()+1;
            _file->write((char*)&stage_name_length,sizeof(int)); //Запись размера имени контракта

            char *stage_name = new char[stage_name_length];
            strcpy(stage_name, stage_text.data());
            _file->write((const char*)stage_name,stage_name_length);
            delete [] stage_name;
            stage_name = NULL;

            stage_structure ss;
            ss.start_date_julian = tmp_stage_pointer->getStartDate().toJulianDay();
            ss.finish_date_julian = tmp_stage_pointer->getFinishDate().toJulianDay();

            if  (tmp_stage_pointer->getLeft10DoneStatus()) ss._10_done = Qt::Checked; else ss._10_done = Qt::Unchecked;
            if  (tmp_stage_pointer->getLeft20DoneStatus())  ss._20_done = Qt::Checked; else ss._20_done = Qt::Unchecked;
            if  (tmp_stage_pointer->getDoneStatus()) ss._done = Qt::Checked; else ss._done = Qt::Unchecked;
            _file->write((char*)&ss,sizeof(stage_structure));

        }
    }


    _file->close();

}

void DataBase::readFromFile()
{
    if(!_file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия файла для чтения";
    }
    fileload_status = true;

    /**Чтение заголовка базы **/
    /*TODO : добавить magicword */
    qint64 creation_date_Julian;
    int creation_time_msecs;
    _file->read((char*)&creation_date_Julian,sizeof(qint64)); //Чтение даты создания
   qDebug() << QDate::fromJulianDay(creation_date_Julian);
    _file->read((char*)&creation_time_msecs,sizeof(int)); //Чтение времени создания
   qDebug() << QTime::fromMSecsSinceStartOfDay(creation_time_msecs);
    int base_size;
    _file->read((char*)&base_size,sizeof(int)); //Чтение размеры базы (количество контрактов)

    for (int c  =0; c < base_size; c++)
    {

        Contract* tmp_contract_pointer = createContract();
        tmp_contract_pointer->setFileloadStatus(true);
        int contract_name_length = 0;
        _file->read((char*)&contract_name_length,sizeof(int)); //Чтение размера имени контракта
        char *contract_name = new char[contract_name_length];
        _file->read((char*)contract_name,contract_name_length); //Чтение имени контракта
        QByteArray contract_text(contract_name, contract_name_length);
       // strcpy(contract_text.data(),contract_name);
        tmp_contract_pointer->setContractName(QString::fromLocal8Bit(contract_text)); //Установка имени контракта
        delete [] contract_name;
        contract_name = NULL;

        int contract_size=0;
        _file->read((char*)&contract_size,sizeof(int)); //Чтение размера i-го контракта (количество этапов)

            for (int st=0; st<contract_size; st++)
            {
                Stage* tmp_stage_pointer = tmp_contract_pointer->createStage();
                tmp_stage_pointer->setFileloadStatus(true);
                int stage_name_length = 0;
                _file->read((char*)&stage_name_length,sizeof(int)); //Чтение размера имени этапа
                char *stage_name = new char[stage_name_length];
                _file->read((char*)stage_name,stage_name_length); //Чтение имени этапа
                QByteArray stage_text(stage_name, stage_name_length);
                //strcpy(stage_text.data(),stage_name);
                tmp_stage_pointer->setStageName(QString::fromLocal8Bit(stage_text)); //Установка имени этапа
                delete [] stage_name;
                stage_name = NULL;

                stage_structure ss;
                _file->read((char*)&ss,sizeof(stage_structure));
                tmp_stage_pointer->setStartDate( QDate::fromJulianDay(ss.start_date_julian));
                tmp_stage_pointer->setFinishDate( QDate::fromJulianDay(ss.finish_date_julian));
                tmp_stage_pointer->setLeft10Status(ss._10_done);
                tmp_stage_pointer->setLeft20Status(ss._20_done);
                tmp_stage_pointer->setDoneStatus(ss._done);
                tmp_stage_pointer->setFileloadStatus(false);
            }
          tmp_contract_pointer->setFileloadStatus(false);
    }

    _file->close();
    fileload_status = false;
    base_changed();

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

    if (!fileload_status) emit base_changed();
    qDebug() << "Сигнал: база изменена deleteContractByDelRequest";
    //_stages.squeeze();
}


void DataBase::childChanged()
{
    qSort(_contracts_base.begin(), _contracts_base.end(), Contract::lessThan);
    if (!fileload_status) emit base_changed();

}

