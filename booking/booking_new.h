#ifndef BOOKING_NEW_H
#define BOOKING_NEW_H




#include <QDialog>
#include <QSqlQueryModel>
#include <QtSql>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QVector>
#include <QMap>
#include <QMultiMap>
#include "customer/customer_choose.h"
#include "booking/booking_finish.h"
#include "room.h"
#include "booking/filter_row.h"
#include "login.h"

namespace Ui {
class Booking_new;
}

struct filter_s {
    Filter_row *c1;
    Filter_row *c2;
};
struct c_box_data {
    int id;
    QString name;
};

class Booking_new : public QDialog
{
    Q_OBJECT

public:
    explicit Booking_new(QWidget *parent = 0);
    ~Booking_new();
    void show();
    int exec();

private:
    Ui::Booking_new *ui;
    QSqlQueryModel *rooms;
    QVBoxLayout *flowLayout;
    QVector <filter_s*> filters;
    QMap<int, QString> characters;
    QMultiMap<int, c_box_data> character_vars;
private slots:
        void filter();
        void booking();
        void add_row();
        void delete_row(QObject *a);
        void set_vals(QComboBox* c, int id);


};


struct room_info{
    int id;
    int number;
};

#endif // BOOKING_NEW_H
