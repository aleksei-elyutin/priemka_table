#include "../headers/mainwindow.h"
//#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)//, ui(new Ui::MainWindow)
{

    setWindowTitle("454 ВП МО РФ");

    QPixmap app_pixmap(":/resources/app.png");
    QIcon app_icon(app_pixmap);
    setWindowIcon(app_icon);


    file = new QFile("base.dat");

    setStyleSheet("background-color: rgb(20, 20, 20);");

    base = new DataBase(this);
    base->setFile(file);

    main_window_layout = new QVBoxLayout(this);
    main_window_layout->setSpacing(1);
    main_window_layout->setContentsMargins(2,2,2,7);


    main_table = new TableWidget(this);
    main_table->setContent(base);
    connect(base, &DataBase::loadedFromFile, this, &MainWindow::readState);
    connect(base, &DataBase::storedToFile, this, &MainWindow::writeState);

    main_window_layout->addWidget(main_table);
   // connect (base, &DataBase::baseChanged, main_table, &TableWidget::sort);

    menu_box = new QWidget(this);
    menu_box_layout = new QHBoxLayout(menu_box);
    menu_box_layout->setSpacing(5);
    menu_box_layout->setContentsMargins(10,0,10,0);
    main_window_layout->addWidget(menu_box);


    lock_button = new QPushButton(this);
    lock_button->setStyleSheet("QPushButton{text-align: middle;background-color: rgb(50, 50, 50); width: 0px; "
                       "color: rgb(255, 255, 255); border: 0px solid grey; }"
                       "QPushButton:hover{background-color: rgb(80, 80, 80); color: rgb(255, 255, 255);}");
    lock_button->setMinimumWidth(50);
    lock_button->setMaximumWidth(50);
    lock_button->setMinimumHeight(50);
    lock_button->setMaximumHeight(50);
    lock_button->setToolTip("Разблокировать изменение");
    QPixmap lock_pixmap("://resources/lock_icon.png");
    QIcon lock_icon(lock_pixmap);
    lock_button->setIcon(lock_icon);
    lock_button->setIconSize(QSize(50,50));
    menu_box_layout->addWidget(lock_button);
    connect (lock_button, &QPushButton::clicked, this, &MainWindow::on_lock_button_clicked);

  /*  QPushButton *read_from_file_button = new QPushButton(this);
    read_from_file_button->setStyleSheet("QPushButton{text-align: middle; background-color: rgb(50, 50, 50); width: 0px; "
                                         "color: rgb(255, 255, 255); border: 0px solid grey; }"
                                         "QPushButton:hover{background-color: rgb(80, 80, 80); color: rgb(255, 255, 255);}");
    read_from_file_button->setMinimumWidth(50);
    read_from_file_button->setMaximumWidth(50);
    read_from_file_button->setMinimumHeight(50);
    read_from_file_button->setMaximumHeight(50);
    menu_box_layout->addWidget(read_from_file_button);
    QPixmap read_pixmap("://resources/disk_up_arrow.png");
    QIcon read_icon(read_pixmap);
    read_from_file_button->setIcon(read_icon);
    read_from_file_button->setIconSize(QSize(50,50));
    QObject::connect (read_from_file_button, &QPushButton::clicked, this, &MainWindow::load);
    read_from_file_button->setToolTip("Загрузить из файла");*/


   /* QPushButton *write_to_file_button = new QPushButton(this);
    write_to_file_button->setStyleSheet("QPushButton{text-align: middle; background-color: rgb(50, 50, 50); width: 0px; "
                                        "color: rgb(255, 255, 255); border: 0px solid grey; }"
                                        "QPushButton:hover{background-color: rgb(80, 80, 80); color: rgb(255, 255, 255);}");
    write_to_file_button->setMinimumWidth(50);
    write_to_file_button->setMaximumWidth(50);
    write_to_file_button->setMinimumHeight(50);
    write_to_file_button->setMaximumHeight(50);
    QObject::connect (write_to_file_button, &QPushButton::clicked, this, &MainWindow::save);
    menu_box_layout->addWidget(write_to_file_button);
    QPixmap write_pixmap("://resources/disk_down_arrow.png");
    QIcon write_icon(write_pixmap);
    write_to_file_button->setIcon(write_icon);
    write_to_file_button->setIconSize(QSize(50,50));
    write_to_file_button->setToolTip("Записать в файл");*/


    panel = new QLabel(menu_box);
    panel->setText("");
    menu_box_layout->addWidget(panel);
    panel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
    panel->setMaximumHeight(50);
    panel->setStyleSheet("background-color: rgb(50, 50, 50); width: 0px; "
                          "color: rgb(255, 255, 255); border: 0px solid grey; }");




    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateHandler);
   // connect(timer, &QTimer::timeout, base, &DataBase::contractChangeHandler);
   //  connect(timer, &QTimer::timeout, base, &DataBase::writeToFile);
   // connect(timer, &QTimer::timeout, main_table, &TableWidget::sort);

    //timer->start(1000*60*1); // одна минута


    load();
    timer->start(1000*10);

}

