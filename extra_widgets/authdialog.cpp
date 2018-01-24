#include "authdialog.h"
#include "ui_authdialog.h"

AuthDialog::AuthDialog(QWidget *parent, QString hash) :
    QWidget(parent),
    ui(new Ui::AuthDialog)
{
    crypto.setKey(Q_UINT64_C(0x412773C61A177E9F)); //Ключ шифрования сгенерирован вот так: ващпрвап
    local_hash = hash;
    ui->setupUi(this);

    ui->status_label->setText("");

    connect(ui->ok_button, &QPushButton::clicked, this, &AuthDialog.on_ok_button_clicked);
    connect(ui->cancel_button, &QPushButton::clicked, this, &AuthDialog.on_cancel_button_clicked);
    connect(ui->change_pass_button, &QPushButton::clicked, this,  &AuthDialog::on_change_pass_button_clicked);
}

AuthDialog::~AuthDialog()
{
    delete ui;
    delete change_pass_ui;
}


void AuthDialog::on_ok_button_clicked()
{

    if (local_hash == crypto.encryptToString(entered_password))
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
    this->close();
}

void AuthDialog::on_change_pass_button_clicked()
{
    changepass_widget = new QWidget(0);
    change_pass_ui->setupUi(cp);
    connect(change_pass_ui->changepass_change_button, &QPushButton::clicked, this, &AuthDialog.on_changepass_change_button_clicked);
    connect(change_pass_ui->changepass_close_button, &QPushButton::clicked, this, &AuthDialog.on_changepass_close_button_clicked);
}



/*** Слоты для change_pass_ui ****/

void AuthDialog::on_changepass_change_button_clicked()
{
    if (local_hash == crypto.encryptToString(change_pass_ui->lineEdit->text()))
    {
        if (change_pass_ui->lineEdit_2->text()==change_pass_ui->lineEdit_3->text())
        {
            local_hash = crypto.encryptToString(change_pass_ui->lineEdit_2->text());
            ui->status_label->setText("Пароль успешно изменен");
            emit passwordChanged();
            changepass_widget->close();
        }
        else
            change_pass_ui->label_4->setText("Введенные пароли не совпадают!");
    }
    else
    {
        ui->status_label->setText("Неверный пароль!");
    }

}

void AuthDialog::on_changepass_close_button_clicked()
{
    changepass_widget->close();
}
