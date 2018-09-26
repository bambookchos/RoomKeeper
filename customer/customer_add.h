#ifndef CUSTOMER_ADD_H
#define CUSTOMER_ADD_H

#include <QDialog>
#include <QDate>
#include <QtSql>
#include "login.h"

namespace Ui {
class Customer_add;
}

class Customer_add : public QDialog
{
    Q_OBJECT

public:
    explicit Customer_add(QWidget *parent = 0);
    Customer_add(int id, QWidget *parent = 0);
    ~Customer_add();
    void show();
    int exec();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::Customer_add *ui;
    int user_id;
};

#endif // CUSTOMER_ADD_H
