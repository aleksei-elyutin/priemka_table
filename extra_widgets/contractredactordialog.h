#ifndef CONTRACTREDACTORDIALOG_H
#define CONTRACTREDACTORDIALOG_H

#include <QDialog>
#include <contract.h>
#include <stageredactor.h>

namespace Ui {
class contractRedactorDialog;
}

class contractRedactorDialog : public QDialog
{
    Q_OBJECT
private:
    Contract* _contract;


public:
    explicit contractRedactorDialog(QWidget *parent = 0);
    ~contractRedactorDialog();

    void linkContract(Contract* contract) {_contract=contract;} /** inline impl */
    void draw();
signals:

private:
    Ui::contractRedactorDialog *ui;
};

#endif // CONTRACTREDACTORDIALOG_H
