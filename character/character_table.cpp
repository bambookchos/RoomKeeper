#include "character_table.h"

void Character_table::fill()
{

    clear();

    QSqlQuery query;
    query.exec("SELECT COUNT(ID) FROM characters");
    query.next();
    setRowCount(query.value(0).toInt());
    setColumnCount(3);

    query.exec("SELECT * FROM characters");

    int row = 0;
    while (query.next()) {
        QTableWidgetItem *newItem = new QTableWidgetItem(query.value(0).toString());
        setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(query.value(1).toString());
        setItem(row, 1, newItem);
        QSqlQuery query2;
        query2.prepare("SELECT * FROM character_vars WHERE C_ID=:ID");
        query2.bindValue(":ID",query.value(0).toInt());
        query2.exec();
        QString vars;
        while (query2.next()) {
            vars+= query2.value(2).toString()+"\\";
        }
        newItem = new QTableWidgetItem(vars);
        setItem(row, 2, newItem);
        row++;
    }
}
