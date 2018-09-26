#ifndef CUSTOMER_CHOOSE_H
#define CUSTOMER_CHOOSE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include "customer/customer_add.h"
namespace Ui {
class Customer_choose;
}

class Customer_choose : public QDialog
{
    Q_OBJECT

public:
    explicit Customer_choose(QWidget *parent = 0);
    ~Customer_choose();
    int id;


private:
    Ui::Customer_choose *ui;
    QSqlQueryModel *model;

private slots:
    void search();
    void end();
    void add_customer();
};

#endif // CUSTOMER_CHOOSE_H
