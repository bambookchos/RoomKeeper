#include "room.h"


QVector <room> get_all_rooms() {
    QSqlQuery query;
    query.exec("SELECT ID,Number FROM rooms");
    QVector <room> rooms;
    while (query.next()) {
        room temp;
        temp.id = query.value(0).toInt();
        temp.number = query.value(1).toInt();
        rooms.append(temp);
    }
    return rooms;
}
