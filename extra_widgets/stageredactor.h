#ifndef STAGEREDACTOR_H
#define STAGEREDACTOR_H

#include <QWidget>
#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

#include "dletedialog.h"
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

    QDialog*_parent;
    Stage *_stage;


    void disconnectIfDeleted();

public slots:
    void applyChanges();
    void showDeleteDialog();

public:
    explicit stageRedactor(QWidget *parent = 0);
    stageRedactor(QWidget *parent, Stage* stage);
    ~stageRedactor();

    void setStage(Stage *stage);
    void setNoDeletion();
signals:

    void deleteStageRequest();
    void setNameRequest(QString name);



};
/*class StageDeleteDialog : public QDialog
{
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QLabel *msg_label;
    QPushButton *ok_button;
    QPushButton *cancel_button;
public:
    explicit StageDeleteDialog(QWidget *parent=0);
     ~StageDeleteDialog();


};*/

#endif // STAGEREDACTOR_H
