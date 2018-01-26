#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent, QString hash) :
    QWidget(parent)//,ui(new Ui::AuthDialog)
{
    crypto = new SimpleCrypt();
    crypto->setKey(Q_UINT64_C(0x412773C61A177E9F)); //Ключ шифрования сгенерирован вот так: ващпрвап
    local_hash = hash;

    if (hash == QString(""))
    {

        local_hash = crypto->encryptToString(QString(""));
    }

    ui = new Ui::AuthDialog();
    ui->setupUi(this);



    ui->status_label->setText("");

    connect(ui->ok_button, &QPushButton::clicked, this, &AuthDialog::on_ok_button_clicked);
    connect(ui->cancel_button, &QPushButton::clicked, this, &AuthDialog::on_cancel_button_clicked);
    connect(ui->change_pass_button, &QPushButton::clicked, this, &AuthDialog::on_change_button_clicked);

    show();

}

AuthDialog::~AuthDialog()
{
    delete ui;
}


void AuthDialog::on_ok_button_clicked()
{
   // qDebug()<<"NOT ENCRYPTED: " << "В поле: " << ui->lineEdit->text() << "хеш: " << crypto->decryptToString(local_hash);
   // qDebug()<<"ENCRYPTED: " << "В поле: " << crypto->encryptToString(ui->lineEdit->text()) << "хеш: " << local_hash;
    if (ui->lineEdit->text() == crypto->decryptToString(local_hash))
    {
        emit accessGranted();
        this->close();
    }
    else
    {
        ui->status_label->setText("Неверный пароль!");
    }
}

void AuthDialog::on_cancel_button_clicked()
{
    close();
}

void AuthDialog::on_change_button_clicked()
{
    changepass_widget = new QDialog(this);

    change_pass_ui = new Ui::ChangePassDialog();
    change_pass_ui->setupUi(changepass_widget);

    connect(change_pass_ui->changepass_change_button, &QPushButton::clicked, this, &AuthDialog::on_changepass_change_button_clicked);
    connect(change_pass_ui->changepass_close_button, &QPushButton::clicked, this, &AuthDialog::on_changepass_close_button_clicked);
    changepass_widget->show();
}



/*** Слоты для change_pass_ui ****/

void AuthDialog::on_changepass_change_button_clicked()
{

    if (change_pass_ui->lineEdit->text() == crypto->decryptToString(local_hash))
    {
        if (change_pass_ui->lineEdit_2->text()==change_pass_ui->lineEdit_3->text())
        {
            local_hash = crypto->encryptToString(change_pass_ui->lineEdit_2->text());
            ui->status_label->setText("Пароль успешно изменен");
            emit passwordChanged();
            changepass_widget->close();
        }
        else
            change_pass_ui->label_4->setText("Введенные пароли не совпадают!");
    }
    else
    {
        change_pass_ui->label_4->setText("Неверный пароль!");
    }

}

void AuthDialog::on_changepass_close_button_clicked()
{
    changepass_widget->close();
    delete change_pass_ui;
}
