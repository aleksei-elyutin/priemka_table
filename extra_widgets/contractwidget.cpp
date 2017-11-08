#include "contractwidget.h"

ContractWidget::ContractWidget(QWidget *parent, Contract* contract) : QFrame(parent)
{
//    hLayout = new QHBoxLayout();
//    hLayout->setSpacing(0);
//    hLayout->setMargin(0);

    vLayout = new QVBoxLayout();
    vLayout->setSpacing(3);
    vLayout->setMargin(3);
   // setStyleSheet("border: 2px solid grey; background-color: rgb(180, 180, 180); ");



    /**  Кнопка "Изменить..." **/


//    _dock = new QWidget(this);
//    header = new MonHeaderWidget(_dock);


//    num = new QLabel(QString::number(contract->getNumber()),this);
//   // num->setText(QString("1"));
//    num->setStyleSheet("background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
//    name = new QLabel(contract->getContractName(),this);
//    name->setStyleSheet("background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
//    //name->setText(QString("Name"));


//    vLayout->addWidget(header);

    int num_stages = contract->getNumStages();
    for (int i=0; i< num_stages; i++)
    {
         StageProgressWidget *tmp_stage_widget = new StageProgressWidget(this,contract->getStage(i));
         _stages_widgets.push_back(tmp_stage_widget);
         vLayout->addWidget(_stages_widgets.at(i));
         //tmp_stage_widget->show();
    }
    _edit_button = new QPushButton (QString("Добавить этап..."),this);
    vLayout->addWidget(_edit_button);
//    _dock->setLayout(vLayout);


//    hLayout->addWidget(num);
//    hLayout->addWidget(name);
//    hLayout->addWidget(_dock);
    setLayout(vLayout);

}


