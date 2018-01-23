#include "authform.h"

AuthForm::AuthForm(QWidget *parent) : QWidget(parent)
{
    crypto.setKey(Q_UINT64_C(0x412773C61A177E9F));


}


void AuthForm::loadHash(QString hash)
{
    local_hash = hash;
    local_hash_loaded = true;
}

QString AuthForm::createHash(QString new_pass)
{
    return crypto.encryptToString(new_pass);
}

bool AuthForm::checkPassword(QString pass)
{
    if (local_hash_loaded)
    {
        if (local_hash == crypto.encryptToString(pass)) return true;
        else return false;
    }
    else qDebug() << "Crypto: Hash not loaded!";
}

void AuthForm::showAuthWindow()
{
    QWidget *auth_window = new QWidget(0,Qt::WindowModal);
    QLayout *window_layout = new QVBoxLayout(auth_window);

    QLabel *auth_message_label = new QLabel("Введите пароль для авторизации:",auth_window);
    window_layout->addWidget(auth_message_label);

    QLineEdit password_edit = new QLineEdit(auth_window);
    window_layout->addWidget(auth_message_label);

    QCheckBox *show_password_chkbox = new QCheckBox(auth_window);
    show_password_chkbox->setText("Показать пароль?");
    window_layout->addWidget(auth_message_label);

    QDialogButtonBox *dial_butons = new QDialogButtonBox(auth_window);


}

void AuthForm::showChangePassWindow()
{
    QWidget *setpass_window = new QWidget(0,Qt::WindowModal);
    QLayout *window_layout = new QVBoxLayout(setpass_window);

    QLabel *auth_message_label_oldpass = new QLabel("Введите текущий пароль:",auth_window);
    window_layout->addWidget(auth_message_label_oldpass);

    //---QLineEdit

    QLabel *auth_message_label_newpass = new QLabel("Введите новый пароль:",auth_window);
    window_layout->addWidget(auth_message_label_newpass);

    //---QLineEdit

    QLabel *auth_message_label_newpass_confirm = new QLabel("Повторите новый пароль:",auth_window);
    window_layout->addWidget(auth_message_label_newpass_confirm);
}



