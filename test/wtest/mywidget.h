#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QLayout>
#include <QResizeEvent>
#include <QDate>




class mywidget : public QWidget
{
    Q_OBJECT

private:
    int _year;
    QLabel *lbl;
    double _size_factor = 3;
    int _wheight = 30;
    QVector <QLabel*> mons;
public:
    explicit mywidget(QWidget *parent = 0);

    void setYear(int year);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
};

#endif // MYWIDGET_H
