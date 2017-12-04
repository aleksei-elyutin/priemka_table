#include "./extra_widgets/dletedialog.h"
#include "ui_dletedialog.h"

DleteDialog::DleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DleteDialog)
{
    ui->setupUi(this);
 //   setStyleSheet("background-color: rgb(20, 20, 20); color: rgb(255, 255, 255); border: 1px solid rgb(20, 20, 20);");

//    ui->buttonBox->layout()->setSpacing(100);
 //   ui->buttonBox->setStyleSheet("background-color: rgb(100, 100, 100); color: rgb(255, 255, 255); border: 1px solid rgb(50, 50, 50);");

}

DleteDialog::~DleteDialog()
{
    delete ui;
}

void DleteDialog::setLabelText(QString text)
{
    ui->label->setText(text);
}
