#include "stageredactor.h"
#include "ui_stageredactor.h"


void stageRedactor::applyChanges()
{
    _stage->setStartDate(ui->_start_date_edit->date());
    _stage->setFinishDate(ui->_finish_date_edit->date());
    _stage->setStageName(ui->textEdit->toPlainText());

}

void stageRedactor::deleteStage()
{

    qDebug() << "Отправка сигнала на удаление к Stage";
    _stage->;
    this->close();
}

void stageRedactor::showDeleteDialog()
{
    DeleteDialog *deleteDialog = new DeleteDialog(0);
    deleteDialog->setModal(true);

    connect(deleteDialog, &DeleteDialog::accepted, this, &stageRedactor::deleteStage);
    deleteDialog->show();
}

stageRedactor::stageRedactor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stageRedactor)
{
    ui->setupUi(this);
    ui->_start_date_edit->setDate(QDate::currentDate());
    ui->_finish_date_edit->setDate(QDate::currentDate());
    ui->_start_date_edit->setCalendarPopup(true);
    ui->_finish_date_edit->setCalendarPopup(true);

    connect(ui->pushButton, &QPushButton::clicked, this, &stageRedactor::showDeleteDialog);

}

stageRedactor::stageRedactor(QWidget *parent, Stage *stage):
    QWidget(parent),
    ui(new Ui::stageRedactor)
{
    ui->setupUi(this);
    setStage(stage);

    ui->_start_date_edit->setCalendarPopup(true);
    ui->_finish_date_edit->setCalendarPopup(true);

//    connect(this, change(), this, apply_changes());

}

stageRedactor::~stageRedactor()
{
    delete ui;
}

void stageRedactor::setStage(Stage *stage)
{
    _stage=stage;

    ui->_start_date_edit->setDate(_stage->getStartDate());
    ui->_finish_date_edit->setDate(_stage->getFinishDate());
    ui->textEdit->setText(_stage->getStageName());
    connect(this, &stageRedactor::deleteStage, _stage, &stageRedactor::showDeleteDialog);

}

/**class StageDeleteDialog **/
StageDeleteDialog::StageDeleteDialog(QWidget *parent):QDialog(parent)
{
    vlayout = new QVBoxLayout();
    hlayout = new QHBoxLayout();
    setLayout(vlayout);
    msg_label= new QLabel("Удалить этап?", this);
    vlayout->addWidget(msg_label);
    vlayout->addLayout(hlayout);
    ok_button = new QPushButton(this);
    ok_button->setText("Подтвердить");
    hlayout->addWidget(ok_button);
    cancel_button = new QPushButton(this);
    cancel_button ->setText("Отменить");
    hlayout->addWidget(cancel_button);
    connect(ok_button, &QPushButton::clicked, this, &DeleteDialog::accepted);
    connect(ok_button, &QPushButton::clicked, this, &DeleteDialog::close);
    connect(cancel_button, &QPushButton::clicked, this, &DeleteDialog::rejected);
    connect(ok_button, &QPushButton::clicked, this, &DeleteDialog::close);
}

StageDeleteDialog::~StageDeleteDialog()
{
    delete vlayout;
    delete hlayout;
}
