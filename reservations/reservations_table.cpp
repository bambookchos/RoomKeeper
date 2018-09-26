#include "reservations_table.h"

void Reservations_table::fill(QDate date_start, QDate date_end, QVector <room> rooms, QDate fill_start, QDate fill_end) {

    QSqlQuery query;
    clear();

    //ROW HEADERS
    setRowCount(rooms.size());
    for (int i = 0; i < rooms.size(); i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(rooms[i].number));
        setVerticalHeaderItem(i, newItem);
        //        ui->comboBox->addItem(query.value(1).toString(),query.value(0).toInt());
    }

    //COLUMN HEADERS
    setColumnCount(date_start.daysTo(date_end));
    int in_month = date_start.daysInMonth();
    int day = date_start.day();
    for (int i=0; i<date_start.daysTo(date_end); i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(day));
        day++;
        if (day>in_month) {
            day = 1;
        }
        setHorizontalHeaderItem(i, newItem);
        setColumnWidth(i,30);
    }
    if (!fill_start.isNull() && !fill_end.isNull()) {
        //FILL
        for (int i =0; i< rooms.size(); i++) {
            for (int j = date_start.daysTo(fill_start); j <= date_start.daysTo(fill_end); j++){
                QTableWidgetItem *newItem = new QTableWidgetItem("");
                newItem->setBackground(Qt::blue);
                setItem(i, j, newItem);
            }
        }
    }

    for (int i = 0; i < rooms.size(); i++) {
        query.prepare("SELECT *,\
                      (julianday(:START) - julianday(Start_Date)) as Day,\
                      (julianday(End_Date) - julianday(Start_Date)) as Time\
                      FROM reservations WHERE \
                      ((julianday(Start_Date) - julianday(:START)>=0 AND julianday(Start_Date) - julianday(:END) <= 0)\
                       OR (julianday(End_Date) - julianday(:START)>=0 AND julianday(End_Date) - julianday(:END) <= 0)\
                       OR (julianday(Start_Date) - julianday(:START)<=0 AND julianday(End_Date) - julianday(:END) >= 0))\
                      AND (Room_ID=:ID)"
                      );
        query.bindValue(":ID",rooms[i].id);
        query.bindValue(":START",date_start);
        query.bindValue(":END",date_end);
        query.exec();

        while  (query.next()) {
            QSqlRecord rec = query.record();
            int time =query.value(rec.indexOf("Time")).toInt();

            QSqlQuery query2;
            query2.prepare("SELECT Name FROM customers WHERE ID=:ID");
            query2.bindValue(":ID",query.value(rec.indexOf("Customer_ID")).toString());
            query2.exec();
            query2.next();
            QString name = query2.value(0).toString();

            for (int j = 0; j<= time; j++){
                if (-query.value(rec.indexOf("Day")).toInt()+j < 0) {
                    continue;
                }
                if (-query.value(rec.indexOf("Day")).toInt()+j >= date_start.daysTo(date_end)) {
                    continue;
                }
                QTableWidgetItem *newItem = new QTableWidgetItem(name.left(1));
                switch (query.value(rec.indexOf("Status")).toInt()) {
                case 0:
                    newItem->setBackground(Qt::yellow);
                    break;
                case 1:
                    newItem->setBackground(Qt::green);
                    break;
                case 2:
                    newItem->setBackground(Qt::red);
                    break;
                default:
                    break;
                }
                newItem->setToolTip(name); //TODO
                setItem(i, -query.value(rec.indexOf("Day")).toInt()+j, newItem);
            }
        }
    }
}
