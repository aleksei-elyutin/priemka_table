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
  //  Q_ENUM(Priority)

private:

    QString _contract_name;
    QVector <Stage *> _stages;

    int _priority;
    bool fileload_status = false;

   // enum Priority{Normal, Overdude_20, Overdude_10, Overdude};

public:

    explicit Contract(QObject *parent = 0);

    void setContractName(QString name);

    QString getContractName() {return _contract_name;}

    Stage *createStage();

    int getNumStages();

    Stage *getStage(int stage_num);

    bool deleteStage(int stage_num);

    void deleteThisContract();

    void setFileloadStatus(bool status) {fileload_status = status;}

    int getPriority();

    int getDaysLeft();

public slots:

    void deleteContractRequestHandler();
    void deleteStageRequestHandler(); /*SLOT*/
   // void stageChangeHandler(); /*SLOT*/

signals:
    void deleteRequested();
    void contractChanged();
    void contractPriorityChanged();



};

#endif // CONTRACT_H
