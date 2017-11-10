#include "./extra_widgets/dletedialog.h"
#include "ui_dletedialog.h"

DleteDialog::DleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DleteDialog)
{
    ui->setupUi(this);


}

DleteDialog::~DleteDialog()
{
    delete ui;
}

void DleteDialog::setLabelText(QString text)
{
    ui->label->setText(text);
}
