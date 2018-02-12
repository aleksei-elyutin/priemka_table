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
#include <QEventLoop>
#include <QPropertyAnimation>
#include <QLCDNumber>
#include "./headers/stage.h"
#include "monheaderwidget.h"
#include "dletedialog.h"
#include "dletedialog.h"
#include "stageredactor.h"

class StageProgressWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int alpha READ alpha WRITE setAlpha)
private:
    Stage *_stage;   
    QDate _curr_start_date;
    QDate _curr_finish_date;
    int _selected_year;

    bool islocked = true;

    QProgressBar *_progress;
    MonHeaderWidget *_monheader;

    int _start_progress_bar_position = 0;
    int _end_progress_bar_position = 0;

    int _size_factor = 3;
    int _vert_size = 40;

    int _alpha;

    QHBoxLayout *_widget_layout;
    QWidget *_elements_box;
    QVBoxLayout *_elements_box_layout;
    QWidget *_top_box;
    QHBoxLayout  *_top_box_layout;

    QWidget *_status_box;
    QLabel *_days_left_label;

    QWidget* _startfinish_labels_box;
    QWidget *_button_box;
    QHBoxLayout *_button_box_layout;

    QCheckBox *_done_checkbox;
    QCheckBox *_done10_checkbox;
    QCheckBox *_done20_checkbox;

    QPushButton *delete_stage_button;
    QPushButton *setup_stage_button;


    QLCDNumber *_stage_number;
    QLabel *_stage_name;
    QLabel *_start_date_label;
    QLabel *_finish_date_label;

    QPushButton *decrease_year_button;
    QPushButton *increase_year_button;
    QPushButton *year_label_btn;

    void setCheckBoxesState();
    void updateStartFinishLabels();
    void updateProgress();
    void selectYear(); //private SLOT for year selection

    void resize();

    void setCheckBoxHandler(int state);


    int alpha() {return _alpha;}
    void setAlpha(int a);

protected:
    void resizeEvent(QResizeEvent *event) override;


public:
    explicit StageProgressWidget(QWidget *parent = 0);
   // StageProgressWidget(QWidget *parent = 0, Stage&  stage);

    void setStage (Stage *stage);

    void draw();

    void setupStage();

    void showDeleteDialog();

    void lock();
    void unlock();

signals:
    void deleteRequested();

public slots:

};

#endif // STAGEPROGRESSWIDGET_H
