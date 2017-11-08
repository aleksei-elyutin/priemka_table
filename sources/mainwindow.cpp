#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    TableWidget *main_table = new TableWidget(this);
    ui->gridLayout->addWidget(main_table);
   // setCentralWidget(main_table);




    //main_table->setSizePolicy(QSizePolicy::QSizePolicy::Maximum,QSizePolicy::Maximum);



    DataBase *base = new DataBase(this);
    /*заполнение бд*/
        for (int i = 0; i < 5; i++){
            Contract *tmp_contract  = new Contract(i+1,
                    QString("Наименование контракта номер ")+QString::number(i+1));
            for (int k=0; k<=i; k++)
            {
                Stage *tmp_stage = new Stage(QDate(2017,5,10),QDate(2017,11,10+k+i));
                tmp_contract->pushStage(tmp_stage);
            }
            base->contracts.push_back(tmp_contract);
        }


    main_table->setContent(base);

    contractRedactorDialog *dial = new contractRedactorDialog (0);

    dial->linkContract(base->contracts[1]);
    dial->draw();
    dial->show();
    connect(dial, &contractRedactorDialog::accepted, main_table, &TableWidget::draw);


    //_scrollArea->resize(this->size());
    //ui->verticalLayout->addWidget(main_table);

}

MainWindow::~MainWindow()
{
    delete ui;
}
