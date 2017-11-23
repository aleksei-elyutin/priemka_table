#include "tablewidget.h"


TableWidget::TableWidget(QFrame *parent) : QFrame(parent)
{  
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _layout = new QVBoxLayout(this);

    header_dock = new QFrame(this);
    header_dock_layout = new QHBoxLayout(header_dock);

    int left_margin = 0, top_margin = 0, right_margin = 0, bottom_margin = 0;
    header_dock_layout->getContentsMargins(&left_margin, &top_margin, &right_margin, &bottom_margin);
    header_dock_layout->setContentsMargins(left_margin, top_margin, 15, bottom_margin);
    addHeader();
    _layout->addWidget(header_dock);


    table_dock = new QWidget(this);
   _scrollArea = new QScrollArea;
    _scrollArea->setWidget(table_dock);
   _scrollArea->setWidgetResizable(true);
   _layout->addWidget(_scrollArea);

   QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
       shadowEffect -> setBlurRadius(9.0);
       shadowEffect -> setColor(QColor(90, 200, 40, 80));
       shadowEffect -> setOffset(4.0);
   setGraphicsEffect(shadowEffect);

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
    _last_entry = 0;

    table_dock = new QWidget();
    _scrollArea->setWidget(table_dock);



    tableDock_glayout = new QGridLayout(table_dock);
    tableDock_glayout->setColumnStretch(0,0);
    tableDock_glayout->setColumnStretch(1,0);
    tableDock_glayout->setColumnStretch(2,1);
    tableDock_glayout->setSpacing(1);
    table_dock->setLayout(tableDock_glayout);

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
      // num->setMaximumHeight(50);
       num->setMaximumWidth(50);
       num->setDigitCount(3);
       num->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

//        num->setStyleSheet("border: 0px solid black;");
        num->setStyleSheet("text-align: middle; background-color: rgb(250, 250, 250); width: 0px; border: 1px solid black;");
        //num->setMinimumWidth(60);

        tableDock_glayout->addWidget(num,_last_entry,0);

        QLabel* name = new QLabel(contract->getContractName(),table_dock);
        name->setStyleSheet("text-align: middle; color: rgb(0, 0, 0); background-color: rgb(250, 250, 250); width: 1px; border: 1px solid black;");
        name->setWordWrap(true);
        name->setFont(QFont("Times", 14, QFont::Normal));
        name->setMinimumHeight(50);
        name->setMinimumWidth(250);
        name->setMaximumWidth(250);
        name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        //name->setMinimumWidth(400);

        tableDock_glayout->addWidget(name,_last_entry, 1);

        ContractWidget *contractWidget = new ContractWidget(table_dock, contract);
        contractWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
        tableDock_glayout->addWidget(contractWidget,_last_entry,2);


        tableDock_glayout->setRowStretch(_last_entry,1); ///???
        _last_entry++;

}
void TableWidget::addHeader()
{
    QLabel* num = new QLabel(QString("№ П/П"),header_dock);
    num->setStyleSheet("text-align: middle; background-color: rgb(230, 240, 240); width: 10px; border: 2px solid black;");
    num->setMinimumWidth(50);
    num->setMaximumWidth(50);
    num->setMinimumHeight(50);
    num->setMaximumHeight(50);
    header_dock_layout->addWidget(num);
    QLabel* name = new QLabel(QString("Номер контракта"),header_dock); // \n
    name->setStyleSheet("text-align: middle; background-color: rgb(230, 240, 240); width: 10px; border: 2px solid black;");
    name->setWordWrap(true);
    name->setMinimumWidth(250);
    name->setMaximumWidth(250);
    name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    header_dock_layout->addWidget(name);

    MonHeaderWidget* header = new MonHeaderWidget(header_dock);
    header->setYear(2017);
    header->setVerticalSize(50);
    header->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    header->setStyleSheet("text-align: middle; background-color: rgb(230, 240, 240); width: 10px; border: 2px solid black;");
    header_dock_layout->addWidget(header);

}





