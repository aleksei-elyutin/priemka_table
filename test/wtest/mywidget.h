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
#include <QRegExp>
#include <QLCDNumber>



class mywidget : public QWidget
{
    Q_OBJECT

private:
//    QPushButton *btn;
    QPropertyAnimation *pa;
    QVBoxLayout *l ;

    void updateNumbers();

public:
    explicit mywidget(QWidget *parent = 0);

protected:

    void buttonClicked();
    void popWidgetAnim(QWidget* _widget);
    void moveWidgetAnim(QWidget* _widget, int pos);


signals:
    void order_changed();

};

#endif // MYWIDGET_H
