#include "contractredactordialog.h"
#include "ui_contractredactordialog.h"

contractRedactorDialog::contractRedactorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contractRedactorDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QWidget::deleteLater);
}

void contractRedactorDialog::draw()
{

    QWidget *stages_box = new QWidget(this);
    QVBoxLayout *vlayout=new QVBoxLayout(stages_box);
    ui->scrollArea->setWidget(stages_box);

    int num_stages=_contract->getNumStages();
    for (int i = 0; i < num_stages; i++)
    {
        stageRedactor *sr = new stageRedactor(stages_box);
        sr->setStage(_contract->getStage(i));
        vlayout->addWidget(sr);

    }
}


contractRedactorDialog::~contractRedactorDialog()
{
    deleteLater();

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
    deleteLater();

}
