#include "stageprogresswidget.h"


StageProgressWidget::StageProgressWidget(QWidget *parent) : QFrame(parent)
{

    _selected_year = QDate::currentDate().year();
    setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    setStyleSheet("text-align: middle; background-color: rgba(90, 90, 90, 0); width: 10px; "
                       "color: rgb(255, 255, 255); border: 0px solid black;");


    _widget_layout = new QHBoxLayout(this);
    _widget_layout->setSpacing (7);
    _widget_layout->setContentsMargins(3,1,3,1);
   // _widget_layout->setStretch(0,1);
   // _widget_layout->setStretch(1,1);

    _stage_number = new QLCDNumber(this);
    _stage_number->setStyleSheet("text-align: middle; background-color: rgba(0, 0, 0, 0); width: 10px; "
                                  "color: rgba(255, 255, 255); border: 0px;");
    _stage_number->setMinimumWidth(50);
    _stage_number->setMinimumHeight(40);
    _stage_number->setMaximumWidth(50);
    _stage_number->setMaximumHeight(40);
    _stage_number->setObjectName("number");
    _widget_layout->addWidget( _stage_number);

    /*Создание прогрессбара и сетки*/
    //_progress_box = new QWidget(this);
    _monheader = new MonHeaderWidget(this);
    _monheader->setNamesVisible(false);   ///Изменить на false
    _monheader->setStyleSheet("text-align: middle; background-color: rgba(0, 0, 0, 0); width: 10px; "
                              "color: rgba(255, 255, 255); border: 1px solid rgba(120,120,120,150);");
    _monheader->setVerticalSize( _vert_size);
    _progress = new QProgressBar(_monheader);

    _monheader->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    _widget_layout->addWidget(_monheader);


    //_elements_box - content_box_layout(QHBoxLayout)
   // _elements_box = new QWidget(_monheader);
    _elements_box_layout = new QVBoxLayout(_monheader);
    _elements_box_layout->setContentsMargins(0,0,0,0);
     _elements_box_layout->setSpacing (0);
   // _widget_layout->addWidget(_elements_box);


    _top_box = new QWidget(_monheader);
    _top_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                           "color: rgb(255, 255, 255); border: 0px solid black;");
    _top_box->setMaximumHeight(20);
    _top_box_layout = new QHBoxLayout(_top_box);
    _top_box_layout->setSpacing(0);
   _top_box_layout->setContentsMargins(0,0,0,0);

    //_top_box - top_box_layout(QHBoxLayout) :
            //button_box
            //spacer
            //year_select_box

    //_startfinish_labels_box - bottom_box_layout(QHBoxLayout):
            //

    /*Создание кнопок изменить, удалить и лейбла названия контракта*/
  /*  _name_button_box  = new QWidget(this); //!!!!
    _name_button_box->setMinimumHeight(30);
    //_name_button_box->setMaximumHeight(30);
    _name_button_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                    "color: rgb(255, 255, 255); border: 0px solid black;");
    _name_button_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    QHBoxLayout *hLayout = new QHBoxLayout(_name_button_box);

    hLayout->setContentsMargins(0,0,0,0);
    //hLayout->setSpacing(3);
    _stage_name = new QLabel(_name_button_box);
    _stage_name->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    _stage_name->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                               "color: rgb(255, 255, 255); border: 0px solid black;");
    _stage_name->setWordWrap(true);
    hLayout->addWidget(_stage_name);
    QSpacerItem *hspacer = new QSpacerItem(50,20,QSizePolicy::Expanding,QSizePolicy::Expanding);
    hLayout->addItem(hspacer);*/


     /** Создание лейбла остатка дней и чекбоксов контрольных точек **/

    _status_box = new QWidget(_top_box);
    _status_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                     "color: rgba(255, 255, 255, 120); border: 0px solid black;");
    QHBoxLayout *_status_box_layout = new QHBoxLayout(_status_box);
    _status_box_layout->setContentsMargins(0,0,0,0);
    _status_box_layout->setStretch(0,0);
    _status_box_layout->setStretch(1,0);
    _status_box_layout->setStretch(2,0);

    QLabel *checkpoints_label = new QLabel("КТ:", _status_box);
    _status_box_layout->addWidget(checkpoints_label);

    _done20_checkbox = new QCheckBox (QString( "20 дней "),_status_box);
    _done20_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                    "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                    "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90);"
                                    "width: 15px; height: 15px}"
                                    );


    _done20_checkbox->setObjectName("_done20_checkbox");
     _done20_checkbox->setMinimumWidth(70);
    _status_box_layout->addWidget(_done20_checkbox);

    _done10_checkbox = new QCheckBox (QString("10 дней "),_status_box);
    _done10_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                    "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                    "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90); "
                                    "width: 15px; height: 15px}");

    _done10_checkbox->setObjectName("_done10_checkbox");
    _done10_checkbox->setMinimumWidth(70);
    _status_box_layout->addWidget(_done10_checkbox);

    _done_checkbox = new QCheckBox (QString("выполнено"),_status_box);
    _done_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90);"
                                  "width: 15px; height: 15px}");
    _done_checkbox->setObjectName("_done_checkbox");
    _done_checkbox->setMinimumWidth(80);
    _status_box_layout->addWidget(_done_checkbox);

    // _done_checkbox->setStyleSheet("QCheckBox::indicator {background-color: rgba(255, 255, 255, 120);}");
    _top_box_layout->addWidget(_status_box);


    QSpacerItem *top_box_spacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);
    _top_box_layout->addItem(top_box_spacer);

    /*Создание кнопок изменить, удалить*/
   _button_box = new QWidget(_top_box);
   _button_box_layout = new QHBoxLayout(_button_box);
   _button_box_layout->setContentsMargins(0,0,0,0);

   setup_stage_button = new QPushButton (_button_box);
   QPixmap pen_pixmap("://resources/pen.png");
   QIcon pen_icon(pen_pixmap);
   setup_stage_button->setIcon(pen_icon);
   setup_stage_button->setIconSize(QSize(20,20));
   setup_stage_button->setStyleSheet("QPushButton:hover{background-color: rgb(80, 80, 80);}");
   setup_stage_button->setMinimumHeight(20);
   setup_stage_button->setMaximumHeight(20);
   setup_stage_button->setMinimumWidth(20);
   setup_stage_button->setMaximumWidth(20);
   setup_stage_button->setToolTip("Изменить этап");
   //setup_stage_button->setVisible(false);
    _button_box_layout->addWidget(setup_stage_button);
   connect(setup_stage_button, &QPushButton::clicked, this, &StageProgressWidget::setupStage);

   delete_stage_button = new QPushButton (_button_box); //QString("X"),
   QPixmap delete_pixmap(":/resources/gnome_edit_delete.png");
   QIcon delete_icon(delete_pixmap);
   delete_stage_button->setIcon(delete_icon);
   delete_stage_button->setIconSize(QSize(20,20));
   delete_stage_button->setStyleSheet("QPushButton:hover{background-color: rgb(80, 80, 80);}");
   delete_stage_button->setMinimumHeight(20);
   delete_stage_button->setMaximumHeight(20);
   delete_stage_button->setMinimumWidth(20);
   delete_stage_button->setMaximumWidth(20);
   delete_stage_button->setToolTip("Удалить этап");
   _button_box_layout->addWidget(delete_stage_button);
   connect(delete_stage_button, &QPushButton::clicked, this, &StageProgressWidget::showDeleteDialog);

   _top_box_layout->addWidget(_button_box);


    /* Создание кнопок выбора года для отображения **/
    QWidget *year_selector_box = new QWidget(_top_box);
    year_selector_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                           "color: rgb(255, 255, 255); border: 0px solid black;");
    year_selector_box->setMaximumHeight(20);
    QHBoxLayout *year_selector_box_Layout = new QHBoxLayout(year_selector_box);
    year_selector_box_Layout->setContentsMargins(0,0,10,0);
    year_selector_box_Layout->setSpacing(0);
    decrease_year_button = new QPushButton (year_selector_box);
    QPixmap decrease_pixmap(":/resources/left_grey.png");
    QIcon decrease_icon(decrease_pixmap);
    decrease_year_button->setIcon(decrease_icon);
    decrease_year_button->setIconSize(QSize(20,20));
    decrease_year_button->setStyleSheet("QPushButton:hover{background-color: rgba(80, 80, 80, 90);}");
    decrease_year_button->setMinimumHeight(20);
    decrease_year_button->setMaximumHeight(20);
    decrease_year_button->setMinimumWidth(20);
    decrease_year_button->setMaximumWidth(20);
    decrease_year_button->setObjectName("decrease");
    year_selector_box_Layout ->addWidget(decrease_year_button);
    connect(decrease_year_button, &QPushButton::clicked, this, &StageProgressWidget::selectYear);

    year_label_btn = new QPushButton (QString::number(_selected_year),year_selector_box);
    year_label_btn->setMinimumHeight(20);
    year_label_btn->setMaximumHeight(20);
    year_label_btn->setMinimumWidth(40);
    year_label_btn->setMaximumWidth(40);
    year_label_btn->setObjectName("restore");
    year_label_btn->setStyleSheet("QPushButton:hover{background-color: rgba(80, 80, 80, 90);}");
    connect(year_label_btn, &QPushButton::clicked, this, &StageProgressWidget::selectYear);
    year_selector_box_Layout ->addWidget(year_label_btn);

    increase_year_button = new QPushButton (year_selector_box);
    QPixmap increase_pixmap(":/resources/right_grey.png");
    QIcon increase_icon(increase_pixmap);
    increase_year_button->setIcon(increase_icon);
    increase_year_button->setStyleSheet("QPushButton:hover{background-color: rgba(80, 80, 80, 90);}");
    increase_year_button->setIconSize(QSize(20,20));
    increase_year_button->setMinimumHeight(20);
    increase_year_button->setMaximumHeight(20);
    increase_year_button->setMinimumWidth(20);
    increase_year_button->setMaximumWidth(20);
    increase_year_button->setObjectName("increase");
    year_selector_box_Layout ->addWidget(increase_year_button);
    connect(increase_year_button, &QPushButton::clicked, this, &StageProgressWidget::selectYear);

    _top_box_layout->addWidget(year_selector_box);

    /** Лейбл остатка дней*/
    _days_left_label = new QLabel(_top_box);

    _elements_box_layout->addWidget(_top_box);



    /*Создание меток*/
    _startfinish_labels_box = new QWidget(_monheader);
    _startfinish_labels_box->setMinimumHeight(20);
    _startfinish_labels_box->setMaximumHeight(20);
    _startfinish_labels_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                           "color: rgb(255, 255, 255); border: 0px solid black;");
    _start_date_label = new QLabel(_startfinish_labels_box);
