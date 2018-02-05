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
    int update_counter = 0;
    DataBase *base;
    TableWidget *main_table;
    QFile *file;
    QLabel *panel;
    QPushButton *lock_button;
    QTimer *timer;

    QVBoxLayout *main_window_layout;

    QWidget *menu_box;
    QHBoxLayout *menu_box_layout;

    AuthDialog *auth_dial;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void load();
    void save();  
    void draw();

private:
    //Ui::MainWindow *ui;
    void on_lock_button_clicked();
    void on_action_accessGranted();
    void on_action_passwordChanged();
    void readState(QDateTime t);
    void writeState(QDateTime);
    void updateHandler();
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
