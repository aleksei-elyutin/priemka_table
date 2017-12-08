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
    QString _stage_name;
    bool _is_done = false;
    bool _is_20_done = false;
    bool _is_10_done = false;
    int priority;
    bool fileload_status = false;

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


    bool getDoneStatus() {return _is_done;} //inline impl

    bool getLeft10DoneStatus() {return _is_10_done;} //inline impl

    bool getLeft20DoneStatus() {return _is_20_done;} //inline impl



    void setDoneStatus(int status); //inline impl

    void setLeft10Status(int status); //inline impl

    void setLeft20Status(int status); //inline impl


    void setFileloadStatus(bool status) {fileload_status = status;}






    int calculatePriority();


    int getDaysToNearestUncheckedControlPoint();

public slots:
    /**
     * @brief deleteRequest Обработка запрос на удаление к этому этапу от ГУИ
     */
    void deleteStageRequestHandler();

signals:
    void deleteRequested();
    void stageChanged();

};


#endif // STAGE_H
