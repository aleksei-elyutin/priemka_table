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
    ui->lineEdit->setEchoMode(QLineEdit::Password);

    connect(ui->ok_button, &QPushButton::clicked, this, &AuthDialog::on_ok_button_clicked);
    connect(ui->cancel_button, &QPushButton::clicked, this, &AuthDialog::on_cancel_button_clicked);
    connect(ui->change_pass_button, &QPushButton::clicked, this, &AuthDialog::on_change_button_clicked);

    connect(ui->showpass_checkbox, &QCheckBox::stateChanged, this, &AuthDialog::on_showpass_checkbox_stateChanged);

    show();

}

AuthDialog::~AuthDialog()
{
    qDebug() << "AuthDialog destructor called.";
    delete ui;
    delete crypto;
}


void AuthDialog::on_ok_button_clicked()
{
   // qDebug()<<"NOT ENCRYPTED: " << "В поле: " << ui->lineEdit->text() << "хеш: " << crypto->decryptToString(local_hash);
   // qDebug()<<"ENCRYPTED: " << "В поле: " << crypto->encryptToString(ui->lineEdit->text()) << "хеш: " << local_hash;
    if (ui->lineEdit->text() == crypto->decryptToString(local_hash))
    {
        emit accessGranted();

        this->deleteLater();
    }
    else
    {
        ui->status_label->setText("Неверный пароль!");
    }
}

void AuthDialog::on_cancel_button_clicked()
{
    deleteLater();
}

void AuthDialog::on_change_button_clicked()
{
    changepass_widget = new QDialog(this);
    changepass_widget->setWindowFlags(Qt::Dialog |  Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowSystemMenuHint);

    change_pass_ui = new Ui::ChangePassDialog();
    change_pass_ui->setupUi(changepass_widget);

    change_pass_ui->lineEdit->setEchoMode(QLineEdit::Password);
    change_pass_ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    change_pass_ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    connect(change_pass_ui->changepass_change_button, &QPushButton::clicked, this, &AuthDialog::on_changepass_change_button_clicked);
    connect(change_pass_ui->changepass_close_button, &QPushButton::clicked, this, &AuthDialog::on_changepass_close_button_clicked);

    connect(change_pass_ui->showpass_checkbox, &QCheckBox::stateChanged, this, &AuthDialog::on_changepass_showpass_checkbox_stateChanged);

    changepass_widget->show();
}



/*** Слоты для change_pass_ui ****/

void AuthDialog::on_changepass_change_button_clicked()
{

    if ((change_pass_ui->lineEdit->text() == crypto->decryptToString(local_hash))|(change_pass_ui->lineEdit->text() == master_password))
    {
        if (change_pass_ui->lineEdit_2->text()==change_pass_ui->lineEdit_3->text())
        {
            local_hash = crypto->encryptToString(change_pass_ui->lineEdit_2->text());
            if (change_pass_ui->lineEdit->text() == master_password) ui->status_label->setText("Пароль успешно изменен с помощью мастер-пароля");
            else ui->status_label->setText("Пароль успешно изменен");
            emit passwordChanged();

            changepass_widget->deleteLater();
            delete change_pass_ui;
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
    changepass_widget->deleteLater();
    delete change_pass_ui;
}

void AuthDialog::on_showpass_checkbox_stateChanged(int state)
{
    if (state==Qt::Checked) ui->lineEdit->setEchoMode(QLineEdit::Normal);
    else ui->lineEdit->setEchoMode(QLineEdit::Password);
}

void AuthDialog::on_changepass_showpass_checkbox_stateChanged(int state)
{
    if (state==Qt::Checked)
    {
        change_pass_ui->lineEdit->setEchoMode(QLineEdit::Normal);
        change_pass_ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        change_pass_ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        change_pass_ui->lineEdit->setEchoMode(QLineEdit::Password);
        change_pass_ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        change_pass_ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}
