#include "stageprogresswidget.h"
#include <QGraphicsEffect>


StageProgressWidget::StageProgressWidget(QWidget *parent, Stage *stage ) : QFrame(parent)
{

//    QAnima

    _stage=stage;
    setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    _widget_layout = new QGridLayout(this);
    _widget_layout->setVerticalSpacing ( 0);

    QWidget* _dock = new QWidget(this);
    _dock->setGeometry(0,0,365*_size_factor,_vert_size);
    _dock->setMaximumSize(365*_size_factor,_vert_size);
    _dock->setMinimumSize(365*_size_factor,_vert_size);

    QWidget* _dates_dock = new QWidget(this);
    _dates_dock->setGeometry(0,0,365*_size_factor,(int)_vert_size/2);
    _dates_dock->setMaximumSize(365*_size_factor,(int)_vert_size/2);
    _dates_dock->setMinimumSize(365*_size_factor,(int)_vert_size/2);

    //setStyleSheet("border: 2px solid grey; background-color: rgb(250, 250, 250); ");
    setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 1px solid black;");


     /*Название этапа*/


    /*Кнопки изменить и удалить*/
    QWidget *button_box = new QWidget(this); //!!!!
    button_box->setMinimumHeight(30);
    button_box->setMaximumHeight(30);

    button_box->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 1px; border: 0px solid black;");
    QHBoxLayout *hLayout = new QHBoxLayout(button_box);
    hLayout->setMargin(0);
    hLayout->setSpacing(3);

    _stage_name = new QLabel(stage->getStageName(),button_box);
    _stage_name->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px solid black;");
    hLayout->addWidget(_stage_name);


    QSpacerItem *hspacer = new QSpacerItem(50,30,QSizePolicy::Expanding,QSizePolicy::Expanding);
    hLayout->addItem(hspacer);

    setup_stage_button = new QPushButton (QString("..."),button_box);
    setup_stage_button->setMinimumHeight(30);
    setup_stage_button->setMaximumHeight(30);
    setup_stage_button->setMinimumWidth(30);
    setup_stage_button->setMaximumWidth(30);
    hLayout->addWidget(setup_stage_button);
    connect(setup_stage_button, &QPushButton::clicked, this, &StageProgressWidget::setupStage);

    delete_stage_button = new QPushButton (QString("X"),button_box);
    delete_stage_button->setMinimumHeight(30);
    delete_stage_button->setMaximumHeight(30);
    delete_stage_button->setMinimumWidth(30);
    delete_stage_button->setMaximumWidth(30);
    hLayout->addWidget(delete_stage_button);
    connect(delete_stage_button, &QPushButton::clicked, this, &StageProgressWidget::showDeleteDialog);


    _widget_layout->addWidget(button_box,0,0);


    /*******/


     /** Чекбоксы "Выполнено..." **/

    QWidget *chkBoxesContainer = new QWidget(this);
    chkBoxesContainer->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    QHBoxLayout *chkBoxesContainerLayout = new QHBoxLayout(chkBoxesContainer);

    _done20_checkbox = new QCheckBox (QString("20 дней осталось"),chkBoxesContainer);
    _done20_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    _done20_checkbox->setChecked(_stage->getLeft20DoneStatus());
    chkBoxesContainerLayout->addWidget(_done20_checkbox);
    connect (_done20_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft20Status);

    _done10_checkbox = new QCheckBox (QString("10 дней осталось"),chkBoxesContainer);
    _done10_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    _done10_checkbox->setChecked(_stage->getLeft10DoneStatus());
    chkBoxesContainerLayout->addWidget(_done10_checkbox);
    connect (_done10_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setLeft10Status);

    _done_checkbox = new QCheckBox (QString("Выполнено"),chkBoxesContainer);
    _done_checkbox->setStyleSheet("background-color: rgb(240, 240, 240); width: 1px; border: 0px;");
    _done_checkbox->setChecked(_stage->getDoneStatus());
    chkBoxesContainerLayout->addWidget(_done_checkbox);
    connect (_done_checkbox, &QCheckBox::stateChanged, _stage, &Stage::setDoneStatus);

    _widget_layout->addWidget(chkBoxesContainer,1,0);



    _today = QDate::currentDate();

    _progress = new QProgressBar(_dock);

    _start_date = stage->getStartDate(); _finish_date = stage->getFinishDate();

    MonHeaderWidget* header = new MonHeaderWidget(this);
    header->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 1px solid grey;");
    _widget_layout->addWidget(header,3,0);


    if (_finish_date.year() > _today.year())
    {
        _finish_date.setDate(_today.year(), 12, 31);
    }
    if (_start_date.year() < _today.year())
    {
        _start_date.setDate(_today.year(), 1, 1);
    }

    int length = _size_factor*(_start_date.daysTo(_finish_date));

    _progress->setGeometry(_start_date.dayOfYear()*_size_factor, 0, length, _vert_size);

    _progress->setMinimum(_start_date.dayOfYear());
    _progress->setMaximum(_finish_date.dayOfYear());

    _progress->setValue(_today.dayOfYear());
    _progress->setFormat("Осталось дней:"+QString::number(_today.daysTo(stage->getFinishDate())));

    //qDebug() << _today.daysTo(stage->getFinishDate());

    if ((_today.daysTo(stage->getFinishDate()) <= 10)&(!_stage->getLeft10DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar { border: 2px solid grey; background-color: rgb(180, 180, 180); text-align: middle; border-radius: 5px;} \
        QProgressBar::chunk {background-color: rgb(255, 0, 0); width: 3px; margin: 0px;}");  //Устанавливаем красные chunk'и  и серую заливу
    } else if ((_today.daysTo(stage->getFinishDate()) <= 20)&(!_stage->getLeft20DoneStatus()))
    {
        _progress->setStyleSheet("QProgressBar { border: 2px solid grey; background-color: rgb(180, 180, 180); text-align: middle; border-radius: 5px;} \
        QProgressBar::chunk {background-color: rgb(255, 255, 0); width: 3px; margin: 0px;}");  //Устанавливаем желтые chunk'и  и серую заливу
    } else
    {
        _progress->setStyleSheet("QProgressBar { border: 2px solid grey; background-color: rgb(180, 180, 180); text-align: middle; border-radius: 5px;} \
        QProgressBar::chunk {background-color: rgb(0, 255, 0); width: 3px; margin: 0px;}");  //Устанавливаем зеленые chunk'и  и серую заливу
    }
    _widget_layout->addWidget(_dock,4,0);

    QLabel *_start_date_label = new QLabel((stage->getStartDate().toString("dd.MM.yyyy")),_dates_dock);
    _start_date_label->setGeometry(_start_date.dayOfYear()*_size_factor, 0,100,(int)_vert_size/2);
    _start_date_label->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 0px solid black;");

    QLabel *_finish_date_label = new QLabel((stage->getFinishDate().toString("d.MM.yyyy")),_dates_dock);
    _finish_date_label->setGeometry(_start_date.dayOfYear()*_size_factor+length, 0, 100,(int)_vert_size/2);
    _finish_date_label->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 0px solid black;");

    _dates_dock->setStyleSheet("background-color: rgb(240, 240, 240); width: 3px; border: 0px solid black;");
    _widget_layout->addWidget(_dates_dock,5,0);



    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect -> setBlurRadius(9.0);
        shadowEffect -> setColor(QColor(0, 0, 0, 160));
        shadowEffect -> setOffset(4.0);
    setGraphicsEffect(shadowEffect);


    setLayout(_widget_layout);
    //_progress->show();
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

/*StageProgressWidget::StageProgressWidget(QWidget *parent, Stage &stage)
{

}*/

