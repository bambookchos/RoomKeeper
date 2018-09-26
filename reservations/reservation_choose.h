#ifndef RESERVATION_CHOOSE_H
#define RESERVATION_CHOOSE_H

#include <QDialog>
#include <QDate>
#include <QtSql>
#include <QMessageBox>

#include "login.h"



namespace Ui {
class Reservation_choose;
}

class Reservation_choose : public QDialog
{
    Q_OBJECT

public:
    explicit Reservation_choose(int state = 0, QWidget *parent = 0);
    ~Reservation_choose();


    void show();
    int exec();


private slots:
    void filter();
        void ready();
private:
    Ui::Reservation_choose *ui;
    int s;
    QVector<int> r_id;
};

#endif // RESERVATION_CHOOSE_H
