#include "room_edit.h"
#include "ui_room_edit.h"

extern int PERM[9];

Room_edit::Room_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Room_edit)
{
    ui->setupUi(this);
    connect(ui->pb_add, SIGNAL(released()), this, SLOT(add()));
    connect(ui->pb_edit, SIGNAL(released()), this, SLOT(edit()));
    connect(ui->pb_delete, SIGNAL(released()), this, SLOT(delet()));
    ui->tw_roomCharactes->setSelectionBehavior(QAbstractItemView::SelectRows);

    fill();

}

Room_edit::~Room_edit()
{
    delete ui;
}


void Room_edit::show() {
    if (PERM[ROOM_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Room_edit::exec() {
    if (PERM[ROOM_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}

void Room_edit::add()
{
    Room_add *add = new Room_add();
    add->show();
    add->exec();
    fill();
}
void Room_edit::edit()
{

    QModelIndexList selectedList = ui->tw_roomCharactes->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана комната!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        Room_add *add = new Room_add(room_ids[row]);
        add->show();
        add->exec();
        fill();
    }
}
void Room_edit::delet()
{

    QModelIndexList selectedList = ui->tw_roomCharactes->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана комната!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        QSqlQuery query;
        query.prepare("DELETE FROM room_characters WHERE R_ID=:ID");
        query.bindValue(":ID",room_ids[row]);
        query.exec();
        query.prepare("DELETE FROM rooms WHERE ID=:ID");
        query.bindValue(":ID",room_ids[row]);
        query.exec();
        fill();
    }
}


void Room_edit::fill() {
    room_ids.clear();
    ui->tw_roomCharactes->clear();
    QSqlQuery query;
    query.exec("SELECT COUNT(ID) FROM rooms");
    query.next();
    ui->tw_roomCharactes->setRowCount(query.value(0).toInt());

    query.exec("SELECT COUNT(ID) FROM characters");
    query.next();
    ui->tw_roomCharactes->setColumnCount(query.value(0).toInt()+1);
    QTableWidgetItem *newItem = new QTableWidgetItem("Комната N");
    ui->tw_roomCharactes->setHorizontalHeaderItem(0, newItem);


    QVector<int> character_ids;
    query.exec("SELECT * FROM characters");
    int col = 1;
    while (query.next()) {
        character_ids.append(query.value(0).toInt());
        QTableWidgetItem *newItem = new QTableWidgetItem(query.value(1).toString());
        ui->tw_roomCharactes->setHorizontalHeaderItem(col, newItem);
        col++;
    }

    query.exec("SELECT * FROM rooms");
    int row = 0;
    while (query.next()) {
        room_ids.append(query.value(0).toInt());
        QTableWidgetItem *newItem = new QTableWidgetItem(query.value(1).toString());
        ui->tw_roomCharactes->setItem(row, 0, newItem);
        row++;
    }


    query.exec("SELECT * FROM room_characters");
    while (query.next()) {
        QSqlQuery query2;
        query2.prepare("SELECT * FROM character_vars WHERE ID=:ID");
        query2.bindValue(":ID",query.value(3).toInt());
        query2.exec();
        query2.next();

        QTableWidgetItem *newItem = new QTableWidgetItem(query2.value(2).toString());
        ui->tw_roomCharactes->setItem(room_ids.indexOf(query.value(1).toInt()), character_ids.indexOf(query.value(2).toInt())+1, newItem);
    }



}
