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
    int _year = QDate::currentDate().year(); ///!!!
    QLabel *lbl;
    double _size_factor = 2.9;
    int _grid_width;
    int _wheight = 30;
    QVector <QLabel*> mons;
public:
    explicit MonHeaderWidget(QWidget *parent = 0);

    void setYear(int year);

    void setNamesVisible(bool v);

    double getSizeFactor();

    int getGridWidth();

    void setVerticalSize(int vs);

protected:
   // void draw();
    void resizeEvent(QResizeEvent *event) override;


};



#endif // MONHEADERWIDGET_H
