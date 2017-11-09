#ifndef STAGEPROGRESSWIDGET_H
#define STAGEPROGRESSWIDGET_H

#include <QFrame>
#include <QProgressBar>
#include <QDate>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QCheckBox>
#include "./headers/stage.h"
#include "./monheaderwidget.h"

class StageProgressWidget : public QFrame
{
    Q_OBJECT
private:
    QProgressBar* _progress;
    int _start_position;
    int _end_position;
    QDate _start_date;
    QDate _finish_date;
    QDate _today;
    int _size_factor = 3;
    int _vert_size = 30;
    QGridLayout *_widget_layout;
    QLabel *_stage_name;


    QCheckBox *_done_checkbox;


public:
    /*explicit*/ StageProgressWidget(QWidget *parent , Stage *stage);
    //StageProgressWidget(QWidget *parent = 0, Stage&  stage);


signals:


public slots:

};

#endif // STAGEPROGRESSWIDGET_H
