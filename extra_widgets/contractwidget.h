#ifndef CONTRACTWIDGET_H
#define CONTRACTWIDGET_H

#include <QFrame>
#include <QVector>
#include <QLayout>
#include <QLabel>
#include "stageprogresswidget.h"
#include "../headers/contract.h"
#include "./monheaderwidget.h"

class ContractWidget : public QFrame
{
    Q_OBJECT
private:
    QVector <StageProgressWidget*> _stages_widgets;
    //QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    //QLabel *num;
    // QLabel *name;
    // QWidget *_dock;
    MonHeaderWidget *header;
    QPushButton *_edit_button;

public:
    /*explicit*/ ContractWidget(QWidget *parent, Contract* contract);


signals:

public slots:
};

#endif // CONTRACTWIDGET_H
