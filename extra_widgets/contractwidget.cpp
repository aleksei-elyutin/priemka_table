#include "contractwidget.h"

ContractWidget::ContractWidget(QWidget *parent) : QFrame(parent)
{
    /*** widget stylesheet **/
    setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(255, 255, 255, 255); background-color: rgb(20, 20, 20);");

     main_layout = new QHBoxLayout (this);


     num = new QLCDNumber(this);
     num->setObjectName("number");
     num->setStyleSheet("text-align: middle; background-color: rgb(230, 240, 240); width: 10px; border: 2px solid black;");
     num->setMinimumWidth(50);
     num->setMaximumWidth(50);
     num->setMinimumHeight(50);
     num->setMaximumHeight(50);
     main_layout->addWidget(num);

     name = new QLabel(QString("Номер контракта"),header_dock); // \n
     name->setStyleSheet("text-align: middle; background-color: rgb(230, 240, 240); width: 10px; border: 2px solid black;");
     name->setFont(QFont("Times", 14, QFont::Normal));
     name->setWordWrap(true);
     name->setMinimumWidth(250);
     name->setMaximumWidth(250);
     name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
     main_layout->addWidget(name);


    stages_box = new QWidget(this);
    stages_box_layout = new QVBoxLayout(stages_box);
    stages_box_layout->setSpacing(0);
    stages_box_layout->setMargin(0);

    setStyleSheet("text-align: middle; background-color: rgb(200, 200, 200); width: 1px; border: 1px solid black;");

    /*Кнопки добавить, изменить и удалить*/
    button_box = new QWidget(this);
    button_box->setMinimumHeight(30);
    button_box->setMaximumHeight(30);

    button_box->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 1px; border: 0px solid black;");
    button_box_layout = new QHBoxLayout(button_box);
    button_box_layout->setMargin(0);
    button_box_layout->setSpacing(3);

    QSpacerItem *hspacer = new QSpacerItem(50,30,QSizePolicy::Expanding,QSizePolicy::Expanding);
    hLayout->addItem(hspacer);
    add_stage_button = new QPushButton (QString("+"),this);
    add_stage_button->setMinimumHeight(30);
    add_stage_button->setMaximumHeight(30);
    add_stage_button->setMinimumWidth(30);
    add_stage_button->setMaximumWidth(30);
    // add_stage_button->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 1px; border: 0px solid black;");
    button_box_layout->addWidget(add_stage_button);
    connect(add_stage_button, &QPushButton::clicked, _contract, &Contract::createStage);



    setup_contract_button = new QPushButton (QString("..."),this);
    setup_contract_button->setMinimumHeight(30);
    setup_contract_button->setMaximumHeight(30);
    setup_contract_button->setMinimumWidth(30);
    setup_contract_button->setMaximumWidth(30);
    button_box_layout->addWidget(setup_contract_button);
    connect(setup_contract_button, &QPushButton::clicked, this, &ContractWidget::setupContract);

    delete_contract_button = new QPushButton (QString("X"),this);
    delete_contract_button->setMinimumHeight(30);
    delete_contract_button->setMaximumHeight(30);
    delete_contract_button->setMinimumWidth(30);
    delete_contract_button->setMaximumWidth(30);
    connect(delete_contract_button, &QPushButton::clicked, this, &ContractWidget::showDeleteDialog);

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
    /**************!!!!!!!!!!!!!!!!!*/
    int num_stages = _contract->getNumStages();
    for (int i=0; i< num_stages; i++)
    {
         StageProgressWidget *_stage_widget = new StageProgressWidget(this);
         _stage_widget->setStage(contract->getStage(i));
         stages_box_layout->addWidget(_stage_widget);
         //tmp_stage_widget->show();
    }
}


void ContractWidget::showDeleteDialog()
{
    DleteDialog *dleteDialog = new DleteDialog(0);
    dleteDialog->setLabelText("Удалить контракт \"" + _contract->getContractName() + " \" ?");

    connect(dleteDialog, & DleteDialog::accepted, _contract, &Contract::deleteRequest);
    dleteDialog->show();
}


ContractWidget::~ContractWidget()
{
}


