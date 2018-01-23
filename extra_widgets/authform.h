#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "headers/simplecrypt.h"

class AuthForm : public QWidget
{
    Q_OBJECT
private:
    QString local_hash;
    SimpleCrypt crypto;
    bool local_hash_loaded = false;

public:
    explicit AuthForm(QWidget *parent = 0); 

    void loadHash(QString hash); //Загрузить пароль в экземпляр класса
    QString createHash(QString new_pass); //Зашифровать пароль

    bool checkPassword(QString pass);

    void showAuthWindow();

    void showChangePassWindow();






signals:
    void accessDenied();
    void accessGranted();

public slots:

};

#endif // AUTHFORM_H
