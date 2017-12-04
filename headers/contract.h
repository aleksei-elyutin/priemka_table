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

    QString _contract_name = "Контракт без названия";
    QVector <Stage *> _stages;

    int _priority = 0;
    bool fileload_status = false;



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
    bool deleteStage(int stage_num);

    void deleteThisContract();

    int calculateContractPriority();

   // static bool lessThan( Contract* s1, Contract* s2 );

    void setFileloadStatus(bool status) {fileload_status = status;}



//    bool operator < (Contract& a);


public slots:

    /**
     * @brief deleteRequest Обработка запрос на удаление к этому этапу от ГУИ
     */
    void deleteContractRequestHandler();
    void deleteStageByDelRequest(); /*SLOT*/
    void childChanged(); /*SLOT*/

signals:
    void deleteRequested();
    void imChanged();



};

#endif // CONTRACT_H