void MainWindow::draw()
{
    main_table->reDrawAll();
}

void MainWindow::updateHandler()
{
    qDebug() << "updateHandler: " << update_counter;
    if ((update_counter < 6)&(main_table->isLocked())&(!base->getFileloadStatus()))
    {
       main_table->sort();
       update_counter++;
       if ((update_counter%3 == 0)) base->writeToFile();
    }
    else if (main_table->isLocked()&(!base->getFileloadStatus()))
    {
        base->writeToFile();
        base->readFromFile();
        update_counter = 0;
       // draw();
    }

}

void MainWindow::closeEvent(QCloseEvent *)
{
    qDebug() << "Сохранение при закрытии";
    base->writeToFile();
   // qDebug() << "Закрыт? - " << close();
    deleteLater();
}

void MainWindow::load()
{
    if (base->getNumContracts())
    {
       DleteDialog *purge_dialog = new DleteDialog(0);
        purge_dialog->setLabelText("Текущие записи будут удалены. Продолжить?");

        connect(purge_dialog, &DleteDialog::accepted, base, &DataBase::readFromFile);
        connect(purge_dialog, &DleteDialog::accepted, purge_dialog, &DleteDialog::deleteLater);
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

        connect(rewrite_dialog, &DleteDialog::accepted, base, &DataBase::writeToFile);
        connect(rewrite_dialog, &DleteDialog::accepted, rewrite_dialog, &DleteDialog::deleteLater);
        rewrite_dialog->show();
    } else
    {
        base->writeToFile();
    }
}

void MainWindow::readState(QDateTime t)
{
     panel->setText("Содержимое загружено из файла. Последнее сохранение: " + QDate::longDayName(t.date().dayOfWeek())
                    + " " + t.date().toString("dd.MM.yyyy")
                    + " в " + t.time().toString());
}

void MainWindow::writeState(QDateTime)
{

    panel->setText("Содержимое обновлено и сохранено в файл. Дата: "+ QDate::longDayName(QDate::currentDate().dayOfWeek())
                   + " " + QDate::currentDate().toString("dd.MM.yyyy")
                   + " Время: " + QTime::currentTime().toString());

}

void MainWindow::on_lock_button_clicked()
{
    if (main_table->isLocked())
    {
          auth_dial = new AuthDialog(0, base->getSecureHash());
          connect(auth_dial, &AuthDialog::accessGranted, this, on_action_accessGranted);
          connect(auth_dial, &AuthDialog::passwordChanged, this, on_action_passwordChanged);
          lock_button->setToolTip("Заблокировать изменение");
    }
    else
    {
        main_table->lock();
        main_table->sort();
        QPixmap lock_pixmap("://resources/lock_icon.png");
        QIcon lock_icon(lock_pixmap);
        lock_button->setIcon(lock_icon);
        panel->setText("Запрещено редактирование. "
                       "Дата: "+ QDate::currentDate().toString()+ " Время: " + QTime::currentTime().toString());
    }
}

void MainWindow::on_action_accessGranted()
{
    main_table->unlock();
    QPixmap lock_pixmap("://resources/unlock_icon.png");
    QIcon lock_icon(lock_pixmap);
    lock_button->setIcon(lock_icon);
     panel->setText("Разрешено редактирование. "
                    "Дата: "+ QDate::currentDate().toString()+ " Время: " + QTime::currentTime().toString());


}
void MainWindow::on_action_passwordChanged()
{
    base->setSecureHash(auth_dial->getHash());
    base->writeToFile();
}


MainWindow::~MainWindow()
{
   // delete ui;
}
