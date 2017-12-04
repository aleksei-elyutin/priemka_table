#ifndef CONTRACTWIDGET_H
#define CONTRACTWIDGET_H

#include <QFrame>
#include <QVector>
#include <QLayout>
#include <QLabel>
#include <QLCDNumber>

#include "stageprogresswidget.h"
#include "../headers/contract.h"
#include "monheaderwidget.h"
#include "dletedialog.h"
#include "contractredactordialog.h"

class ContractWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int alpha READ alpha WRITE setAlpha)

private:
    //QVector <StageProgressWidget*> _stages_widgets;

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

    int _alpha;

    void showDeleteDialog();
    void setupContract();
    void addStageWidget(Stage* stage);
    void createStageWidgetRequestHandler();
    void deleteStageWidgetRequestHandler();
    int alpha() {return _alpha;}
    void setAlpha(int a);


public:
    explicit ContractWidget(QWidget *parent = 0);
    void setContract (Contract* contract);
    ~ContractWidget();
    void reDrawAll();
    void clearContractWidget();


signals:
    void deleteRequested();

public slots:
};

#endif // CONTRACTWIDGET_H
