#ifndef ROOM_H
#define ROOM_H

#include <QtSql>
#include <QVector>
struct room{
    int id;
    int number;
};

QVector <room> get_all_rooms();

#endif // ROOM_H
