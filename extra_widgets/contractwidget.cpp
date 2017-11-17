#include "contractwidget.h"

ContractWidget::ContractWidget(QWidget *parent, Contract* contract) : QFrame(parent)
{

//    hLayout->setSpacing(0);
//    hLayout->setMargin(0);

    _contract=contract;
    vLayout = new QVBoxLayout(this);
    vLayout->setSpacing(0);
    vLayout->setMargin(0);

    setStyleSheet("text-align: middle; background-color: rgb(200, 200, 200); width: 1px; border: 2px solid black;");

    /*Кнопки изменить и удалить*/
    QWidget *button_box = new QWidget();
    button_box->setMinimumHeight(30);
    button_box->setMaximumHeight(30);

    button_box->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 1px; border: 0px solid black;");
    QHBoxLayout *hLayout = new QHBoxLayout(button_box);
    hLayout->setMargin(0);
    hLayout->setSpacing(3);

    QSpacerItem *hspacer = new QSpacerItem(50,30,QSizePolicy::Expanding,QSizePolicy::Expanding);
    hLayout->addItem(hspacer);

    setup_contract_button = new QPushButton (QString("..."),this);
    setup_contract_button->setMinimumHeight(30);
    setup_contract_button->setMaximumHeight(30);
    setup_contract_button->setMinimumWidth(30);
    setup_contract_button->setMaximumWidth(30);
    hLayout->addWidget(setup_contract_button);
    connect(setup_contract_button, &QPushButton::clicked, this, &ContractWidget::setupContract);

    delete_contract_button = new QPushButton (QString("X"),this);
    delete_contract_button->setMinimumHeight(30);
    delete_contract_button->setMaximumHeight(30);
    delete_contract_button->setMinimumWidth(30);
    delete_contract_button->setMaximumWidth(30);
    connect(delete_contract_button, &QPushButton::clicked, this, &ContractWidget::showDeleteDialog);

    hLayout->addWidget(delete_contract_button);       
    vLayout->addWidget(button_box);



    /*******/


    /*Содержимое */

    int num_stages = _contract->getNumStages();
    for (int i=0; i< num_stages; i++)
    {
         StageProgressWidget *_stage_widget = new StageProgressWidget(this,contract->getStage(i));
         vLayout->addWidget(_stage_widget);
         //tmp_stage_widget->show();
    }
    /*******/



    /*Кнопка добавить*/
    add_stage_button = new QPushButton (QString("Добавить этап..."),this);
    add_stage_button->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 1px; border: 0px solid black;");
    vLayout->addWidget(add_stage_button);
    connect(add_stage_button, &QPushButton::clicked, _contract, &Contract::createStage);
    /********/

    vLayout->setSpacing(3);

}
void ContractWidget::setupContract()
{
    contractRedactorDialog *dial = new contractRedactorDialog (0);
    dial->linkContract(_contract);
    dial->draw();
    dial->show();
    connect(dial, &contractRedactorDialog::accepted, _contract, &Contract::imChanged);

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


