#include "tablewidget.h"


TableWidget::TableWidget(QFrame *parent) : QFrame(parent)
{  
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);


    header_dock = new QFrame(this);

    header_dock ->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                            "color: rgb(255, 255, 255); border: 0px solid grey;");
    header_dock_layout = new QHBoxLayout(header_dock);
    header_dock_layout->setSpacing(3);

    int left_margin = 0, top_margin = 0, right_margin = 0, bottom_margin = 0;
    header_dock_layout->getContentsMargins(&left_margin, &top_margin, &right_margin, &bottom_margin);
    //header_dock_layout->setContentsMargins(left_margin, top_margin, 15, bottom_margin);

    createHeader();
    main_layout->addWidget(header_dock);


    table_dock = new QWidget(this);
    table_dock ->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                            "color: rgb(255, 255, 255); border: 0px solid black;");
    _scrollArea = new QScrollArea();
    _scrollArea->setWidget(table_dock);



   _scrollArea = new QScrollArea;
   _scrollArea->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                              "color: rgb(255, 255, 255); border: 0px solid black;");;
   _scrollArea->setWidget(table_dock);
   _scrollArea->setWidgetResizable(true);
   _scrollArea->setContentsMargins(0,0,0,0);
   main_layout->addWidget(_scrollArea);
   table_dock_layout = new QVBoxLayout(table_dock);
   table_dock_layout->setSpacing(3);



   //table_dock->setLayout(table_dock_layout); //????
   table_dock_layout->setContentsMargins(0, top_margin,  right_margin, bottom_margin);

   add_contract_button = new QPushButton(table_dock);
   table_dock_layout->addWidget(add_contract_button);
   add_contract_button->setText("Добавить контракт...");
   add_contract_button->setStyleSheet("text-align: middle; qproperty-alignment: AlignCenter; background-color: rgb(20, 20, 20); width: 10px; "
                                      "color: rgb(50, 50, 50); border: 0px solid black; ");
   add_contract_button->setStyleSheet("QPushButton:hover{background-color: rgb(80, 80, 80); color: rgb(255, 255, 255);}");
   add_contract_button->setMinimumHeight(50);
   add_contract_button->setVisible(false);
   connect(add_contract_button, &QPushButton::clicked, this, &TableWidget::createContractWidgetRequestHandler);

   QSpacerItem *vspacer = new QSpacerItem(20,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
   table_dock_layout->addItem(vspacer);

   pa = new QPropertyAnimation(this);
   loop = new QEventLoop(this);



   /*QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
       shadowEffect -> setBlurRadius(9.0);
       shadowEffect -> setColor(QColor(90, 200, 40, 80));
       shadowEffect -> setOffset(4.0);
   setGraphicsEffect(shadowEffect);*/

}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
    connect(_base, &DataBase::baseLoaded, this, &TableWidget::reDrawAll);
    reDrawAll();
}


void TableWidget::reDrawAll()
{  
    int number_of_layout_entries = table_dock_layout->count();
    if (number_of_layout_entries > 2) clearTable();
    if (number_of_layout_entries < 2) qDebug() << "Some shit happened... No button 'add contract' or no spacer in table!";

    int num_contracts=_base->getNumContracts();
    for (int i = 0; i < num_contracts; i++)
    {
            addContractWidget(_base->getContract(i));
         /*   qDebug() << "Отрисован контракт "<<_base->getContract(i)->getContractName() << " с приритетом " <<
                        _base->getContract(i)->calculateContractPriority();*/
    }

}

void TableWidget::clearTable()
{
    int number_of_layout_entries = table_dock_layout->count();
    for (int i = number_of_layout_entries-3; i>=0; i--)
    {
        delete table_dock_layout->itemAt(i)->widget();
    }
}



void TableWidget::addContractWidget(Contract *contract)
{
    ContractWidget *contractWidget = new ContractWidget(table_dock);
    contractWidget->setContract(contract);
    contractWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    table_dock_layout->insertWidget(table_dock_layout->count()-2, contractWidget);
    connect(contractWidget, &ContractWidget::deleteRequested, this, &TableWidget::deleteContractWidgetRequestHandler);
    connect(this, &TableWidget::unlocked, contractWidget, &ContractWidget::setUnlock);
  //  table_dock_layout->setRowStretch(_last_entry,1); ///???
    updateNumbers();

    connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);
    pa->setPropertyName("alpha");
    pa->setTargetObject(contractWidget);
    pa->setDuration(100);
    pa->setStartValue(0);
    pa->setEndValue(255);
    pa->start();
    loop->exec();

}

void TableWidget::createContractWidgetRequestHandler()
{
    Contract* new_contract = _base->createContract();
    addContractWidget(new_contract);
}

void TableWidget::deleteContractWidgetRequestHandler()
{
    delete sender();
    updateNumbers();
}

void TableWidget::unlock()
{
    add_contract_button->setVisible(true);
    emit unlocked();
}


void TableWidget::updateNumbers()
{
    int num_entries = table_dock_layout->count();
    for (int i=0; i < num_entries-2; i ++) {
        QWidget* _widget =(table_dock_layout->itemAt(i)->widget());
        QLCDNumber* lbl = _widget->findChild<QLCDNumber*>("number");
       // qDebug() << lbl->text();
        lbl->display(QString::number(table_dock_layout->indexOf(qobject_cast<QWidget*>(_widget))));
    }

}

void TableWidget::createHeader()
{
    QLabel* num = new QLabel(QString("№ П/П"),header_dock);
    num->setStyleSheet("text-align: middle; qproperty-alignment: AlignCenter;"
                       " background-color: rgb(50, 50, 50); width: 0px; "
                       "color: rgb(255, 255, 255); border: 1px solid grey;");
    num->setMinimumWidth(50);
    num->setMaximumWidth(50);
    num->setMinimumHeight(50);
    num->setMaximumHeight(50);
    header_dock_layout->addWidget(num);
    QLabel* name = new QLabel(QString("Наименование контракта"),header_dock); // \n
    name->setStyleSheet("text-align: middle; qproperty-alignment: AlignCenter;"
                        " background-color: rgb(50, 50, 50); width: 0px; "
                        "color: rgb(255, 255, 255); border: 1px solid grey;");
    name->setWordWrap(true);
    name->setMinimumWidth(250);
    name->setMaximumWidth(250);
    name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    header_dock_layout->addWidget(name);


    QWidget* monthes_dock = new QWidget (header_dock);
    QVBoxLayout* monthes_dock_layout = new QVBoxLayout(monthes_dock);
    monthes_dock_layout->setContentsMargins(3,0,0,0);
    MonHeaderWidget* header = new MonHeaderWidget(monthes_dock);
    monthes_dock_layout->addWidget(header);
    header->setYear(2017); ///Изменить!!!
    header->setVerticalSize(50);
    header->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    header->setStyleSheet("text-align: middle; qproperty-alignment: AlignCenter;"
                          "background-color: rgb(50, 50, 50); width: 0px; "
                          "color: rgb(255, 255, 255); border: 1px solid grey;");
    header_dock_layout->addWidget(monthes_dock);

}







