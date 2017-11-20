#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QLayout>
#include <QResizeEvent>
#include <QDate>
#include <QPainter>
#include <QProgressBar>
#include <QTimer>



class mywidget : public QWidget
{
    Q_OBJECT

private:
    int _selected_year;
    QLabel *days_left_label;
    QProgressBar *_progress_bar;

    QDate _start_date;
    QDate _finish_date;

    double _size_factor = 3;
    int _wheight = 30;
    QVector <QLabel*> mons;

    void inc_bar();
public:
    explicit mywidget(QWidget *parent = 0);

    void setYear(int year);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
};

#endif // MYWIDGET_H
