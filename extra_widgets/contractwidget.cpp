#include "contractwidget.h"

ContractWidget::ContractWidget(QWidget *parent) : QWidget(parent)
{
    /*** widget stylesheet **/
   // setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(255, 255, 255, 255); background-color: rgb(20, 20, 20);");

     main_layout = new QHBoxLayout (this);

     main_layout->setStretch(0,0);
     main_layout->setStretch(1,0);
     main_layout->setStretch(2,1);
     main_layout->setSpacing(3);

     num = new QLCDNumber(this);
     num->setObjectName("number");
     /*Стиль номера*/
//     num->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 0px; "
//                        "color: rgb(255, 255, 255); border: 0px solid black;");
     num->setMinimumWidth(50);
     num->setMaximumWidth(50);
     num->setMinimumHeight(50);
     //num->setMaximumHeight(50);

     main_layout->addWidget(num);

     name = new QLabel(this); // \n

     /*Стиль названия*/
//     name->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 0px;"
//                         "color: rgb(255, 255, 255); border: 0px solid black;");
     //name->setFont(QFont("Times", 14, QFont::Normal));
     name->setWordWrap(true);
     name->setMinimumWidth(250);
     name->setMaximumWidth(250);
     name->setMinimumHeight(50);
     name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
     main_layout->addWidget(name);


    stages_box = new QWidget(this);
//    stages_box->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px;"
//                              "color: rgb(255, 255, 255); border: 0px solid black;");
    stages_box_layout = new QVBoxLayout(stages_box);
    stages_box_layout->setSpacing(0);
    stages_box_layout->setMargin(0);


    /*Кнопки добавить, изменить и удалить*/
    button_box = new QWidget(this);
    button_box->setMinimumHeight(30);
    button_box->setMaximumHeight(30);

    /*Стиль виджета с кнопками и названием*/
//    button_box->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px;"
//                              "color: rgb(255, 255, 255); border: 0px solid black;");

    button_box_layout = new QHBoxLayout(button_box);
    button_box_layout->setMargin(0);
    button_box_layout->setSpacing(3);

    QSpacerItem *hspacer = new QSpacerItem(50,30,QSizePolicy::Expanding,QSizePolicy::Expanding);
    button_box_layout->addItem(hspacer);

    add_stage_button = new QPushButton (QString("+"),this);
//    add_stage_button->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px;"
//                                  "color: rgb(255, 255, 255); border: 0px solid black;");
    add_stage_button->setMinimumHeight(30);
    add_stage_button->setMaximumHeight(30);
    add_stage_button->setMinimumWidth(30);
    add_stage_button->setMaximumWidth(30);
    button_box_layout->addWidget(add_stage_button);

    setup_contract_button = new QPushButton (QString("..."),this);
//    setup_contract_button->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px;"
//                              "color: rgb(255, 255, 255); border: 0px solid black;");
    setup_contract_button->setMinimumHeight(30);
    setup_contract_button->setMaximumHeight(30);
    setup_contract_button->setMinimumWidth(30);
    setup_contract_button->setMaximumWidth(30);
    button_box_layout->addWidget(setup_contract_button);


    delete_contract_button = new QPushButton (QString("X"),this);
//    delete_contract_button->setStyleSheet("text-align: middle; background-color: rgb(50, 50, 50); width: 10px;"
//                              "color: rgb(255, 255, 255); border: 0px solid black;");
    delete_contract_button->setMinimumHeight(30);
    delete_contract_button->setMaximumHeight(30);
    delete_contract_button->setMinimumWidth(30);
    delete_contract_button->setMaximumWidth(30);


    button_box_layout->addWidget(delete_contract_button);

    stages_box_layout->addWidget(button_box);
    /********/


    stages_box_layout->setSpacing(3);
    main_layout->addWidget(stages_box);

}


void ContractWidget::setupContract()
{
    contractRedactorDialog *dial = new contractRedactorDialog (0);
    dial->linkContract(_contract);
    dial->draw();
    dial->show();
    connect(dial, &contractRedactorDialog::accepted, _contract, &Contract::imChanged);

}

void ContractWidget::setContract(Contract *contract)
{
    _contract = contract;
    name->setText(_contract->getContractName());
    connect(add_stage_button, &QPushButton::clicked, this, &ContractWidget::createStageWidgetRequestHandler);
    connect(setup_contract_button, &QPushButton::clicked, this, &ContractWidget::setupContract);
    connect(delete_contract_button, &QPushButton::clicked, this, &ContractWidget::showDeleteDialog);
    reDrawAll();

}

void ContractWidget::reDrawAll()
{
    int number_of_layout_entries = stages_box_layout->count();
    if (number_of_layout_entries > 1) clearContractWidget();
    if (number_of_layout_entries < 1) qDebug() << "Some shit happened... No button 'add stage' ";

    int num_stages = _contract->getNumStages();
    for (int i=0; i< num_stages; i++)
    {
         addStageWidget(_contract->getStage(i));
    }

}

void ContractWidget::clearContractWidget()
{
    int number_of_layout_entries = stages_box_layout->count();

        for (int i = number_of_layout_entries-2; i>=0; i--)
        {
            delete stages_box_layout->itemAt(i)->widget();
        }
}

void ContractWidget::createStageWidgetRequestHandler()
{
    Stage* new_stage = _contract->createStage();
    addStageWidget(new_stage);
}

void ContractWidget::deleteStageWidgetRequestHandler()
{
    delete sender();
    //Добавить сигнал о необходимости пересчета приоритета
}



void ContractWidget::addStageWidget(Stage *stage)
{
     StageProgressWidget *stage_widget = new StageProgressWidget(this);
      stage_widget->setStage(stage);
      stages_box_layout->addWidget(stage_widget);
      connect(stage_widget, &StageProgressWidget::deleteRequested, this, &ContractWidget::deleteStageWidgetRequestHandler);
}

void ContractWidget::showDeleteDialog()
{
    DleteDialog *dleteDialog = new DleteDialog(0);
    dleteDialog->setLabelText("Удалить контракт \"" + _contract->getContractName() + " \" ?");

    connect(dleteDialog, & DleteDialog::accepted, _contract, &Contract::deleteContractRequestHandler);
    connect(dleteDialog, & DleteDialog::accepted, this, &ContractWidget::deleteRequested);
    dleteDialog->show();
}

void ContractWidget::setAlpha(int a)
{
    QString stsh = QString( "background-color: rgba(50, 50, 50, "
                            + QString::number(a) + "); color: rgba(255, 255, 255, "
                            + QString::number(a) + " ); border: 0px solid grey;" );
    setStyleSheet(stsh);
//    num->setStyleSheet(stsh);
//    name->setStyleSheet(stsh);
//    button_box->setStyleSheet(stsh);
//    stages_box->setStyleSheet(stsh);

}

ContractWidget::~ContractWidget()
{
}


