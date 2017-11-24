#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    setStyleSheet("border: 1px solid grey; text-align: middle; color: rgba(255, 255, 255, 255); background-color: rgb(20, 20, 20);");
    resize(500,500);

    l = new QVBoxLayout(this);
    for (int i =0; i<5 ; i++)
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
        pbtn->setFixedSize(200,30+i*10);
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
    pa->setDuration(200);

   // btn->setGeometry(width()/2, height()/2, 20 ,20);
    //btn->setText("Съебус");



}
void mywidget::popWidgetAnim(QWidget* _widget)
{
    QRect current_widget_geometry = _widget->geometry();


    QWidget *dummy = new QWidget(this);
    dummy->setFixedSize(current_widget_geometry.width(),current_widget_geometry.height());
    dummy->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);



    if (l->indexOf(_widget)){

        l->removeWidget(_widget);
        //l->insertWidget(index,&dummy);
        l->insertWidget(0,dummy);

        QRect new_widget_geometry = l->itemAt(1)->geometry();


        pa->setTargetObject(_widget);
        pa->setStartValue(current_widget_geometry);
      //   qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_widget_geometry);
       // qDebug() << "endValue:"<< pa->endValue();

        pa->start();

        l->removeWidget(dummy);
        l->insertWidget(0,_widget);
    }

    delete dummy;
}
void mywidget::moveWidgetAnim(QWidget* _widget, int pos)
{
    if (pos < 0) pos = 0;
    if (pos > l->count()) pos = l->count();
     qDebug() << "selectedPos:"<< pos;
    QRect current_widget_geometry = _widget->geometry();

    QWidget *dummy_current = new QWidget(this);
    dummy_current->setMinimumSize(current_widget_geometry.width(),current_widget_geometry.height());
    dummy_current->setMaximumSize(current_widget_geometry.width(),current_widget_geometry.height());
    dummy_current->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QWidget *dummy_new = new QWidget(this);
    dummy_new->setMinimumSize(current_widget_geometry.width(),current_widget_geometry.height());
    dummy_new->setMaximumSize(current_widget_geometry.width(),current_widget_geometry.height());
    dummy_new->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);



    if (l->indexOf(_widget)!=pos){

        qDebug() << "Вставка пустого виджета current_dummy в позицию " << l->indexOf(_widget);
        l->addWidget(dummy_current);
        l->insertWidget(l->indexOf(_widget),dummy_current);
        qDebug() << "Теперь позиция пустого виджета current_dummy:"  << l->indexOf(dummy_current);
        qDebug() << "Удаление перемещаемого виджета с позиции " << l->indexOf(_widget);
        l->removeWidget(_widget);
        qDebug() << "Теперь позиция пустого виджета current_dummy:"  << l->indexOf(dummy_current);
        qDebug() << "Вставка пустого виджета new_dummy в позицию " << pos;
         l->addWidget(dummy_new);
        l->insertWidget(pos, dummy_new);
         qDebug() << "Теперь позиция пустого виджета new_dummy:"  << l->indexOf(dummy_new);
         qDebug() << "Размер: " << l->itemAt(l->indexOf(dummy_new))->widget()->geometry();


        QRect new_widget_geometry = dummy_new->geometry();

        qDebug() << "Размер: " << new_widget_geometry;
          //       QRect new_widget_geometry = dummy_new->geometry();

        pa->setTargetObject(_widget);
        pa->setStartValue(current_widget_geometry);
        qDebug() << "startValue:"<< pa->startValue();
        pa->setEndValue(new_widget_geometry);
        qDebug() << "endValue:"<< pa->endValue();

      //  pa->start();
        l->removeWidget(dummy_current);
    //    l->insertWidget(pos,_widget);
    //    l->removeWidget(dummy_new);

    }

   // delete dummy_current;
    delete dummy_new;
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
//    popWidgetAnim(_widget);
    moveWidgetAnim(_widget,3);
    emit order_changed();

}

//void mywidget::buttonClicked()
//{
//    pa->setDuration(100);

//    QRect current_geometry = btn->geometry();
//    pa->setStartValue(current_geometry);

//    int new_X =  current_geometry.x()+((rand() % 200)-100);
//    int new_Y = current_geometry.y()+((rand() % 200)-100);
//    if (new_X+btn->width() > this->width()) new_X = this->width()-btn->width();
//    if (new_Y+btn->height() > this->height()) new_Y = this->height()-btn->height();
//    QRect new_geometry = QRect (new_X, new_Y, btn->width() ,btn->height());
//    qDebug() << "Btn Current Geometry" << btn->x() << btn->y() << btn->width() << btn->height();
//    pa->setEndValue(new_geometry);

//    qDebug() << "Btn New Geometry" << btn->x() << btn->y() << btn->width() << btn->height();
//    pa->start();
//    pa->finished();

//}


