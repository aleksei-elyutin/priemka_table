#include "stageprogresswidget.h"


StageProgressWidget::StageProgressWidget(QWidget *parent) : QFrame(parent)
{


    setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                       "color: rgb(255, 255, 255); border: 0px solid black;");
    //setStyleSheet("border: 2px solid grey; background-color: rgb(250, 250, 250); ");

    _widget_layout = new QVBoxLayout(this);
    _widget_layout->setSpacing ( 1);
    _widget_layout->setContentsMargins(3,1,3,1);




    /*Создание кнопок изменить, удалить и лейбла названия контракта*/
    _name_button_box  = new QWidget(this); //!!!!
    _name_button_box->setMinimumHeight(30);
    _name_button_box->setMaximumHeight(30);
    _name_button_box->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                    "color: rgb(255, 255, 255); border: 0px solid black;");
    QHBoxLayout *hLayout = new QHBoxLayout(_name_button_box);
    hLayout->setMargin(0);
    hLayout->setSpacing(3);
    _stage_name = new QLabel(_name_button_box);
    _stage_name->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                               "color: rgb(255, 255, 255); border: 0px solid black;");
    hLayout->addWidget(_stage_name);

    QSpacerItem *hspacer = new QSpacerItem(50,30,QSizePolicy::Expanding,QSizePolicy::Expanding);
    hLayout->addItem(hspacer);

    setup_stage_button = new QPushButton (QString("..."),_name_button_box);
    setup_stage_button->setMinimumHeight(30);
    setup_stage_button->setMaximumHeight(30);
    setup_stage_button->setMinimumWidth(30);
    setup_stage_button->setMaximumWidth(30);
    hLayout->addWidget(setup_stage_button);
    connect(setup_stage_button, &QPushButton::clicked, this, &StageProgressWidget::setupStage);

    delete_stage_button = new QPushButton (QString("X"),_name_button_box);
    delete_stage_button->setMinimumHeight(30);
    delete_stage_button->setMaximumHeight(30);
    delete_stage_button->setMinimumWidth(30);
    delete_stage_button->setMaximumWidth(30);
    hLayout->addWidget(delete_stage_button);
    connect(delete_stage_button, &QPushButton::clicked, this, &StageProgressWidget::showDeleteDialog);

    _widget_layout->addWidget(_name_button_box);

     /** Создание чекбоксов "Выполнено..." **/

    QWidget *chkBoxesContainer = new QWidget(this);
    chkBoxesContainer->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                     "color: rgb(255, 255, 255); border: 0px solid black;");
    QHBoxLayout *chkBoxesContainerLayout = new QHBoxLayout(chkBoxesContainer);

    _done20_checkbox = new QCheckBox (QString("20 дней осталось"),chkBoxesContainer);
    _done20_checkbox->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                    "color: rgb(255, 255, 255); border: 0px solid black;");
    chkBoxesContainerLayout->addWidget(_done20_checkbox);

    _done10_checkbox = new QCheckBox (QString("10 дней осталось"),chkBoxesContainer);
    _done10_checkbox->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                    "color: rgb(255, 255, 255); border: 0px solid black;");
    chkBoxesContainerLayout->addWidget(_done10_checkbox);

    _done_checkbox = new QCheckBox (QString("Выполнено"),chkBoxesContainer);
    _done_checkbox->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                  "color: rgb(255, 255, 255); border: 0px solid black;");
    chkBoxesContainerLayout->addWidget(_done_checkbox);

    _widget_layout->addWidget(chkBoxesContainer);


    /*Создание прогрессбара и сетки*/
    //_progress_box = new QWidget(this);
    _monheader = new MonHeaderWidget(this);
    _monheader->setNamesVisible(false);   ///Изменить на false
    _monheader->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                              "color: rgb(255, 255, 255); border: 1px solid grey;");
    _monheader->setVerticalSize(30);
    _progress = new QProgressBar(_monheader);
    _widget_layout->addWidget(_monheader);

    /*Создание меток*/
    _startfinish_labels_box = new QWidget(this);
    _startfinish_labels_box->setMinimumHeight(20);
    _startfinish_labels_box->setMaximumHeight(20);
    _startfinish_labels_box->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                           "color: rgb(255, 255, 255); border: 0px solid black;");
    _start_date_label = new QLabel(_startfinish_labels_box);
     _start_date_label->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                      "color: rgb(255, 255, 255); border: 0px solid black;");
    _finish_date_label = new QLabel(_startfinish_labels_box);
    _finish_date_label->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
                                               "color: rgb(255, 255, 255); border: 0px solid black;");

    _widget_layout->addWidget(_startfinish_labels_box);


}
void StageProgressWidget::setStage(Stage *stage)
{
    _stage=stage;

    _done20_checkbox->setChecked(_stage->getLeft20DoneStatus());
    connect (_done20_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft20Status);
    connect (_done20_checkbox, &QCheckBox::stateChanged, this, &StageProgressWidget::draw);
    _done10_checkbox->setChecked(_stage->getLeft10DoneStatus());
    connect (_done10_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft10Status);
    connect (_done10_checkbox, &QCheckBox::stateChanged, this, &StageProgressWidget::draw);
    _done_checkbox->setChecked(_stage->getDoneStatus());
    connect (_done_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setDoneStatus);
    connect (_done_checkbox, &QCheckBox::stateChanged, this, &StageProgressWidget::draw);

    _stage_name->setText(_stage->getStageName());

    draw();
}

