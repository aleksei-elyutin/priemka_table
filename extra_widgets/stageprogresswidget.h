#ifndef STAGEPROGRESSWIDGET_H
#define STAGEPROGRESSWIDGET_H

#include <QFrame>
#include <QProgressBar>
#include <QDate>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include "./headers/stage.h"
#include "./monheaderwidget.h"
#include "dletedialog.h"
#include "dletedialog.h"
#include "stageredactor.h"

class StageProgressWidget : public QFrame
{
    Q_OBJECT
private:
    Stage *_stage;
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

    int _selected_year;


    QCheckBox *_done_checkbox;
    QCheckBox *_done10_checkbox;
    QCheckBox *_done20_checkbox;

    QPushButton *add_stage_button;
    QPushButton *delete_stage_button;
    QPushButton *setup_stage_button;


public:
    /*explicit*/ StageProgressWidget(QWidget *parent , Stage *stage);
    //StageProgressWidget(QWidget *parent = 0, Stage&  stage);

    void setupStage();

    void showDeleteDialog();


signals:


public slots:

};

#endif // STAGEPROGRESSWIDGET_H
