#ifndef CONTRACTREDACTORDIALOG_H
#define CONTRACTREDACTORDIALOG_H

#include <QDialog>
#include <headers/contract.h>
#include <extra_widgets/stageredactor.h>

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

    void linkContract(Contract* contract); /** inline impl */
    void draw();
    void applyChanges();
signals:

private:
    Ui::contractRedactorDialog *ui;
};

#endif // CONTRACTREDACTORDIALOG_H
