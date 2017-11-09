#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QScrollArea>
#include <QLCDNumber>

#include "contractwidget.h"
#include "headers/contract.h"
#include "headers/database.h"

class TableWidget : public QWidget
{
    Q_OBJECT
private:
    DataBase *_base; //Указатель на базу данных

    QScrollArea *_scrollArea;
    QWidget *table_dock;

    QGridLayout *table_glayout;
    QPushButton *add_contract_button;


    int _year = QDate::currentDate().year();

    int _last_entry = 1;



public:
    explicit TableWidget(QWidget *parent = 0);

    void addContractWidget (Contract *contract);

    void addHeader();

    void setContent(DataBase *base);

    void setYear(int year ) {_year = year;}



signals:

public slots:
    void draw();

};

#endif // TABLEWIDGET_H