//     _start_date_label->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
//                                      "color: rgb(255, 255, 255); border: 0px solid black;");
    _finish_date_label = new QLabel(_startfinish_labels_box);
//    _finish_date_label->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
//                                               "color: rgb(255, 255, 255); border: 0px solid black;");

   _elements_box_layout->addWidget(_startfinish_labels_box);


}
void StageProgressWidget::setStage(Stage *stage)
{
    _stage=stage;

    connect(_stage, &Stage::stageChanged, this, &StageProgressWidget::draw);


    connect (_done20_checkbox, &QCheckBox::stateChanged, this, &StageProgressWidget::setCheckBoxHandler);
    connect (_done10_checkbox, &QCheckBox::stateChanged, this, &StageProgressWidget::setCheckBoxHandler);
    connect (_done_checkbox,  &QCheckBox::stateChanged, this, &StageProgressWidget::setCheckBoxHandler);

    draw();
}

void StageProgressWidget::setCheckBoxHandler(int state)
{
    int days_left = QDate::currentDate().daysTo(_stage->getFinishDate());

    if (sender()->objectName() == "_done20_checkbox")
    {
        if (!_stage->setLeft20Status(state)) qDebug() << "setCheckBoxHandler: setLeft20Status state not set!";
        else
        {
            if ((_stage->getLeft20DoneStatus()) & (days_left <= 10))
            {
                _done10_checkbox->setCheckable(true);
                //_done_checkbox->setCheckable(true);
            }
            else
            {
                _done10_checkbox->setChecked(false);
                _done_checkbox->setChecked(false);
                _done10_checkbox->setCheckable(false);
                _done_checkbox->setCheckable(false);
               // if (!_stage->setLeft10Status(Qt::Unchecked)) qDebug() << "setCheckBoxHandler: setLeft10Status state not set!";
               // if (!_stage->setDoneStatus(Qt::Unchecked)) qDebug() << "setCheckBoxHandler: setDoneStatus state not set!";
            }
        }
    }

    else if (sender()->objectName() == "_done10_checkbox")
    {
        if (!_stage->setLeft10Status(state)) qDebug() << "setCheckBoxHandler: setLeft20Status state not set!";
        else
        {
            if ((_stage->getLeft10DoneStatus())  & (days_left <= 0)) _done_checkbox->setCheckable(true);
            else
            {
                 _done_checkbox->setChecked(false);
                 _done_checkbox->setCheckable(false);
               //  if (!_stage->setDoneStatus(Qt::Unchecked)) qDebug() << "setCheckBoxHandler: setDoneStatus state not set!";
            }

        }
    }
    else if (sender()->objectName() == "_done_checkbox")
    {
         if (!_stage->setDoneStatus(state)) qDebug() << "setDoneStatus state not set!";
    }
    else qDebug() << "setCheckBoxHandler: Object name not responsed!";

    draw();

}

