#include "tablewidget.h"


TableWidget::TableWidget(QFrame *parent) : QFrame(parent)
{  
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _layout = new QGridLayout(this);
    table_dock = new QWidget();
   // _layout->addWidget(table_dock,0,0);
   // add_contract_button = new QPushButton(this);
   // _layout->addWidget(add_contract_button, 1, 0);
   _scrollArea = new QScrollArea;
   _scrollArea->setWidgetResizable(true);
   _layout->addWidget(_scrollArea,0,0);



//    tableDock_glayout = new QGridLayout(table_dock);
//    table_dock->setLayout(tableDock_glayout);


//    _scrollArea->setMinimumWidth(1800);
//    _scrollArea->setMinimumHeight(900);

}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
    connect(_base, &DataBase::base_changed, this, &TableWidget::draw);
    draw();
}


void TableWidget::draw()
{  
    delete table_dock;
    _last_entry = 1;

    table_dock = new QWidget();
    _scrollArea->setWidget(table_dock);



    tableDock_glayout = new QGridLayout(table_dock);
    tableDock_glayout->setSpacing(3);
    table_dock->setLayout(tableDock_glayout);

    addHeader();

    int num_contracts=_base->getNumContracts();
    for (int i = 0; i < num_contracts; i++)
    {
            addContractWidget(_base->getContract(i));
            qDebug() << "Отрисован контракт "<<_base->getContract(i)->getContractName() << " с приритетом " <<
                        _base->getContract(i)->calculateContractPriority();

    }


    add_contract_button = new QPushButton(table_dock);
    tableDock_glayout->addWidget(add_contract_button, ++_last_entry, 0, 1, 4);
    add_contract_button->setText("Добавить контракт...");
    connect(add_contract_button, &QPushButton::clicked, _base, &DataBase::createContract);

    QSpacerItem *vspacer = new QSpacerItem(20,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableDock_glayout->addItem(vspacer,++_last_entry,0);

//    QSpacerItem *hspacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
//    tableDock_glayout->addItem(hspacer,0,4);


}

void TableWidget::addContractWidget(Contract *contract)
{


      // QLabel* num = new QLabel(QString::number(_last_entry),table_dock);

       QLCDNumber *num = new QLCDNumber(this);
       num->display(QString::number(_last_entry));
       num->setMinimumHeight(50);
       num->setMinimumWidth(50);
       num->setMaximumHeight(50);
       //num->setMaximumWidth(50);
       num->setDigitCount(2);
       num->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

//        num->setStyleSheet("border: 0px solid black;");
        num->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 1px; border: 1px solid black;");
        //num->setMinimumWidth(60);

        tableDock_glayout->addWidget(num,_last_entry,0);

        QLabel* name = new QLabel(contract->getContractName(),table_dock);
        name->setStyleSheet("text-align: middle; color: rgb(0, 0, 0); background-color: rgb(250, 250, 250); width: 1px; border: 1px solid black;");
        name->setWordWrap(true);
        name->setFont(QFont("Times", 16, QFont::Normal));
        name->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        //name->setMinimumWidth(400);

        tableDock_glayout->addWidget(name,_last_entry, 1);

        ContractWidget *contractWidget = new ContractWidget(table_dock, contract);
        tableDock_glayout->addWidget(contractWidget,_last_entry,2);

        _last_entry++;

}
void TableWidget::addHeader()
{
    QLabel* num = new QLabel(QString("№ П/П"),table_dock);
    num->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
    num->setMinimumWidth(50);
    tableDock_glayout->addWidget(num,0,0);
    QLabel* name = new QLabel(QString("Номер \nконтракта"),table_dock);
    name->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
   // name->setWordWrap(true);
   // name->setMinimumWidth(400);
    tableDock_glayout->addWidget(name,0,1);
    QLabel* st = new QLabel(QString("Прогресс выполнения"),table_dock);
    st->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
    st->setWordWrap(true);
    st->setMinimumWidth(1000); /*Костыль !!!!*/
    tableDock_glayout->addWidget(st,0,2);
}





