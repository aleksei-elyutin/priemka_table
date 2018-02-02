#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QDebug>
#include "ui_form1.h"
#include "ui_form2.h"

class mywidget : public QWidget
{
    Q_OBJECT

private:

    Ui::Form2 progress_form;

    void destoyedSignalMonitor(QObject *obj);
public:
    explicit mywidget(QWidget *parent = 0);

protected:



signals:

private slots:
    void on_pushButton_clicked();
};


    #endif // MYWIDGET_H
