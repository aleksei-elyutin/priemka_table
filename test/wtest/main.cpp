#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include "mywidget.h"

//#include "../../extra_widgets/monheaderwidget.h"
//#include "../../extra_widgets/stageprogresswidget.h"
//#include "../../extra_widgets/tablewidget.h"

//#include "../../headers/contract.h"
//#include "../../headers/stage.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    mywidget *w = new mywidget();


    w->show();



    return a.exec();
}
