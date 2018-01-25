#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QScrollArea>
#include <QLCDNumber>
#include <QGraphicsEffect>

#include "contractwidget.h"
#include "headers/contract.h"
#include "headers/database.h"


class TableWidget : public QFrame
{
    Q_OBJECT
private:
    DataBase *_base; //Указатель на базу данных
    QVBoxLayout *main_layout; // Основной layout виджета

    QScrollArea *_scrollArea;

    QFrame *header_dock;
    QHBoxLayout * header_dock_layout; //Layout заголовка таблицы
    QWidget *table_dock;
    QVBoxLayout *table_dock_layout; //Layout содержимого таблицы

    QPushButton *add_contract_button;

    QEventLoop *loop ;
    QPropertyAnimation *pa;

    int _year = QDate::currentDate().year();
    int _last_entry = 1;

    void createHeader();


public:
    explicit TableWidget(QFrame *parent = 0);

    void addContractWidget (Contract *contract);

    void setContent(DataBase *base);

    void setYear(int year ) {_year = year;}

    void updateNumbers();

    void clearTable();

    void createContractWidgetRequestHandler (); //SLOT

    void deleteContractWidgetRequestHandler(); //SLOT

    void unlock();


signals:
    void unlocked();

public slots:
    void reDrawAll();

};

#endif // TABLEWIDGET_H
