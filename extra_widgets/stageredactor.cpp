#include "stageredactor.h"
#include "ui_stageredactor.h"


void stageRedactor::applyChanges()
{
    if (qobject_cast<Stage*>(_stage))
    {
        _stage->setStartDate(ui->_start_date_edit->date());
        _stage->setFinishDate(ui->_finish_date_edit->date());
        _stage->setStageName(ui->textEdit->toPlainText());
    }

}


void stageRedactor::showDeleteDialog()
{
    DleteDialog *deleteDialog = new DleteDialog(0);
    deleteDialog->setLabelText("Удалить \"" + _stage->getStageName() + " \" ?");

    connect(deleteDialog, & DleteDialog::accepted, _stage, &Stage::deleteStageRequestHandler);
    connect(deleteDialog, & DleteDialog::accepted, this, &stageRedactor::disconnectIfDeleted);
    connect(deleteDialog, & DleteDialog::accepted, this, &stageRedactor::close);

    deleteDialog->show();
}

void stageRedactor::disconnectIfDeleted()
{
    disconnect(_parent, &QDialog::accepted, this, &stageRedactor::applyChanges);
}

stageRedactor::stageRedactor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stageRedactor)
{
    //setStyleSheet("text-align: middle; background-color: rgb(20, 20, 20); width: 10px; "
     //                       "color: rgb(255, 255, 255); border: 1px solid black;");

    _parent = qobject_cast<QDialog*>(parent);
    ui->setupUi(this);
    ui->_start_date_edit->setDate(QDate::currentDate());
    ui->_finish_date_edit->setDate(QDate::currentDate());
    ui->_start_date_edit->setCalendarPopup(true);
    ui->_finish_date_edit->setCalendarPopup(true);

    connect(_parent, &QDialog::accepted, this, &stageRedactor::applyChanges);
    connect(ui->pushButton, &QPushButton::clicked, this, &stageRedactor::showDeleteDialog);

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
   // connect(this, &stageRedactor::deleteStage, _stage, &stageRedactor::showDeleteDialog);

}
void stageRedactor::setNoDeletion()
{
    this->ui->pushButton->setVisible(false);
}


