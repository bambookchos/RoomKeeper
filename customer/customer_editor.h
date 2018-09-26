#ifndef CUSTOMER_EDITOR_H
#define CUSTOMER_EDITOR_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>

#include "login.h"
#include "customer/customer_add.h"
namespace Ui {
class Customer_editor;
}

class Customer_editor : public QDialog
{
    Q_OBJECT

public:
    explicit Customer_editor(QWidget *parent = 0);
    ~Customer_editor();



private:
    Ui::Customer_editor *ui;
    QSqlQueryModel *model;
    int id;

private slots:
    void search();
    void del();
    void edit();
    void add_customer();
};

#endif // CUSTOMER_EDITOR_H
