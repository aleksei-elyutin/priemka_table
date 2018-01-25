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

     QString secure_hash;

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

     bool getFileloadStatus() {return fileload_status;}

     int getNumContracts();

     Contract *getContract(int contract_num);

     Contract *createContract();


     bool deleteContract(int contract_num);

     void purgeBase();

     QString getSecureHash() {return secure_hash;}
     void setSecureHash(QString sh) {secure_hash = sh;}



public slots:
     void deleteContractRequestHandler();/*SLOT*/
     void childChanged(); /*SLOT*/


signals:
     void baseLoaded();
     void baseChanged();

};

#endif // DATABASE_H
