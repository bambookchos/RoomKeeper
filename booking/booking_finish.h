#ifndef BOOKING_FINISH_H
#define BOOKING_FINISH_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class Booking_finish;
}

class Booking_finish : public QDialog
{
    Q_OBJECT

public:
    explicit Booking_finish(QWidget *parent = 0);
    ~Booking_finish();
    void get_data(QVector<QString> data);

private:
    Ui::Booking_finish *ui;
};

#endif // BOOKING_FINISH_H
