#include "contractredactordialog.h"
#include "ui_contractredactordialog.h"

contractRedactorDialog::contractRedactorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contractRedactorDialog)
{
    ui->setupUi(this);

}

void contractRedactorDialog::draw()
{
    QVBoxLayout *vlayout=new QVBoxLayout(ui->scrollArea);

    int num_stages=_contract->getNumber();
    for (int i = 0; i < num_stages; i++)
    {
        stageRedactor *sr = new stageRedactor(this);
        sr->setStage(_contract->getStage(i));
        vlayout->addWidget(sr);
        connect(this, &contractRedactorDialog::accepted, sr, &stageRedactor::applyChanges);
    }
}

contractRedactorDialog::~contractRedactorDialog()
{
    delete ui;
}
