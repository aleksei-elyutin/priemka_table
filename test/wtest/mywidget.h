#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QLayout>
#include <QResizeEvent>
#include <QDate>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QPropertyAnimation>



class mywidget : public QWidget
{
    Q_OBJECT

private:
//    QPushButton *btn;
//    QPropertyAnimation *pa;
    QVBoxLayout *l ;


public:
    explicit mywidget(QWidget *parent = 0);

protected:

    void buttonClicked();

signals:


};

#endif // MYWIDGET_H
