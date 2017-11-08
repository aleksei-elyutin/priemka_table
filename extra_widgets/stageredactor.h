#ifndef STAGEREDACTOR_H
#define STAGEREDACTOR_H

#include <QWidget>
#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include "../headers/stage.h"


namespace Ui {
class stageRedactor;
class DeleteDialog;
}

class stageRedactor : public QWidget
{
    Q_OBJECT

private:
    Ui::stageRedactor *ui;

    Stage *_stage;



public slots:
    void applyChanges();
    void deleteStage();
    void showDeleteDialog();

public:
    explicit stageRedactor(QWidget *parent = 0);
    stageRedactor(QWidget *parent, Stage* stage);
    ~stageRedactor();

    void setStage(Stage *stage);




};
class DeleteDialog : public QDialog
{
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QLabel *msg_label;
    QPushButton *ok_button;
    QPushButton *cancel_button;
public:
    explicit DeleteDialog(QWidget *parent=0);


};

#endif // STAGEREDACTOR_H
