#include "customer_add.h"
#include "ui_customer_add.h"

extern int PERM[9];

Customer_add:: Customer_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui:: Customer_add)
{
    ui->setupUi(this);
    user_id =0;
}
Customer_add::Customer_add(int id, QWidget *parent) : QDialog(parent), ui(new Ui::Customer_add)
{
    ui->setupUi(this);
    user_id = id;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM customers WHERE ID=:ID"));
    query.bindValue(":ID",id);
    query.exec();
    query.next();
    QSqlRecord rec = query.record();
    QString name;
    QString passport;
    QDate birtdate;
    name = query.value(rec.indexOf("Name")).toString();
    passport = query.value(rec.indexOf("Passport")).toString();
    birtdate = query.value(rec.indexOf("Birthday")).toDate();

    ui->le_name->setText(name);
    ui->le_passport->setText(passport);
    ui->dateEdit->setDate(birtdate);
}
Customer_add::~ Customer_add()
{
    delete ui;
}

void Customer_add::show() {

    if (user_id == 0) {
        if (PERM[CUSTOMER_ADD_PERM] == 0) {
            QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
            return;
        }
        else {
            return QDialog::show();
        }
    }
    else {
        if (PERM[CUSTOMER_EDIT_PERM] == 0) {
            QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
            return;
        }
        else {
            return QDialog::show();
        }
    }

}

int Customer_add::exec() {
    if (user_id == 0) {
        if (PERM[CUSTOMER_ADD_PERM] == 0) {
            return 0;
        }
        else {
            return QDialog::exec();
        }
    }
    else {
        if (PERM[CUSTOMER_EDIT_PERM] == 0) {
            return 0;
        }
        else {
            return QDialog::exec();
        }
    }
}

void Customer_add::on_buttonBox_accepted()
{
    QString name;
    QString passport;
    QDate birtdate;

    name  = ui->le_name->text();
    passport = ui->le_passport->text();
    birtdate = ui->dateEdit->date();
    QSqlQuery query;
    if (user_id == 0) {
        query.prepare(QString("INSERT INTO customers VALUES(NULL,:NAME,:DATE,:PASSPORT)"));
        query.bindValue(":NAME",name);
        query.bindValue(":DATE",birtdate);
        query.bindValue(":PASSPORT",passport);
        query.exec();
    }
    else {
        query.prepare("UPDATE customers SET Name=:NAME, Birthdate=:DATE, Passport=:PASSPORT WHERE ID=:ID");
        query.bindValue(":ID",user_id);
        query.bindValue(":NAME",name);
        query.bindValue(":DATE",birtdate);
        query.bindValue(":PASSPORT",passport);
        query.exec();
    }
}



