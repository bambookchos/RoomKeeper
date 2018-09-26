#ifndef CHARACTER_TABLE_H
#define CHARACTER_TABLE_H

#include <QTableWidget>
#include <QtSql>
#include <QDebug>


class Character_table : public QTableWidget
{
    Q_OBJECT
public:
    Character_table(QWidget *parent = 0) : QTableWidget(parent) { fill();};
    void fill();
};

#endif // CHARACTER_TABLE_H
