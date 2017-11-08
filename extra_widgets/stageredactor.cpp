#include "stageredactor.h"
#include "ui_stageredactor.h"


void stageRedactor::applyChanges()
{
    _stage->setStartDate(ui->_start_date_edit->date());
    _stage->setFinishDate(ui->_finish_date_edit->date());
    _stage->setStageName(ui->textEdit->toPlainText());

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

//    connect(this, change(), this, apply_changes());

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
}
