#ifndef STAGEREDACTOR_H
#define STAGEREDACTOR_H

#include <QWidget>
#include "../headers/stage.h"


namespace Ui {
class stageRedactor;
}

class stageRedactor : public QWidget
{
    Q_OBJECT

private:
    Ui::stageRedactor *ui;

    Stage *_stage;



public slots:
    void applyChanges();

public:
    explicit stageRedactor(QWidget *parent = 0);
    stageRedactor(QWidget *parent, Stage* stage);
    ~stageRedactor();

    void setStage(Stage *stage);




};

#endif // STAGEREDACTOR_H
