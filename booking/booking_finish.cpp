#include "booking_finish.h"
#include "ui_booking_finish.h"

Booking_finish::Booking_finish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Booking_finish)
{
    ui->setupUi(this);
}


Booking_finish::~Booking_finish()
{
    delete ui;
}

void Booking_finish::get_data(QVector<QString> data) {
    ui->l_start->setText(data[0]);
    ui->l_end->setText(data[1]);
    ui->l_number->setText(data[2]);
    QSqlQuery query;
    query.prepare("SELECT Name FROM customers WHERE ID=:ID");
    query.bindValue(":ID",data[3].toInt());
    query.exec();
    query.next();
    ui->l_customer->setText(query.value(0).toString());

}


