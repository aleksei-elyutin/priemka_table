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

    QWidget *name_buttons_box;
    QVBoxLayout *name_buttons_box_layout;
    QLabel *name;

    QWidget *stages_box;
    QVBoxLayout *stages_box_layout;
    QWidget *button_box;
    QHBoxLayout *button_box_layout;
    QSpacerItem *dummy;


    MonHeaderWidget *header;
    QPushButton *add_stage_button;
    QPushButton *delete_contract_button;
    QPushButton *setup_contract_button;

    QEventLoop *loop ;
    QPropertyAnimation *pa;

    int _alpha;
    bool islocked = true;


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
    Contract *getContract () {return _contract;}
    ~ContractWidget();
    void draw();
    void clear();

    void unlock();
    void lock();


    void updateNumbers();
signals:
    void deleteRequested();

    void unlocked();
    void locked();
    void doubleClicked();

public slots:

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // CONTRACTWIDGET_H
