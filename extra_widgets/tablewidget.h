#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QScrollArea>
#include <QLCDNumber>

#include "contractwidget.h"
#include "headers/contract.h"
#include "headers/database.h"


class TableWidget : public QFrame
{
    Q_OBJECT
private:
    DataBase *_base; //Указатель на базу данных
    QVBoxLayout *_layout;
    QHBoxLayout * header_dock_layout;
    QScrollArea *_scrollArea;

    QFrame *header_dock;
    QWidget *table_dock;
    QGridLayout *tableDock_glayout;

    QPushButton *add_contract_button;


    int _year = QDate::currentDate().year();

    int _last_entry = 1;


public:
    explicit TableWidget(QFrame *parent = 0);

    void addContractWidget (Contract *contract);

    void addHeader();

    void setContent(DataBase *base);

    void setYear(int year ) {_year = year;}


signals:

public slots:
    void draw();

};

#endif // TABLEWIDGET_H
