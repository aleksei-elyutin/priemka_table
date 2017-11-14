#include "../headers/mainwindow.h"
//#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    file = new QFile("base.dat");

    setStyleSheet("background-color: rgb(255, 255, 255);");

    base = new DataBase(this);
    base->setFile(file);

    QVBoxLayout *main_window_layout = new QVBoxLayout(this);
    main_table = new TableWidget();
    main_table->setContent(base);
    main_window_layout->addWidget(main_table);
    QPushButton *read = new QPushButton(this);
    read->setText("Загрузить из файла");
    QObject::connect (read, &QPushButton::clicked, this, &MainWindow::load);
    main_window_layout->addWidget(read);
    QPushButton *write = new QPushButton(this);
    write->setText("Сохранить в файл");
    QObject::connect (write, &QPushButton::clicked, this, &MainWindow::save);
    main_window_layout->addWidget(write);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, base, &DataBase::childChanged);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateControl);

    timer->start(1000*60*30);

}
void MainWindow::load()
{
    if (base->getNumContracts())
    {
        DleteDialog *purge_dialog = new DleteDialog(0);
        purge_dialog->setLabelText("Текущие записи будут удалены. Продолжить?");

        connect(purge_dialog, &DleteDialog::accepted, base, &DataBase::purgeBase);
        connect(purge_dialog, &DleteDialog::accepted, base, &DataBase::readFromFile);
        connect(purge_dialog, &DleteDialog::accepted, purge_dialog, &DleteDialog::close);
        purge_dialog->show();
    }
    else if ((file->exists())&(file->size()>0))
    {
              base->readFromFile();
    }
}
void MainWindow::save()
{
    if ((file->exists())&(file->size()>0))
    {
        DleteDialog *rewrite_dialog = new DleteDialog(0);
        rewrite_dialog->setLabelText("Файл существует и не пуст. Перезаписать?");

        file->
        connect(rewrite_dialog, &DleteDialog::accepted, base, &DataBase::writeToFile);
        connect(rewrite_dialog, &DleteDialog::accepted, rewrite_dialog, &DleteDialog::close);
        rewrite_dialog->show();
    } else
    {
        base->writeToFile();
    }
}
void MainWindow::updateControl()
{
    QLabel *w = new QLabel("Обновлено "+ QDate::currentDate().toString(),0);
    w->show();
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, w, &QWidget::close);
    connect(timer, &QTimer::timeout, timer, &QTimer::stop);
    timer->start(2000);

}


MainWindow::~MainWindow()
{
   // delete ui;
}
