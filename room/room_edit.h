#ifndef ROOM_EDIT_H
#define ROOM_EDIT_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "room/room_add.h"
#include "login.h"
namespace Ui {
class Room_edit;
}

class Room_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Room_edit(QWidget *parent = 0);
    ~Room_edit();
    void show();
    int exec();

private:
    Ui::Room_edit *ui;
    void fill();
    QVector<int> room_ids;
private slots:
    void add();
    void edit();
    void delet();
};

#endif // ROOM_EDIT_H