void StageProgressWidget::draw()
{

    int days_left = QDate::currentDate().daysTo(_stage->getFinishDate());
    if (days_left <= 20) _done20_checkbox->setCheckable(true);
    else _done20_checkbox->setCheckable(false);
    _done20_checkbox->setChecked(_stage->getLeft20DoneStatus());

    if ((_stage->getLeft20DoneStatus()) & (days_left <= 10))
    {
        _done10_checkbox->setCheckable(true);
        _done10_checkbox->setChecked(_stage->getLeft10DoneStatus());

        if ((_stage->getLeft10DoneStatus()) & (days_left <= 0))
        {
             _done_checkbox->setCheckable(true);
             _done_checkbox->setChecked(_stage->getDoneStatus());
        }
        else _done_checkbox->setCheckable(false);
    }
    else
    {
         _done10_checkbox->setCheckable(false);
         _done_checkbox->setCheckable(false);
    }



    _stage->calculatePriority();

    //_stage_name->setText(_stage->getStageName());

    setToolTip(_stage->getStageName());


    QDate _today = QDate::currentDate();

    _curr_start_date = _stage->getStartDate(); _curr_finish_date = _stage->getFinishDate();


    if (_curr_finish_date.year() >  _selected_year)
    {
        _curr_finish_date.setDate(_selected_year, 12, 31);
    }
    if (_curr_start_date.year() <  _selected_year)
    {
        _curr_start_date.setDate(_selected_year, 1, 1);
    }
    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));
    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);
    _progress->setMinimum(_curr_start_date.dayOfYear()); //!!!!
    _progress->setMaximum(_curr_finish_date.dayOfYear()); //!!!!


    if (_selected_year < QDate::currentDate().year())
    {
         //_today = QDate( _selected_year, 12, 31);
         _progress->setValue(_progress->maximum());
    }
    else if (_selected_year > QDate::currentDate().year())
    {
         //_today = QDate( _selected_year, 1, 1);
         _progress->setValue(_progress->minimum());
    }
    else
    {
        _progress->setValue(_today.dayOfYear());
        if (_curr_finish_date.dayOfYear() < _today.dayOfYear())  _progress->setValue(_progress->maximum());
    }


    _progress->setFormat("");
    if (days_left >=0 )
    {
        if (days_left == 0 ) _days_left_label->setText("Истекает сегодня!");
        else _days_left_label->setText("Осталось дней: "+QString::number(days_left));

    }
    else if (_stage->getDoneStatus())
    {
        _days_left_label->setText("Завершено");
    }
    else
    {
        _days_left_label->setText("Просрочено дней: "+QString::number(abs(days_left)));
    }



    if (_stage->getPriority() == Stage::Overdude)//((days_left <= 10)&(!_stage->getLeft10DoneStatus()))
    {
        if (days_left < 0)
        {

            if ((days_left < 0)&(_stage->getDoneStatus()))
            {
                _progress->setStyleSheet("QProgressBar {  border: 1px solid rgba(0, 128, 255, 60); background-color: rgba(0, 128, 255, 20); text-align: middle; border-radius: 0px;} \
                QProgressBar::chunk {background-color: rgba(0, 128, 255, 100); width: 3px; margin: 0px;}");  //Устанавливаем синие chunk'и и серую заливу
                setStyleSheet("QWidget {background-color: rgba(0, 128, 255, 50)}; QWidget:hover{background-color: rgba(0, 128, 255, 50);}");
            }
            else
            {
                _progress->setStyleSheet("QProgressBar {border: 1px solid rgba(255, 0, 0, 60); background-color: rgba(255, 0, 0, 20); text-align: middle; border-radius: 0px;} \
                QProgressBar::chunk {background-color: rgba(255, 0, 0, 100); width: 3px; margin: 0px;}");
                setStyleSheet("QWidget {background-color: rgba(255, 0, 0, 50)}; QWidget:hover{background-color: rgba(255, 0, 0, 50);}");
            }
        }
        else
        {
            _progress->setStyleSheet("QProgressBar {border: 1px solid rgba(200, 200, 200, 60); background-color: rgba(200, 200, 200, 50); text-align: middle; border-radius: 0px;} \
            QProgressBar::chunk {background-color: rgba(255, 0, 0, 100); width: 3px; margin: 0px;}");
            setStyleSheet("QWidget:hover{background-color: rgba(255, 0, 0, 50);}");
        }
    }
    else if (_stage->getPriority() == Stage::Overdude_10)//((days_left <= 10)&(!_stage->getLeft10DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar {border: 1px solid rgba(255, 0, 0, 60); background-color: rgba(255, 0, 0, 50); text-align: middle; border-radius: 0px;} \
        QProgressBar::chunk {background-color: rgba(255, 0, 0, 100); width: 3px; margin: 0px;}");  //Устанавливаем красные chunk'и  и серую заливу
        setStyleSheet("QWidget:hover{background-color: rgba(255, 0, 0, 50);}");

    }
    else if (_stage->getPriority() == Stage::Overdude_20) //((days_left <= 20)&(!_stage->getLeft20DoneStatus())&(!_stage->getLeft10DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar { border: 1px solid rgba(255, 255, 0, 60); background-color: rgba(255, 255, 0, 20); text-align: middle; border-radius: 0px;} \
        QProgressBar::chunk {background-color: rgba(255, 255, 0, 100); width: 3px; margin: 0px;}");  //Устанавливаем желтые chunk'и  и серую заливу
       setStyleSheet("QWidget:hover{background-color: rgba(255, 255, 0, 50);}");
    }
    else if (_stage->getPriority() == Stage::Normal)
    {
       /* if (days_left < 0)
        {
            _progress->setStyleSheet("QProgressBar {  border: 1px solid grey; background-color: rgba(180, 180, 180, 50); text-align: middle; border-radius: 0px;} \
            QProgressBar::chunk {background-color: rgba(0, 128, 255, 100); width: 3px; margin: 0px;}");  //Устанавливаем зеленые chunk'и  и серую заливу
            setStyleSheet("QWidget {background-color: rgba(0, 128, 255, 50)}; QWidget:hover{background-color: rgba(0, 128, 255, 50);}");
        }
        else*/
        {
            _progress->setStyleSheet("QProgressBar {  border: 1px solid rgba(0, 255, 0, 60); background-color: rgba(0, 255, 0, 20); text-align: middle; border-radius: 0px;} \
            QProgressBar::chunk {background-color: rgba(0, 255, 0, 100); width: 3px; margin: 0px;}");  //Устанавливаем зеленые chunk'и  и серую заливу
            setStyleSheet("QWidget:hover{background-color: rgba(0, 255, 0, 50);}");
        }
    }


