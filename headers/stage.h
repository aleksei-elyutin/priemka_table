#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QDate>
#include <QVector>
#include <QDebug>


class Stage: public QObject {

    Q_OBJECT
private:
    QDate _start_date;
    QDate _finish_date;
    QString _stage_name = QString("Этап без названия");
    bool _is_done = false;



public:
    Stage( QDate start_date = QDate(1,1,2017), QDate finish_date= QDate(1,31,2017));

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
    void setStageName(QString name) {_stage_name = name;} //inline impl
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

    void setStatusDone() { _is_done = true;} //inline impl

    void setStatusUnDone() { _is_done = false;} //inline impl
};


#endif // STAGE_H
