#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include "extra_widgets/tablewidget.h"
#include "extra_widgets/contractredactordialog.h"
#include "headers/contract.h"
#include "headers/stage.h"

#include "headers/database.h"

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
