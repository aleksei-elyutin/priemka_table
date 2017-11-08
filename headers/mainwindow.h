#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <tablewidget.h>
#include <contract.h>
#include <stage.h>
#include <contractredactordialog.h>
#include <database.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
