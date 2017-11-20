#ifndef MONHEADERWIDGET_H
#define MONHEADERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QResizeEvent>
#include <QDebug>


class MonHeaderWidget : public QWidget
{
    Q_OBJECT


private:
    int _year;
    QLabel *lbl;
    double _size_factor = 3;
    int _wheight = 30;
    QVector <QLabel*> mons;
public:
    explicit MonHeaderWidget(QWidget *parent = 0);

    void setYear(int year);

protected:
    void resizeEvent(QResizeEvent *event) override;

};



#endif // MONHEADERWIDGET_H
