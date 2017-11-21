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
#include "monheaderwidget.h"
#include "dletedialog.h"
#include "dletedialog.h"
#include "stageredactor.h"

class StageProgressWidget : public QFrame
{
    Q_OBJECT
private:
    Stage *_stage;   
    QDate _curr_start_date;
    QDate _curr_finish_date;
    int _selected_year;


    QProgressBar *_progress;
    MonHeaderWidget *_monheader;

    int _start_progress_bar_position = 0;
    int _end_progress_bar_position = 0;

    int _size_factor = 3;
    int _vert_size = 30;

    QVBoxLayout *_widget_layout;

    QWidget* _progress_box;
    QWidget* _startfinish_labels_box;
    QWidget *_name_button_box;




    QCheckBox *_done_checkbox;
    QCheckBox *_done10_checkbox;
    QCheckBox *_done20_checkbox;

    QPushButton *add_stage_button;
    QPushButton *delete_stage_button;
    QPushButton *setup_stage_button;

    QLabel *_stage_name;
    QLabel *_start_date_label;
    QLabel *_finish_date_label;


public:
    explicit StageProgressWidget(QWidget *parent = 0);
   // StageProgressWidget(QWidget *parent = 0, Stage&  stage);

    void setStage (Stage *stage);

    void selectYear(int year);

    void setupStage();

    void showDeleteDialog();


signals:


public slots:

};

#endif // STAGEPROGRESSWIDGET_H
