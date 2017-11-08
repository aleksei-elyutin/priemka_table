#ifndef CONTRACT_H
#define CONTRACT_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QVector>
#include "../headers/stage.h"

class Contract : public QObject
{
    Q_OBJECT
private:
    QString _contract_name = "";
    QVector <Stage*> _stages;
    //int _number;



public:
    /*explicit*/
    Contract(int number, QString name);
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
     * @brief pushStage Добавить этап
     */
    void pushStage(Stage *stage);

    /**
     * @brief getNumStages Получить количество этапов
     * @return
     */
    int getNumStages() {return _stages.size();}

    /**
     * @brief getStage Получить этап по номеру
     * @param stage_num
     * @return
     */
    Stage *getStage(int stage_num);

    int getNumber () ;


signals:

public slots:
};

#endif // TABLEENTRY_H
