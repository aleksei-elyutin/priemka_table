#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <contract.h>

class DataBase : public QObject
{
    Q_OBJECT
private:


public:
    explicit DataBase(QObject *parent = 0);
    QVector <Contract*> contracts;


signals:

public slots:
};

#endif // DATABASE_H
