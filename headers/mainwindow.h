#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//#include <QMainWindow>
#include <QTimer>
#include "extra_widgets/tablewidget.h"
#include "headers/database.h"

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    DataBase *base;
    TableWidget *main_table;
    QFile *file;

    QVBoxLayout *main_window_layout;

    QWidget *menu_box;
    QHBoxLayout *menu_box_layout;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void load();
    void save();
    void updateControl();


private:
    //Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