//    setToolTip(QString("Этап. Приоритет: " + QString::number(_stage->getPriority()) + ", "
//                       "дней до конца: " + QString::number(QDate::currentDate().daysTo(_stage->getFinishDate()))));

   /* QResizeEvent rse = QResizeEvent(QSize(),QSize());
    resizeEvent(&rse);*/
    resize();

}

void StageProgressWidget::updateStartFinishLabels()
{

    /** Обновление лейблов даты начала и конца этапа */



    /** Попробовать исправить, если будет время */

    double _size_factor =  _monheader->getSizeFactor();

    int maximum = _monheader->width();
    int minimum = 0;
    int label_width = 65;

    int _start_label_x_position = (_curr_start_date.dayOfYear()-1)*_size_factor-label_width;
    if ((_start_label_x_position + label_width)>(maximum-label_width) ) _start_label_x_position = _start_label_x_position-2*label_width;
    if ((_start_label_x_position)<(minimum)) _start_label_x_position = minimum;

    int _finish_label_x_position = (_curr_finish_date.dayOfYear()-1)*_size_factor;
    if (_finish_label_x_position  > (maximum-label_width))  _finish_label_x_position = maximum-label_width;

    _start_date_label->setText(_stage->getStartDate().toString("dd.MM.yyyy"));
    _start_date_label->setGeometry(_start_label_x_position, 0,label_width,20);
//    _start_date_label->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
//                                     "color: rgb(255, 255, 255); border: 0px solid black;");


    _finish_date_label->setText(_stage->getFinishDate().toString("dd.MM.yyyy"));
    _finish_date_label->setGeometry(_finish_label_x_position, 0, label_width,20);
//    _finish_date_label->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
//                                      "color: rgb(255, 255, 255); border: 0px solid black;");

}


