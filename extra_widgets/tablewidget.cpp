#include "tablewidget.h"


TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    table_dock = new QWidget(this);

}

void TableWidget::setContent(DataBase *base)
{
    _base = base;
    draw();
}

void TableWidget::draw()
{
    delete table_dock;
    _last_entry = 1;

    table_dock = new QWidget(this);
    QScrollArea *_scrollArea = new QScrollArea(this);
    _scrollArea->setMinimumWidth(1800);
    _scrollArea->setMinimumHeight(900);


    table_glayout = new QGridLayout(table_dock);
    table_dock->setLayout(table_glayout);

    _scrollArea->setWidget(table_dock);
    _scrollArea->setWidgetResizable(true);
    addHeader();

    int num_contracts=_base->contracts.size();
    for (int i = 0; i < num_contracts; i++){

            addContractWidget(_base->contracts.at(i));
            qDebug()<<"added stage";

    }

qDebug()<<"added contract";






}

void TableWidget::addContractWidget(Contract *contract)
{

    /*Убрать ебаный костыль с -1 */


        QLabel* num = new QLabel(QString::number(contract->getNumber()),this);

       //QLCDNumber *num = new QLCDNumber(this);
       // num->display(QString::number(contract->getNumber()));

        num->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 30px; border: 2px solid black;");
        //num->setMinimumWidth(60);

        table_glayout->addWidget(num,_last_entry,0);

        QLabel* name = new QLabel(contract->getContractName(),this);
        name->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
        name->setWordWrap(true);
        //name->setMinimumWidth(400);

        table_glayout->addWidget(name,_last_entry, 1);

        ContractWidget *_contractWidget = new ContractWidget(this,contract);

        table_glayout->addWidget(_contractWidget,_last_entry,2);
        _last_entry++;

}

void TableWidget::addHeader()
{
    QLabel* num = new QLabel(QString("№ П/П"),table_dock);
    num->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
    //num->setMinimumWidth(60);
    table_glayout->addWidget(num,0,0);
    QLabel* name = new QLabel(QString("Номер контракта"),table_dock);
    name->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
    name->setWordWrap(true);
   // name->setMinimumWidth(400);
    table_glayout->addWidget(name,0,1);
    QLabel* st = new QLabel(QString("Прогресс выполнения"),table_dock);
    st->setStyleSheet("text-align: middle; background-color: rgb(240, 240, 240); width: 10px; border: 2px solid black;");
    st->setWordWrap(true);
   // st->setMinimumWidth(400);
    table_glayout->addWidget(st,0,2);
}



