#ifndef RESERVATIONS_EDIT_H
#define RESERVATIONS_EDIT_H



#include <QDialog>
#include <QTableWidgetItem>
#include <QVector>
#include "booking/booking_new.h"
#include "reservations/reservation_redactor.h"
namespace Ui {
class Reservations_edit;
}



class Reservations_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Reservations_edit(QWidget *parent = 0);
    ~Reservations_edit();

private:
    Ui::Reservations_edit *ui;
    QVector<int> r_id;
private slots:
    void add();
    void del();
    void edit();
    void filter();
};

#endif // RESERVATIONS_EDIT_H
