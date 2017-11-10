#ifndef DLETEDIALOG_H
#define DLETEDIALOG_H

#include <QDialog>

namespace Ui {
class DleteDialog;
}

class DleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DleteDialog(QWidget *parent = 0);
    ~DleteDialog();

    void setLabelText(QString text);

private:
    Ui::DleteDialog *ui;
};

#endif // DLETEDIALOG_H
