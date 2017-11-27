#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(255, 255, 255, 255); background-color: rgb(20, 20, 20);");
    resize(500,500);

    l = new QVBoxLayout(this);
    for (int i =0; i<10 ; i++)
    {
        QWidget *wdgt = new QWidget(this);
        QHBoxLayout *wdgt_layout = new QHBoxLayout(wdgt);

        QLCDNumber *num = new QLCDNumber(wdgt);
        num->display(QString::number(i));
        num->setMinimumHeight(50);
        num->setMinimumWidth(50);
        num->setMaximumHeight(50);
        num->setMaximumWidth(50);
        num->setDigitCount(3);
        num->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        wdgt_layout->addWidget(num);
        num->setObjectName("number");


        QPushButton *pbtn = new QPushButton(wdgt);
        wdgt_layout->addWidget(pbtn);
        pbtn->setText("Pop");
        pbtn->setFixedSize(200,50+i*10);
        pbtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
        pbtn->setStyleSheet("color: rgba(255, 255, 255, 255); background-color: rgb(50, 50, 50);");
        connect (pbtn, &QPushButton::clicked, this, &mywidget::buttonClicked);




        QLabel *name = new QLabel(wdgt);
        name->setText("Виджет номер"+QString::number(i));
        wdgt_layout->addWidget(name);
        l->addWidget(wdgt);


    }
    connect(this, &mywidget::order_changed, this, &mywidget::updateNumbers);

    pa = new QPropertyAnimation(this);
    pa->setPropertyName("geometry");

    loop = new QEventLoop(this);
    connect (pa, &QPropertyAnimation::finished, loop, &QEventLoop::quit);

}
void mywidget::popWidgetAnim(QWidget* _widget)
{
    moveWidgetAnim(_widget, 0);
}

void mywidget::swapWidgets(int widget_in_pos_a, int widget_in_pos_b)
{
    if (widget_in_pos_a < 0) widget_in_pos_a = 0;
    if (widget_in_pos_a >= l->count()) widget_in_pos_a = l->count()-1;
    if (widget_in_pos_b < 0) widget_in_pos_b = 0;
    if (widget_in_pos_b >= l->count()) widget_in_pos_b = l->count()-1;

    int upper, lower;
    if (widget_in_pos_a < widget_in_pos_b)
    {
        upper = widget_in_pos_a;
        lower =widget_in_pos_b;
    }
    else
    {
        upper = widget_in_pos_b;
        lower =widget_in_pos_a;
    }

    moveWidgetAnim(l->itemAt(lower)->widget(), upper);
    moveWidgetAnim(l->itemAt(upper+1)->widget(), lower);
}

void mywidget::moveWidgetAnim(QWidget* _widget, int pos)
{
    if (l->indexOf(_widget)!=pos)
    {
        if (pos < 0) pos = 0;
        if (pos >= l->count()) pos = l->count()-1;

        QRect current_widget_geometry = _widget->geometry();
        QRect new_widget_geometry =l->itemAt(pos)->geometry();
        new_widget_geometry.setWidth(l->itemAt(pos)->geometry().width());
        new_widget_geometry.setHeight(l->itemAt(pos)->geometry().height());
        _widget->raise();

        l->removeWidget(_widget);

        pa->setDuration((int) ((float) abs(new_widget_geometry.top()-current_widget_geometry.top())*duration_factor));

        pa->setTargetObject(_widget);
        pa->setStartValue(current_widget_geometry);
       // qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_widget_geometry);
       // qDebug() << "endValue:"<< pa->endValue();

         pa->start();
        loop->exec();

        l->insertWidget(pos,_widget);
        l->update();

    }
}


void mywidget::updateNumbers()
{
    int num_entries = l->count();
    for (int i=0; i < num_entries; i ++) {
        QWidget* _widget =(l->itemAt(i)->widget());
        QLCDNumber* lbl = _widget->findChild<QLCDNumber*>("number");
       // qDebug() << lbl->text();
        lbl->display(QString::number(l->indexOf(qobject_cast<QWidget*>(_widget))));
    }

}

void mywidget::buttonClicked()
{

    QWidget *_widget = qobject_cast<QWidget*> (sender()->parent());
    popWidgetAnim(_widget);
//    QTimer t;
//    connect(&t, &QTimer::timeout, loop, &QEventLoop::quit);
//    t.setSingleShot(true);
//    t.start(1000);
//    loop->exec();

//   moveWidgetAnim(_widget,l->count());
//    swapWidgets(1,8);
    emit order_changed();

}




