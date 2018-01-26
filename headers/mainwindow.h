#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//#include <QMainWindow>
#include <QTimer>
#include "extra_widgets/tablewidget.h"
#include "headers/database.h"
#include "extra_widgets/authdialog.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    DataBase *base;
    TableWidget *main_table;
    QFile *file;

    QPushButton *lock_button;

    QVBoxLayout *main_window_layout;

    QWidget *menu_box;
    QHBoxLayout *menu_box_layout;

    AuthDialog *auth_dial;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void load();
    void save();
    void updateControl();


private:
    //Ui::MainWindow *ui;
    void on_lock_button_clicked();
    void on_action_accessGranted();
    void on_action_passwordChanged();
};

#endif // MAINWINDOW_H
