#ifndef SECONDUI_H
#define SECONDUI_H


#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QVector>

#include "booking/booking_new.h"
#include "personal/personal_edit.h"
#include "customer/customer_editor.h"
#include "room/room_edit.h"
#include "character/character_edit.h"
#include "reservations/reservations_edit.h"
#include "reservations/reservation_choose.h"


namespace Ui {
class SecondUI;
}

class SecondUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondUI(QWidget *parent = 0);
    ~SecondUI();

private slots:

    void add_user();
    void booking();
    void customers_editor();
    void characters_editor();
    void rooms_editor();
    void books_editor();
    void refresh_table();
        void in();
            void out();

private:
    Ui::SecondUI *ui;
    QSqlTableModel *customers_model;

    QSqlTableModel *rooms_model;
    QSqlTableModel *reservations_model;

    QVector<QLabel*> labels;

};


#endif // SECONDUI_H
