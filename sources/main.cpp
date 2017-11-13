//#include "../headers/mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QWidget>

#include "extra_widgets/tablewidget.h"
#include "headers/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* MainWindow w;
    w.show();*/

    QFile file("base.dat");
    QWidget main_window;

    main_window.setStyleSheet("background-color: rgb(255, 255, 255);");
    main_window.resize(1500,1000);
    DataBase base;
    base.setFile(&file);

    QVBoxLayout *main_window_layout = new QVBoxLayout(&main_window);
    TableWidget *main_table = new TableWidget();
    main_table->setContent(&base);
    main_window_layout->addWidget(main_table);
    QPushButton *read = new QPushButton(&main_window);
    read->setText("Загрузить из файла");
    QObject::connect (read, &QPushButton::clicked, &base, &DataBase::readFromFile);
    main_window_layout->addWidget(read);
    QPushButton *write = new QPushButton(&main_window);
    write->setText("Сохранить в файл");
    QObject::connect (write, &QPushButton::clicked, &base, &DataBase::writeToFile);
    main_window_layout->addWidget(write);


    main_window.show();

    return a.exec();
}
