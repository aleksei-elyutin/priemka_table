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

    int num_stages=_contract->getNumStages();
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

void contractRedactorDialog::linkContract(Contract *contract)
{
    _contract=contract;
    ui->textEdit->setText(_contract->getContractName());
    connect(this, &contractRedactorDialog::accepted, this, &contractRedactorDialog::applyChanges);
}


void contractRedactorDialog::applyChanges()
{
    _contract->setContractName(ui->textEdit->toPlainText());

}
