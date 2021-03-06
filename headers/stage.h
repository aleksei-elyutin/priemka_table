#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QDate>
#include <QVector>
#include <QDebug>


class Stage: public QObject {

    Q_OBJECT
    //Q_ENUM(Priority)

private:
    QDate _start_date;
    QDate _finish_date;
    QString _stage_name;
    bool _is_done = false;
    bool _is_20_done = false;
    bool _is_10_done = false;
    int _priority;
    int _days_to_checkpoint;
    bool fileload_status = false;



public:
    /*explicit*/ Stage(QObject *parent = 0);

    enum Priority{Normal, Overdude_20, Overdude_10, Overdude};

    void setStartDate(QDate startdate);

    QDate getStartDate () {return _start_date;} //inline impl


    void setFinishDate (QDate finishdate);

    QDate getFinishDate () {return _finish_date;} //inline impl


    void setStageName(QString name);
    QString getStageName() {return _stage_name;} //inline impl


    bool setDoneStatus(int status);
    bool getDoneStatus() {return _is_done;} //inline impl


    bool setLeft10Status(int status);
    bool getLeft10DoneStatus() {return _is_10_done;} //inline impl


    bool setLeft20Status(int status);
    bool getLeft20DoneStatus() {return _is_20_done;} //inline impl



    void setFileloadStatus(bool status) {fileload_status = status;} //inline impl


    void calculatePriority();


    int getPriority() {return _priority;}

public slots:

    void deleteStageRequestHandler();

signals:

    void deleteRequested();
    void stageChanged();
    void priorityChanged();

};


#endif // STAGE_H
