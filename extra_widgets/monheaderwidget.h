#ifndef MONHEADERWIDGET_H
#define MONHEADERWIDGET_H

#include <QWidget>
#include <QLabel>


class MonHeaderWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *jan_label;
    QLabel *feb_label;
    QLabel *mar_label;
    QLabel *apr_label;
    QLabel *may_label;
    QLabel *jun_label;
    QLabel *dec_label;
    QLabel *jul_label;
    QLabel *sep_label;
    QLabel *oct_label;
    QLabel *nov_label;
    QLabel *aug_label;

public:
    explicit MonHeaderWidget(QWidget *parent = 0);


};

#endif // MONHEADERWIDGET_H
