#include "contractwidget.h"

ContractWidget::ContractWidget(QWidget *parent) : QWidget(parent)
{
    /*** widget stylesheet **/
    setStyleSheet("border: 0px solid grey; text-align: middle; color: rgba(255, 255, 255, 255);"
                  " background-color: rgb(50, 50, 50);");

     main_layout = new QHBoxLayout (this);

     main_layout->setStretch(0,0);
     main_layout->setStretch(1,0);
     main_layout->setStretch(2,1);
     main_layout->setSpacing(4);
     main_layout->setContentsMargins(main_layout->contentsMargins().left(),0, main_layout->contentsMargins().right(),0);


     num = new QLCDNumber(this);
     num->setObjectName("number");
     /*Стиль номера*/
    // num->setStyleSheet(" background-color: rgba(50, 50, 50, 150); background-image: url(:/resources/41009187.png);");
//                        "color: rgb(255, 255, 255); border: 0px solid black;");
     num->setMinimumWidth(50);
     num->setMaximumWidth(50);
     num->setMinimumHeight(40);
     //num->setMaximumHeight(50);

     main_layout->addWidget(num);

     name_buttons_box = new QWidget(this);
    // name_buttons_box->setStyleSheet("background-image: url(://resources/20719.png)");
     name_buttons_box_layout = new QVBoxLayout(name_buttons_box);
     name_buttons_box_layout->setContentsMargins(0,0,0,0);
     name_buttons_box_layout->setSpacing(0);

     name = new QLabel(this);
     name->setStyleSheet("text-align: middle; qproperty-alignment: AlignCenter;"
                         " background-color: rgb(50, 50, 50); width: 0px;"
                         "color: rgb(255, 255, 255); border: 0px solid black;");
     name->setWordWrap(true);
     name->setMinimumWidth(250);
     name->setMaximumWidth(250);
     name->setMinimumHeight(40);
     name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
     name_buttons_box_layout->addWidget(name);

     /*Кнопки добавить, изменить и удалить*/
     button_box = new QWidget(this);
     button_box->setMinimumHeight(20);
     button_box->setMaximumHeight(20);
     button_box->setStyleSheet("text-align: middle; color: rgba(255, 255, 255, 255);"
                               " background-color: rgb(50, 50, 50); border: 0px solid black;");
     button_box_layout = new QHBoxLayout(button_box);
     button_box_layout->setMargin(0);
     button_box_layout->setSpacing(0);

    // QSpacerItem *hspacer = new QSpacerItem(50,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
   //  button_box_layout->addItem(hspacer);

     add_stage_button = new QPushButton (this);
    // add_stage_button->setText("Добавить этап");
     QPixmap add_pixmap("://resources/button_grey_add.png");
     QIcon add_icon(add_pixmap);
     add_stage_button->setIcon(add_icon);
     add_stage_button->setIconSize(QSize(20,20));
     add_stage_button->setStyleSheet("QPushButton:hover{background-color: rgba(0, 255, 0, 100);}");
     add_stage_button->setMinimumHeight(20);
     add_stage_button->setMaximumHeight(20);
    // add_stage_button->setMinimumWidth(20);
    // add_stage_button->setMaximumWidth(20);
     button_box_layout->addWidget(add_stage_button);

     setup_contract_button = new QPushButton (this);
    // setup_contract_button->setText("Изменить контракт");
     QPixmap pen_pixmap("://resources/pen.png");
     QIcon pen_icon(pen_pixmap);
     setup_contract_button->setIcon(pen_icon);
     setup_contract_button->setIconSize(QSize(20,20));
     setup_contract_button->setStyleSheet("QPushButton:hover{background-color: rgba(255, 255, 0, 100);}");
     setup_contract_button->setMinimumHeight(20);
     setup_contract_button->setMaximumHeight(20);
    // setup_contract_button->setMinimumWidth(20);
    // setup_contract_button->setMaximumWidth(20);
     button_box_layout->addWidget(setup_contract_button);


     delete_contract_button = new QPushButton (this);
   //  delete_contract_button->setText("Удалить контракт");
     QPixmap delete_pixmap(":/resources/gnome_edit_delete.png");
     QIcon delete_icon(delete_pixmap);
     delete_contract_button->setIcon(delete_icon);
     delete_contract_button->setIconSize(QSize(20,20));
     delete_contract_button->setStyleSheet("QPushButton:hover{background-color: rgba(255, 0, 0, 100);}");
     delete_contract_button->setMinimumHeight(20);
     delete_contract_button->setMaximumHeight(20);
     //delete_contract_button->setMinimumWidth(20);
    // delete_contract_button->setMaximumWidth(20);
     button_box_layout->addWidget(delete_contract_button);

     name_buttons_box_layout->addWidget(button_box);
     /********/

     main_layout->addWidget(name_buttons_box);


    stages_box = new QWidget(this);
    stages_box_layout = new QVBoxLayout(stages_box);
    stages_box_layout->setSpacing(0);
    stages_box_layout->setMargin(0);

    dummy = new QSpacerItem (20,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
    stages_box_layout->addItem(dummy);


    stages_box_layout->setSpacing(3);
    stages_box_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(stages_box);

   /* pa = new QPropertyAnimation(this);
    loop = new QEventLoop(this);
    connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);*/


}

void ContractWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
}

