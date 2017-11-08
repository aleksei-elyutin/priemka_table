#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <contract.h>

class DataBase : public QObject
{
    Q_OBJECT
private:
     QVector <Contract*> _contracts_base;

public:
    explicit DataBase(QObject *parent = 0);

     void pushContract(Stage *stage);

     /**
      * @brief getNumStages Получить количество э
      * @return
      */
     int getNumContracts();

     /**
      * @brief getStage Получить указатель на экземпляр контракта по номеру
      * @param contract_num
      * @return
      */
     Contract *getContract(int contract_num);

     /**
      * @brief deleteContract Удалить указатель контракт с номером contract_num и очистиь память по нему
      * @param contract_num
      */

     void deleteContract(int contract_num);


     /**Не реализовано*/
     //Методы для кодирования записи в файл и декодирования записи из файла
     //codeBase();
     //decodeBase();


signals:

public slots:
};

#endif // DATABASE_H
