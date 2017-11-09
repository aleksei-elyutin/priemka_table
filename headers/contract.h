#ifndef CONTRACT_H
#define CONTRACT_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QVector>
#include "headers/stage.h"
//#include "headers/database.h"

class Contract : public QObject {

    Q_OBJECT

private:

    //DataBase *_dataBase;
    QString _contract_name = "Контракт без названия";
    QVector <Stage *> _stages;
    //int _number;



public:
    /*explicit*/
    explicit Contract(QObject *parent = 0);
    /**
     * @brief setContractName Задать имя договора
     * @param name
     */
    void setContractName(QString name) {_contract_name = name;}

    /**
     * @brief getContractName Получить имя договора
     * @return QString Имя договора
     */
    QString getContractName() {return _contract_name;}

    /**
     * @brief pushStage Добавить существующий этап
     */
    void pushStage(Stage *stage);

    /**
     * @brief createStageСоздать новый этап
     * @return Указатель на созданный объект Stage
     */
    Stage *createStage();


    /**
     * @brief getNumStages Получить количество этапов
     * @return
     */
    int getNumStages();

    /**
     * @brief getStage Получить этап по номеру
     * @param stage_num
     * @return
     */
    Stage *getStage(int stage_num);

    /**
     * @brief deleteStage Удалить указатель на этап с номером stage_num и очистить память по нему
     * @param stage_num
     */
    void deleteStage(int stage_num);

    void deleteStageByDelRequest(); /*SLOT*/

    void deleteThisContract();


};

#endif // CONTRACT_H
