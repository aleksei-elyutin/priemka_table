#ifndef CONTRACTWIDGET_H
#define CONTRACTWIDGET_H

#include <QFrame>
#include <QVector>
#include <QLayout>
#include <QLabel>

#include "stageprogresswidget.h"
#include "../headers/contract.h"
#include "monheaderwidget.h"
#include "dletedialog.h"
#include "contractredactordialog.h"

class ContractWidget : public QFrame
{
    Q_OBJECT
private:
    QVector <StageProgressWidget*> _stages_widgets;

    Contract* _contract;

    QHBoxLayout *main_layout;
    QLCDNumber *num;
    QLabel *name;

    QWidget *stages_box;
    QVBoxLayout *stages_box_layout;
        QWidget *button_box;
        QHBoxLayout *button_box_layout;


    MonHeaderWidget *header;
    QPushButton *add_stage_button;
    QPushButton *delete_contract_button;
    QPushButton *setup_contract_button;



    void showDeleteDialog();
    void setupContract();

public:
    /*explicit*/ ContractWidget(QWidget *parent, );
    void setContract (Contract* contract);
    ~ContractWidget();



signals:

public slots:
};

#endif // CONTRACTWIDGET_H
