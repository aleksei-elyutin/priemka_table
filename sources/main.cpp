//#include "../headers/mainwindow.h"
#include <QApplication>
#include <QLayout>

#include "extra_widgets/tablewidget.h"
#include "headers/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* MainWindow w;
    w.show();*/

    QWidget main_window;
    main_window.setStyleSheet("background-color: rgb(255, 255, 255);");
    main_window.resize(1500,1000);
    DataBase base;


    QVBoxLayout *main_window_layout = new QVBoxLayout(&main_window);

    TableWidget *main_table = new TableWidget();

    main_table->setContent(&base);


    main_window_layout->addWidget(main_table);


    main_window.show();
    return a.exec();
}
