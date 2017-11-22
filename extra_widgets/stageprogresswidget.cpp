#include "stageprogresswidget.h"
#include <QGraphicsEffect>


void StageProgressWidget::setCheckBoxesState()
{

}



StageProgressWidget::StageProgressWidget(QWidget *parent) : QFrame(parent)
{


    setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 1px solid black;");
    //setStyleSheet("border: 2px solid grey; background-color: rgb(250, 250, 250); ");
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect -> setBlurRadius(9.0);
        shadowEffect -> setColor(QColor(90, 200, 40, 80));
        shadowEffect -> setOffset(4.0);
    setGraphicsEffect(shadowEffect);
    _widget_layout = new QVBoxLayout(this);
    _widget_layout->setSpacing ( 5);




    /*Создание кнопок изменить, удалить и лейбла названия контракта*/
    _name_button_box  = new QWidget(this); //!!!!
    _name_button_box->setMinimumHeight(30);
    _name_button_box->setMaximumHeight(30);
    _name_button_box->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 1px; border: 0px solid black;");
    QHBoxLayout *hLayout = new QHBoxLayout(_name_button_box);
    hLayout->setMargin(0);
    hLayout->setSpacing(3);
    _stage_name = new QLabel(_name_button_box);
    _stage_name->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px solid black;");
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
    chkBoxesContainer->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    QHBoxLayout *chkBoxesContainerLayout = new QHBoxLayout(chkBoxesContainer);

    _done20_checkbox = new QCheckBox (QString("20 дней осталось"),chkBoxesContainer);
    _done20_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    chkBoxesContainerLayout->addWidget(_done20_checkbox);

    _done10_checkbox = new QCheckBox (QString("10 дней осталось"),chkBoxesContainer);
    _done10_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    chkBoxesContainerLayout->addWidget(_done10_checkbox);

    _done_checkbox = new QCheckBox (QString("Выполнено"),chkBoxesContainer);
    _done_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    chkBoxesContainerLayout->addWidget(_done_checkbox);

    _widget_layout->addWidget(chkBoxesContainer);


    /*Создание прогрессбара и сетки*/
    //_progress_box = new QWidget(this);
    _monheader = new MonHeaderWidget(this);
    _monheader->setNamesVisible(true);   ///Изменить на false
    _progress = new QProgressBar(_monheader);
    _widget_layout->addWidget(_monheader);

    /*Создание меток*/
    _startfinish_labels_box = new QWidget(this);
    _startfinish_labels_box->setMinimumHeight(30);
    _startfinish_labels_box->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 1px solid black;");
    _start_date_label = new QLabel(_startfinish_labels_box);
    _finish_date_label = new QLabel(_startfinish_labels_box);

    _widget_layout->addWidget(_startfinish_labels_box);


}
void StageProgressWidget::setStage(Stage *stage)
{
    _stage=stage;

    _done20_checkbox->setChecked(_stage->getLeft20DoneStatus());
    connect (_done20_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft20Status);
    _done10_checkbox->setChecked(_stage->getLeft10DoneStatus());
    connect (_done10_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft10Status);
    _done_checkbox->setChecked(_stage->getDoneStatus());
    connect (_done_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setDoneStatus);

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

    updateStartFinishLabels();

}

void StageProgressWidget::updateStartFinishLabels()
{

    /** Обновление лейблов даты начала и конца этапа */
    double _size_factor =  _monheader->getSizeFactor();

    _start_date_label->setText(_stage->getStartDate().toString("dd.MM.yyyy"));
    _start_date_label->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0,100,(int)_vert_size);
    _start_date_label->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 0px solid black;");


    _finish_date_label->setText(_stage->getFinishDate().toString("d.MM.yyyy"));
    _finish_date_label->setGeometry((_curr_finish_date.dayOfYear()-1)*_size_factor, 0, 100,(int)_vert_size);
    _finish_date_label->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 0px solid black;");


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
    connect(dial, &QDialog::accepted, _stage, &Stage::imChanged);

}


void StageProgressWidget::showDeleteDialog()
{
    DleteDialog *dleteDialog = new DleteDialog(0);
    dleteDialog->setLabelText("Удалить контракт \"" + _stage->getStageName() + " \" ?");

    connect(dleteDialog, & DleteDialog::accepted, _stage, &Stage::deleteRequest);
    dleteDialog->show();
}

void StageProgressWidget::resizeEvent(QResizeEvent *event)
{

    double _size_factor =  _monheader->getSizeFactor();
    int length = _size_factor*(_curr_start_date.daysTo(_curr_finish_date));

    _progress->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0, length, _vert_size);
    _start_date_label->setGeometry((_curr_start_date.dayOfYear()-1)*_size_factor, 0,100,(int)_vert_size);
    _finish_date_label->setGeometry((_curr_finish_date.dayOfYear()-1)*_size_factor, 0, 100,(int)_vert_size);
}

/*StageProgressWidget::StageProgressWidget(QWidget *parent, Stage &stage)
{

}*/

