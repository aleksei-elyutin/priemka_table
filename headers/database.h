#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QVector>
#include <QFile>
#include "headers/contract.h"

class DataBase : public QObject {

    Q_OBJECT

private:
     QVector <Contract *> _contracts_base;
     QDate _lastInFile;
     QFile *_file;

     bool fileload_status = false; //Флаг - Производится чтение из файла

     struct stage_structure{
         qint64 start_date_julian;
         qint64 finish_date_julian;
         char _20_done;
         char _10_done;
         char _done;
     };


public:
    explicit DataBase(QObject *parent = 0);

     void writeToFile();
     void readFromFile();
     void setFile(QFile *file) {_file=file;}


     void pushContract(Contract *contract);

     /**
      * @brief getNumContracts Получить количество контрактов
      * @return
      */
     int getNumContracts();

     /**
      * @brief getStage Получить указатель на экземпляр контракта по номеру
      * @param contract_num
      * @return
      */
     Contract *getContract(int contract_num);

     Contract *createContract();

     /**
      * @brief deleteContract Удалить указатель контракт с номером contract_num и очистиь память по нему
      * @param contract_num
      */

     bool deleteContract(int contract_num);



public slots:
     void deleteContractByDelRequest();/*SLOT*/
     void childChanged(); /*SLOT*/


signals:
     void base_changed();

};

#endif // DATABASE_H
