#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include "ui_form1.h"
#include "ui_form2.h"

class mywidget : public QWidget
{
    Q_OBJECT

private:

    Ui::Form1 form1;
    Ui::Form2 form2;

public:
    explicit mywidget(QWidget *parent = 0);

protected:



signals:

private slots:
    void on_pushButton_clicked();
};


    #endif // MYWIDGET_H
