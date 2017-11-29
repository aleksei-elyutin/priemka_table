#include "tablewidget.h"


TableWidget::TableWidget(QFrame *parent) : QFrame(parent)
{  
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    main_layout = new QVBoxLayout(this);

    header_dock = new QFrame(this);
    header_dock_layout = new QHBoxLayout(header_dock);
    int left_margin = 0, top_margin = 0, right_margin = 0, bottom_margin = 0;
    header_dock_layout->getContentsMargins(&left_margin, &top_margin, &right_margin, &bottom_margin);
    header_dock_layout->setContentsMargins(left_margin, top_margin, 15, bottom_margin);
    createHeader();
    main_layout->addWidget(header_dock);


    table_dock = new QWidget(this);
    _scrollArea->setWidget(table_dock);



   _scrollArea = new QScrollArea;
   _scrollArea->setWidget(table_dock);
   _scrollArea->setWidgetResizable(true);
   main_layout->addWidget(_scrollArea);
   table_dock_layout = new QVBoxLayout(table_dock);

   table_dock->setLayout(table_dock_layout); //????

   add_contract_button = new QPushButton(table_dock);
   table_dock_layout->addWidget(add_contract_button);
   add_contract_button->setText("Добавить контракт...");
   add_contract_button->setStyleSheet("color: rgba(255, 255, 255, 255); background-color: rgb(50, 50, 50);");
   connect(add_contract_button, &QPushButton::clicked, _base, &DataBase::createContract);

   QSpacerItem *vspacer = new QSpacerItem(20,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
   table_dock_layout->addItem(vspacer);



   /*QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
       shadowEffect -> setBlurRadius(9.0);
       shadowEffect -> setColor(QColor(90, 200, 40, 80));
       shadowEffect -> setOffset(4.0);
   setGraphicsEffect(shadowEffect);*/

}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
    //connect(_base, &DataBase::base_changed, this, &TableWidget::draw);
    draw();
}


void TableWidget::draw()
{  
    delete table_dock;
    _last_entry = 0;

    table_dock = new QWidget();
    _scrollArea->setWidget(table_dock);

    int num_contracts=_base->getNumContracts();
    for (int i = 0; i < num_contracts; i++)
    {
            addContractWidget(_base->getContract(i));
            qDebug() << "Отрисован контракт "<<_base->getContract(i)->getContractName() << " с приритетом " <<
                        _base->getContract(i)->calculateContractPriority();

    }




//    QSpacerItem *hspacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
//    table_dock_layout->addItem(hspacer,0,4);


}

void TableWidget::addContractWidget(Contract *contract)
{
    ContractWidget *contractWidget = new ContractWidget(table_dock);
    contractWidget->setContract( contract);
    contractWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    table_dock_layout->insertWidget(table_dock_layout->count()-3, contractWidget);
  //  table_dock_layout->setRowStretch(_last_entry,1); ///???
    updateNumbers();
}

void TableWidget::updateNumbers()
{
    int num_entries = table_dock_layout->count();
    for (int i=0; i < num_entries; i ++) {
        QWidget* _widget =(table_dock_layout->itemAt(i)->widget());
        QLCDNumber* lbl = _widget->findChild<QLCDNumber*>("number");
       // qDebug() << lbl->text();
        lbl->display(QString::number(table_dock_layout->indexOf(qobject_cast<QWidget*>(_widget))));
    }

}

void TableWidget::createHeader()
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