void ContractWidget::setupContract()
{
    contractRedactorDialog *dial = new contractRedactorDialog (0);
    dial->linkContract(_contract);
    dial->draw();
    dial->show();
    connect(dial, &contractRedactorDialog::accepted, _contract, &Contract::contractChanged);

}

void ContractWidget::setContract(Contract *contract)
{
    _contract = contract;

    connect(add_stage_button, &QPushButton::clicked, this, &ContractWidget::createStageWidgetRequestHandler);
    connect(setup_contract_button, &QPushButton::clicked, this, &ContractWidget::setupContract);
    connect(delete_contract_button, &QPushButton::clicked, this, &ContractWidget::showDeleteDialog);
    connect(_contract, &Contract::contractChanged, this, &ContractWidget::draw);

    draw();

}

void ContractWidget::draw()
{

    clear();
//    int number_of_layout_entries = stages_box_layout->count();
//    if (number_of_layout_entries > 1)
//    if (number_of_layout_entries < 1) qDebug() << "Some shit happened... No button 'add stage' ";

    int num_stages = _contract->getNumStages();

       // stages_box_layout->removeItem(stages_box_layout->itemAt(0));
        for (int i=0; i< num_stages; i++)
        {
             addStageWidget(_contract->getStage(i));
        }

    name->setText(_contract->getContractName());
    updateNumbers();

//    setToolTip(QString("Контракт. Приоритет: " + QString::number(_contract->getPriority()) + ", дней до конца: " + QString::number(_contract->getDaysLeft())));

}

void ContractWidget::clear()
{
    int number_of_layout_entries = stages_box_layout->count();

    for (int i = number_of_layout_entries-1; i>0; i--)
    {
        delete stages_box_layout->itemAt(i)->widget();
    }

}

void ContractWidget::unlock()
{
    islocked = false;
    add_stage_button->setVisible(true);
    delete_contract_button->setVisible(true);
    setup_contract_button->setVisible(true);
    emit unlocked();
}
void ContractWidget::lock()
{
    islocked = true;
    add_stage_button->setVisible(false);
    delete_contract_button->setVisible(false);
    setup_contract_button->setVisible(false);
    emit locked();
}


void ContractWidget::createStageWidgetRequestHandler()
{
    Stage* new_stage = _contract->createStage();
    addStageWidget(new_stage);
}

void ContractWidget::deleteStageWidgetRequestHandler()
{
    delete sender();
    if (stages_box_layout->count() == 0) stages_box_layout->addItem(dummy);
    updateNumbers();
}

void ContractWidget::addStageWidget(Stage *stage)
{
      if (stages_box_layout->itemAt(0)->spacerItem() != 0)
          stages_box_layout->removeItem(stages_box_layout->itemAt(0));
      StageProgressWidget *stage_widget = new StageProgressWidget(this);
      stage_widget->setStage(stage);
      stages_box_layout->addWidget(stage_widget);
      connect(stage_widget, &StageProgressWidget::deleteRequested, this, &ContractWidget::deleteStageWidgetRequestHandler);


      if (islocked == true) stage_widget->lock();
      else stage_widget->unlock();

      connect(this, &ContractWidget::locked, stage_widget, &StageProgressWidget::lock);
      connect(this, &ContractWidget::unlocked, stage_widget, &StageProgressWidget::unlock);
      //   draw();
      updateNumbers();

   /*   pa->setPropertyName("alpha");
      pa->setTargetObject(stage_widget );
      pa->setDuration(20);
      pa->setStartValue(0);
      pa->setEndValue(255);


      pa->start();
      loop->exec();*/

}

void ContractWidget::updateNumbers()
{
    int num_entries = stages_box_layout->count();
   if (stages_box_layout->itemAt(0)->spacerItem() == 0)
   {
       for (int i=0; i < num_entries; i ++)
       {
            QWidget* _widget = (stages_box_layout->itemAt(i)->widget());
            QLCDNumber* lbl = _widget->findChild<QLCDNumber*>("number");
            lbl->display(i+1);
        }
   }
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
    num->setStyleSheet(stsh);
    name->setStyleSheet(stsh);
    button_box->setStyleSheet(stsh);
    stages_box->setStyleSheet(stsh);

}

ContractWidget::~ContractWidget()
{
   if (stages_box_layout->itemAt(0)->spacerItem() == 0) delete dummy;
}