void StageProgressWidget::setupStage()
{
    QDialog *dial = new QDialog(0);
    QVBoxLayout *dial_layout = new QVBoxLayout(dial);
    stageRedactor *sr = new stageRedactor (dial);
    sr->setStage(_stage);
    sr->setNoDeletion();
    dial_layout->addWidget(sr);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(dial);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    dial_layout->addWidget(buttonBox);
    dial->show();

    connect(buttonBox, &QDialogButtonBox::accepted,dial, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected,dial, &QDialog::reject);
    connect(dial, &QDialog::accepted, sr, &stageRedactor::applyChanges);
    connect(dial, &QDialog::accepted, dial, &stageRedactor::deleteLater);

    connect(dial, &QDialog::rejected, dial, &QDialog::deleteLater );
    //connect(dial, &QDialog::accepted, this, &StageProgressWidget::draw);
    //connect(dial, &QDialog::accepted, _stage, &Stage::stageChanged);

}


void StageProgressWidget::showDeleteDialog()
{
    DleteDialog *dleteDialog = new DleteDialog(0);
    dleteDialog->setLabelText("Удалить этап \"" + _stage->getStageName() + " \" ?");

    connect(dleteDialog, & DleteDialog::accepted, _stage, &Stage::deleteStageRequestHandler);
    connect(dleteDialog, & DleteDialog::accepted, this, &StageProgressWidget::deleteRequested);
    dleteDialog->show();
}

