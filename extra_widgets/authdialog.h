#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QDialog>

#include "headers/simplecrypt.h"
#include "ui_changepassdialog.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = 0, QString hash = "");
    ~AuthDialog();

    QString getHash() {return local_hash;} /** Inline impl */

private:
    SimpleCrypt *crypto;
    Ui::AuthDialog *ui;
    Ui::ChangePassDialog *change_pass_ui;
    QString local_hash;

    QDialog *changepass_widget;

    void on_change_button_clicked();
    void on_ok_button_clicked();
    void on_cancel_button_clicked();

    void on_changepass_change_button_clicked();
    void on_changepass_close_button_clicked();

signals:
    void accessGranted(); //Соединить со слотом, выполняющим разблокировку таблицы
    void passwordChanged(); //Соединить к слоту, выполняющему изменение пароля в базе

};

#endif // AUTHDIALOG_H