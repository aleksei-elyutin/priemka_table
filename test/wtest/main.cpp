#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QLayout>
#include <QDate>
#include <QFile>
#include <QString>
#include <iostream>

//#include "../../extra_widgets/monheaderwidget.h"
//#include "../../extra_widgets/stageprogresswidget.h"
//#include "../../extra_widgets/tablewidget.h"

//#include "../../headers/contract.h"
//#include "../../headers/stage.h"

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);
    //MainWindow w;
  //  QWidget w;

   /* QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QTime rt;
    QDate rd;*/

    QFile *file = new QFile("test.dat");
    if(!file->open(QIODevice::ReadWrite))
    {
        qDebug() << "Ошибка открытия";
    }

//     qDebug() << date.toString() << " : " << date.toJulianDay();
//     qDebug() << time.toString() << " : " <<  time.msecsSinceStartOfDay();
//     qint64 dj = date.toJulianDay();
//     int tms = time.msecsSinceStartOfDay();

//     file->write((const char*)&dj,sizeof(qint64));
//     file->write((const char*)&tms,sizeof(int));
//     file->close();

//     if(!file->open(QIODevice::ReadWrite))
//     {
//         qDebug() << "Ошибка открытия";
//     }

//     qint64 dj2;
//     int tms2;
//     file->read((char*)&dj2,sizeof(qint64));
//     file->read((char*)&tms2,sizeof(int));
//     rd = QDate::fromJulianDay(dj2);
//     rt = QTime::fromMSecsSinceStartOfDay(tms2);
//     qDebug() << rd.toString() << " : " << rd.toJulianDay();
//     qDebug() << rt.toString() << " : " <<  rt.msecsSinceStartOfDay();

    QString str = "Жопа капуста";
    QByteArray text = str.toLocal8Bit();
    char *data = new char[text.size()+1];
    int data_size = text.size()+1;
    file->write((const char*)&data_size,sizeof(int));
    strcpy(data, text.data());
    file->write((const char*)data,text.size()+1);
    delete [] data;
    file->close();

    if(!file->open(QIODevice::ReadWrite))
         {
             qDebug() << "Ошибка открытия";
         }
    QString str2;
   // QByteArray text ;
    file->read((char*)&data_size,sizeof(int));
    qDebug() << data_size;
    data = new char[data_size];

    file->read((char*)data,data_size);
    strcpy(text.data(),data);
    str2 = QString::fromLocal8Bit(text);

    delete [] data;
        qDebug() << str2;

    file->close();



   // table->show();
    return 0;//a.exec();
}
