#include "mywidget.h"

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{
    progress_form.setupUi(this);
}


void mywidget::on_pushButton_clicked()
{
    QWidget *setter_widget = new QWidget(0);
   // setter_widget->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout *setter_widget_layout = new QVBoxLayout(setter_widget);
    QPushButton *close_button = new QPushButton("Close",setter_widget);
    //connect(close_button, &QPushButton::clicked, setter_widget,  &QWidget::close);
    connect(close_button, &QPushButton::clicked, [setter_widget]{delete setter_widget;});
    connect(close_button, &QPushButton::destroyed, this,  &mywidget::destoyedSignalMonitor);
    setter_widget_layout->addWidget(close_button);


    connect(setter_widget, &QObject::destroyed, this, &mywidget::destoyedSignalMonitor);
    setter_widget->show();
}

void mywidget::destoyedSignalMonitor(QObject *obj)
{

   // qDebug() << "Object " << QString(sender()->objectName()) << "has deleted.";
    qDebug() << "Object " << QString(qobject_cast<QWidget*>(obj)->objectName()) << "has deleted.";
}
