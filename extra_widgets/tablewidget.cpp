#include "tablewidget.h"


TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{  
    //setFrameStyle(QFrame::Panel | QFrame::Sunken);
    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);


    header_dock = new QFrame(this);

    header_dock ->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                            "color: rgb(255, 255, 255); border: 0px solid grey;");
    header_dock_layout = new QHBoxLayout(header_dock);
    header_dock_layout->setSpacing(1);

    int left_margin = 0, top_margin = 0, right_margin = 0, bottom_margin = 0;
    header_dock_layout->getContentsMargins(&left_margin, &top_margin, &right_margin, &bottom_margin);
    header_dock_layout->setContentsMargins(left_margin, top_margin, 20, bottom_margin);

    createHeader();
    main_layout->addWidget(header_dock);


    table_dock = new QWidget(this);
    table_dock ->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                            "color: rgb(255, 255, 255); border: 0px solid black;");
    _scrollArea = new QScrollArea();
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
   add_contract_button->setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
                                      "color: rgb(50, 50, 50); border: 0px solid black; ");
   add_contract_button->setStyleSheet("QPushButton:hover{background-color: rgb(80, 80, 80); color: rgb(255, 255, 255);}");
   add_contract_button->setMinimumHeight(50);
   add_contract_button->setVisible(false);
   connect(add_contract_button, &QPushButton::clicked, this, &TableWidget::createContractWidgetRequestHandler);

   QSpacerItem *vspacer = new QSpacerItem(20,50,QSizePolicy::Expanding,QSizePolicy::Expanding);
   table_dock_layout->addItem(vspacer);

   pa = new QPropertyAnimation(this);
   loop = new QEventLoop(this);
   connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);

}

TableWidget::~TableWidget()
{
    delete _scrollArea;
}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
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
    //sort();

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

    connect(contractWidget, &ContractWidget::doubleClicked, this, &TableWidget::popSelected);

    updateNumbers();

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
        lbl->display(QString::number(table_dock_layout->indexOf(qobject_cast<QWidget*>(_widget))+1));
    }
}

void TableWidget::sort()
{   
   // if (islocked)
    {
        /*** ЗАГЛУШЕНО  **/
        qDebug() << "СОРТИРОВКА";
        qDebug() << "Sender" << sender();

        Contract *tmp1, *tmp2;
        int max_priority_pos = 0;
        int max_priority = 0;


         int num_entries = table_dock_layout->count()-2;
          for (int j=0; (j < num_entries); j++)
         {
             for (int i=0; (i < num_entries-1); i++)
             {
                 tmp1 = qobject_cast<ContractWidget*>(table_dock_layout->itemAt(i)->widget())->getContract();
                 max_priority_pos = i;
                 max_priority = tmp1->getPriority();

                 for (int k=i+1; k < num_entries; k++)
                 {
                     tmp2 = qobject_cast<ContractWidget*>(table_dock_layout->itemAt(k)->widget())->getContract();
                     if (tmp2->getPriority() > max_priority)
                     {
                         max_priority = tmp2->getPriority();
                         max_priority_pos = k;
                     }

                     if ( max_priority_pos != i)
                     {
                          qDebug() << "Moving: from pos. " << max_priority_pos
                                   << "(prioirity=" << (tmp2->getPriority()) <<") " << " to pos." << tmp1->getPriority()
                                   << "(prioirity="<< (tmp1->getPriority()) <<")";
                         popEntryAnim(qobject_cast<QWidget*>(table_dock_layout->itemAt(max_priority_pos)->widget()),i);
                         //  popEntry(k,i);
                           break;
                        // qobject_cast<ContractWidget*>(table_dock_layout->itemAt(k)->widget())->draw();
                     }

                 }
             }
         }
         updateNumbers();
    }
  //  else qDebug() << "СОРТИРОВКА ПРОПУЩЕНА - таблица редактируется";

}

void TableWidget::popSelected()
{
 /*  qDebug() << "Origin: "<<sender();
   QWidget *s  = qobject_cast<QWidget*>(sender());
    qDebug() << "Casted: "<< s;
   int num = table_dock_layout->indexOf(s);
    qDebug() << "Num: "<< num;
   popEntryAnim(s,0);*/
}

void TableWidget::popEntryAnim(QWidget* _widget, int pos)
{
    if (table_dock_layout->indexOf(_widget)!=pos)
    {
        float duration_factor = 1.0;
        if (pos < 0) pos = 0;
        if (pos > table_dock_layout->count()-3) pos = table_dock_layout->count()-3;

        QRect current_widget_geometry = _widget->geometry();
        QRect new_widget_geometry = table_dock_layout->itemAt(pos)->geometry();
       // new_widget_geometry.setWidth(table_dock_layout->itemAt(pos)->geometry().width());
       // new_widget_geometry.setHeight(table_dock_layout->itemAt(pos)->geometry().height());
        new_widget_geometry.setX(table_dock_layout->itemAt(pos)->geometry().x());
        new_widget_geometry.setY(table_dock_layout->itemAt(pos)->geometry().y());
        new_widget_geometry.setWidth(_widget->geometry().width());
        new_widget_geometry.setHeight(_widget->geometry().height());
        _widget->raise();

        pa->setPropertyName("geometry");
        pa->setDuration((int) ((float) abs(new_widget_geometry.top()-current_widget_geometry.top())*duration_factor));

        pa->setTargetObject(_widget);
        pa->setStartValue(current_widget_geometry);
        qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_widget_geometry);
        qDebug() << "endValue:"<< pa->endValue();


        //connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);
        pa->start();
        loop->exec();
        //disconnect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);

        table_dock_layout->removeWidget(_widget);
        table_dock_layout->insertWidget(pos,_widget);
        table_dock_layout->update();
    }

}

void TableWidget::popEntry(int current_pos, int new_pos)
{
    QWidget *tmp = qobject_cast<QWidget*>(table_dock_layout->itemAt(current_pos)->widget());
    table_dock_layout->removeWidget(tmp);
    table_dock_layout->insertWidget(new_pos,tmp);
   // table_dock_layout->update();
   // qobject_cast<ContractWidget*>(table_dock_layout->itemAt(new_pos)->widget())->draw();
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
    header->setYear(QDate::currentDate().year());
    header->setVerticalSize(50);
    header->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    header->setStyleSheet("text-align: middle; "
                          "background-color: rgb(50, 50, 50); width: 0px; "
                          "color: rgb(255, 255, 255); border: 1px solid grey;");
    header_dock_layout->addWidget(monthes_dock);

}







