#ifndef RESERVATIONS_TABLE_H
#define RESERVATIONS_TABLE_H

#include <QTableWidget>
#include <QDate>
#include <QtSql>
#include <QDebug>
#include "room.h"
#include <QHeaderView>
class Reservations_table : public QTableWidget
{
    Q_OBJECT
public:
    Reservations_table(QWidget *parent = 0) : QTableWidget(parent) {}
    void fill(QDate date_start, QDate date_end, QVector <room> rooms, QDate fill_start = QDate(), QDate fill_end = QDate());
private:
};

#endif // RESERVATIONS_TABLE_H
