#ifndef RESERVATION_REDACTOR_H
#define RESERVATION_REDACTOR_H

#include <QDialog>
#include <QtSql>
#include "customer/customer_choose.h"

#include "login.h"

namespace Ui {
class Reservation_redactor;
}

class Reservation_redactor : public QDialog
{
    Q_OBJECT

public:
    explicit Reservation_redactor(QWidget *parent = 0);
    Reservation_redactor(int id, QWidget *parent = 0);
    ~Reservation_redactor();
    void show();
    int exec();

private:
    Ui::Reservation_redactor *ui;
    int customer_id;
    QDate date_start;
    QDate date_end;
    int id_r;
    int room_id;

private slots:
    void choose();
    void filter();
    void ready();
};

#endif // RESERVATION_REDACTOR_H
