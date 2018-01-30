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
}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
    connect(_base, &DataBase::baseLoaded, this, &TableWidget::reDrawAll);
    //connect(_base, &DataBase::baseChanged, this, &TableWidget::reDrawAll); //!!!!!
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

    if (islocked == true) contractWidget->lock();
    else contractWidget->unlock();

    connect(this, &TableWidget::unlocked, contractWidget, &ContractWidget::unlock);
    connect(this, &TableWidget::locked, contractWidget, &ContractWidget::lock);
    updateNumbers();

    connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);
    pa->setPropertyName("alpha");
    pa->setTargetObject(contractWidget);
    pa->setDuration(50);
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
    islocked = false;
    add_contract_button->setVisible(true);
    emit unlocked();
}
void TableWidget::lock()
{
    islocked = true;
    add_contract_button->setVisible(false);
    emit locked();
}



void TableWidget::updateNumbers()
{
    int num_entries = table_dock_layout->count();
    for (int i=0; i < num_entries-2; i ++)
    {
        QWidget* _widget =(table_dock_layout->itemAt(i)->widget());
        QLCDNumber* lbl = _widget->findChild<QLCDNumber*>("number");
        lbl->display(QString::number(table_dock_layout->indexOf(qobject_cast<QWidget*>(_widget))));
    }
}

void TableWidget::sort()
{
    Contract *tmp1, *tmp2;
    bool stopFlag = true;

     int num_entries = table_dock_layout->count();
     for (int i=0; (i < num_entries-2)&stopFlag ; i ++)
     {

       tmp1 = qobject_cast<ContractWidget*>(table_dock_layout->itemAt(i)->widget())->getContract();
       stopFlag = true;
       int max_priority_pos = i;
       int max_priority = tmp1->getPriority();
        for (int k=i+1; k < num_entries-2; k ++)
        {
            tmp2 = qobject_cast<ContractWidget*>(table_dock_layout->itemAt(k)->widget())->getContract();
            if (tmp2->getPriority() > max_priority)
            {
                stopFlag = false;
                max_priority = tmp2->getPriority();
                max_priority_pos = k;
            }
            if (!stopFlag) popEntry(qobject_cast<ContractWidget*>(table_dock_layout->itemAt(max_priority_pos)->widget()),i);
        }
     }

}

void TableWidget::popEntry(QWidget* _widget, int pos)
{
    if (table_dock_layout->indexOf(_widget)!=pos)
    {
        float duration_factor = 2.4;

        if (pos < 0) pos = 0;
        if (pos >= table_dock_layout->count()) pos = table_dock_layout->count()-1;

        QRect current_widget_geometry = _widget->geometry();
        QRect new_widget_geometry = table_dock_layout->itemAt(pos)->geometry();
        new_widget_geometry.setWidth(table_dock_layout->itemAt(pos)->geometry().width());
        new_widget_geometry.setHeight(table_dock_layout->itemAt(pos)->geometry().height());
        _widget->raise();

        table_dock_layout->removeWidget(_widget);

        pa->setPropertyName("geometry");
        pa->setDuration((int) ((float) abs(new_widget_geometry.top()-current_widget_geometry.top())*duration_factor));

        pa->setTargetObject(_widget);
        pa->setStartValue(current_widget_geometry);
       // qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_widget_geometry);
       // qDebug() << "endValue:"<< pa->endValue();

         pa->start();
        loop->exec();

        table_dock_layout->insertWidget(pos,_widget);
        table_dock_layout->update();

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







