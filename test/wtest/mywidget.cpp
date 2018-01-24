#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    QWidget *progress = new QWidget(this);
    QWidget *setter = new QWidget(0);

    form1.setupUi(setter);
    form2.setupUi(progress);

    setter->show();



}


void mywidget::on_pushButton_clicked()
{

}
