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
    QString _stage_name;
    bool _is_done = false;
    bool _is_20_done = false;
    bool _is_10_done = false;
    int priority;
    int _days_to_checkpoint;
    bool fileload_status = false;

public:
    /*explicit*/ Stage(QObject *parent = 0);


    void setStartDate(QDate startdate);

    QDate getStartDate () {return _start_date;} //inline impl


    void setFinishDate (QDate finishdate);

    QDate getFinishDate () {return _finish_date;} //inline impl


    void setStageName(QString name);

    QString getStageName() {return _stage_name;} //inline impl


    void setDoneStatus(int status);

    bool getDoneStatus() {return _is_done;} //inline impl


    void setLeft10Status(int status);

    bool getLeft10DoneStatus() {return _is_10_done;} //inline impl


    void setLeft20Status(int status);

    bool getLeft20DoneStatus() {return _is_20_done;} //inline impl



    void setFileloadStatus(bool status) {fileload_status = status;} //inline impl


    int calculatePriority();


    int calculateDaysToNearestUncheckedCheckPoint();

public slots:

    void deleteStageRequestHandler();

signals:

    void deleteRequested();
    void stageChanged();

};


#endif // STAGE_H