void StageProgressWidget::lock()
{
    islocked = true;
    _done_checkbox->setDisabled(true);
    _done10_checkbox->setDisabled(true);
    _done20_checkbox->setDisabled(true);

    delete_stage_button->setVisible(false);
    setup_stage_button->setVisible(false);

    _status_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                     "color: rgba(255, 255, 255, 120); border: 0px solid black;");

    _done20_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90);"
                                  "width: 15px; height: 15px}");
    _done10_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90);"
                                  "width: 15px; height: 15px}");
    _done_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(100,100,100,90);"
                                  "width: 15px; height: 15px}");
}
void StageProgressWidget::unlock()
{
    islocked = false;
    _done_checkbox->setDisabled(false);
    _done10_checkbox->setDisabled(false);
    _done20_checkbox->setDisabled(false);

    delete_stage_button->setVisible(true);
    setup_stage_button->setVisible(true);

    _status_box->setStyleSheet("text-align: middle; background-color: rgba(70, 70, 70, 0); width: 10px; "
                                     "color: rgba(255, 255, 255, 255); border: 0px solid black;");
    _done20_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(255,255,255,150);"
                                  "width: 15px; height: 15px}");
    _done10_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(255,255,255,150);"
                                  "width: 15px; height: 15px}");
    _done_checkbox->setStyleSheet("QCheckBox::indicator:checked {background-color: rgba(100,100,100,90); "
                                  "image:url(://resources/if_Checkbox Full_58508.png); width: 15px; height: 15px}"
                                  "QCheckBox::indicator:unchecked {background-color: rgba(255,255,255,150);"
                                  "width: 15px; height: 15px}");
}



void StageProgressWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    /*double _size_factor =  _monheader->getSizeFactor();
    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));

    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);
    _days_left_label->setGeometry(_monheader->geometry().width()/2-50,0,120,20);
    updateStartFinishLabels();*/
    resize();
}

void StageProgressWidget::resize()
{
    double _size_factor =  _monheader->getSizeFactor();
    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));

    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);
    _days_left_label->setGeometry(_monheader->geometry().width()/2-50,0,120,20);
    updateStartFinishLabels();
}

void StageProgressWidget::selectYear()
{
    QObject *_sender = sender();
    if (_sender->objectName() == QString("increase")) _selected_year++;
    if (_sender->objectName() == QString("decrease")) _selected_year--;
    if (_sender->objectName() == QString("restore")) _selected_year = QDate::currentDate().year();
    year_label_btn->setText(QString::number(_selected_year));
    draw();
}


void StageProgressWidget::setAlpha(int a)
{
    QString stsh = QString( "background-color: rgba(90, 90, 90,0 ); color: rgba(255, 255, 255, "
                            + QString::number(a) + " ); border: 0px solid grey;" );
    setStyleSheet(stsh);

//    num->setStyleSheet(stsh);
//    name->setStyleSheet(stsh);
//    button_box->setStyleSheet(stsh);
//    stages_box->setStyleSheet(stsh);

}
