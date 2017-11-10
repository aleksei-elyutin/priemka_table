#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QDate>
#include <QVector>
#include <QDebug>
//#include "headers/contract.h"


class Stage: public QObject {

    Q_OBJECT
private:
    QDate _start_date;
    QDate _finish_date;
    QString _stage_name = QString("Этап без названия");
    bool _is_done = false;

public:
    /*explicit*/ Stage(QObject *parent = 0);

    /** Public nethods */
    /**
     * @brief setStartDate Установить дату начала заказа
     * @param startdate
     */
    void setStartDate(QDate startdate);

    /**
     * @brief getStartDate Получить дату начала заказа
     * @return
     */
    QDate getStartDate () {return _start_date;} //inline impl
    /**
     * @brief getNumFinishDates Получить количество окончательных сроков
     * @return
     */
    void setFinishDate (QDate finishdate);
    /**
     * @brief getFinishDate Получить окончательную дату по номеру
     * @return
     */
    QDate getFinishDate () {return _finish_date;} //inline impl

    /**
     * @brief setContractName Задать название этапа
     * @param name
     */
    void setStageName(QString name); //inline impl
    /**
     * @brief getContractName Получить название этапа
     * @return
     */
    QString getStageName() {return _stage_name;} //inline impl

    /**
     * @brief getDoneStatus Получить статус исполнения этапа
     * @return
     */
    bool getDoneStatus() {return _is_done;} //inline impl

    /**
     * @brief setStatusDone Установить статус исполнения ятапа в "Выполнено"
     */
    void setStatusDone() { _is_done = true;} //inline impl

    /**
     * @brief setStatusUnDone Установить статус исполнения этапа в "Невыполнено"
     */
    void setStatusUnDone() { _is_done = false;} //inline impl

public slots:
    /**
     * @brief deleteRequest Обработка запрос на удаление к этому этапу от ГУИ
     */
    void deleteRequest();

signals:
    void deleteMe();
    void imChanged();

};


#endif // STAGE_H