void StageProgressWidget::draw()
{

    QDate _today = QDate::currentDate();

    _curr_start_date = _stage->getStartDate(); _curr_finish_date = _stage->getFinishDate();


    if (_curr_finish_date.year() > _today.year())
    {
        _curr_finish_date.setDate(_today.year(), 12, 31);
    }
    if (_curr_start_date.year() < _today.year())
    {
        _curr_start_date.setDate(_today.year(), 1, 1);
    }

    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));

    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);

    _progress->setMinimum(_curr_start_date.dayOfYear()); //!!!!
    _progress->setMaximum(_curr_finish_date.dayOfYear()); //!!!!

    _progress->setValue(_today.dayOfYear());
    _progress->setFormat("Осталось дней:"+QString::number(_today.daysTo(_stage->getFinishDate())));

    //qDebug() << _today.daysTo(_stage->getFinishDate());

    if ((_today.daysTo(_stage->getFinishDate()) <= 10)&(!_stage->getLeft10DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar { border: 1px solid grey; background-color: rgba(180, 180, 180, 50); text-align: middle; border-radius: 0px;} \
        QProgressBar::chunk {background-color: rgba(255, 0, 0, 50); width: 3px; margin: 0px;}");  //Устанавливаем красные chunk'и  и серую заливу


    } else if ((_today.daysTo(_stage->getFinishDate()) <= 20)&(!_stage->getLeft20DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar { border: 1px solid grey; background-color: rgba(180, 180, 180, 50); text-align: middle; border-radius: 0px;} \
        QProgressBar::chunk {background-color: rgba(255, 255, 0, 50); width: 3px; margin: 0px;}");  //Устанавливаем желтые chunk'и  и серую заливу
    } else
    {
        _progress->setStyleSheet("QProgressBar { border: 1px solid grey; background-color: rgba(180, 180, 180, 50); text-align: middle; border-radius: 0px;} \
        QProgressBar::chunk {background-color: rgba(0, 255, 0, 50); width: 3px; margin: 0px;}");  //Устанавливаем зеленые chunk'и  и серую заливу
    }


    QResizeEvent rse = QResizeEvent(QSize(),QSize());
    resizeEvent(&rse);
    updateStartFinishLabels();

}

void StageProgressWidget::updateStartFinishLabels()
{

    /** Обновление лейблов даты начала и конца этапа */
    double _size_factor =  _monheader->getSizeFactor();

    _start_date_label->setText(_stage->getStartDate().toString("dd.MM.yyyy"));
    _start_date_label->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0,100,20);
//    _start_date_label->setStyleSheet("text-align: middle; background-color: rgb(70, 70, 70); width: 10px; "
//                                     "color: rgb(255, 255, 255); border: 0px solid black;");


    _finish_date_label->setText(_stage->getFinishDate().toString("d.MM.yyyy"));
    _finish_date_label->setGeometry((_curr_finish_date.dayOfYear()-1)*_size_factor, 0, 100,20);
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
    connect(dial, &QDialog::accepted, this, &StageProgressWidget::draw);
    connect(dial, &QDialog::accepted, _stage, &Stage::imChanged);

}


void StageProgressWidget::showDeleteDialog()
{
    DleteDialog *dleteDialog = new DleteDialog(0);
    dleteDialog->setLabelText("Удалить контракт \"" + _stage->getStageName() + " \" ?");

    connect(dleteDialog, & DleteDialog::accepted, _stage, &Stage::deleteStageRequestHandler);
    connect(dleteDialog, & DleteDialog::accepted, this, &StageProgressWidget::deleteRequested);
    dleteDialog->show();
}

void StageProgressWidget::resizeEvent(QResizeEvent *event)
{

    double _size_factor =  _monheader->getSizeFactor();
    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));

    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);
    _start_date_label->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0,100,20);
    _finish_date_label->setGeometry((_curr_finish_date.dayOfYear()-1)*_size_factor, 0, 100,20);
}


/*StageProgressWidget::StageProgressWidget(QWidget *parent, Stage &stage)
{

}*/

