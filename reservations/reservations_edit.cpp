#include "reservations_edit.h"
#include "ui_reservations_edit.h"
extern int PERM[9];

Reservations_edit::Reservations_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservations_edit)
{
    ui->setupUi(this);
    connect(ui->pb_add, SIGNAL(released()),this,SLOT(add()));
    connect(ui->pb_delete, SIGNAL(released()),this,SLOT(del()));
    connect(ui->pb_edit, SIGNAL(released()),this,SLOT(edit()));



    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->dateEdit_2, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(filter()));

    ui->tw_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit_2->setCalendarPopup(true);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());

    QDate date_start = ui->dateEdit->date();
    QDate date_end = ui->dateEdit_2->date();

    ui->tableWidget->fill(date_start, date_end.addDays(1), get_all_rooms());


}

Reservations_edit::~Reservations_edit()
{
    delete ui;
}



void Reservations_edit::add() {
    Booking_new *book = new Booking_new();
    book->show();
    book->exec();
    //    QDate now = QDate::currentDate();
    //    ui->tableWidget->fill(now.addDays(-2),now.addDays(30),get_all_rooms());
}



void Reservations_edit::filter(){
    QDate date_start = ui->dateEdit->date();
    QDate date_end = ui->dateEdit_2->date();
    ui->tw_list->clear();
    r_id.clear();
    ui->tw_list->setRowCount(0);
    ui->tw_list->setColumnCount(5);


    QTableWidgetItem *temp = new QTableWidgetItem("Дата заезда");
    ui->tw_list->setHorizontalHeaderItem(0,temp);
    temp = new QTableWidgetItem("Дата выезда");
    ui->tw_list->setHorizontalHeaderItem(1,temp);
    temp = new QTableWidgetItem("N комнаты");
    ui->tw_list->setHorizontalHeaderItem(2,temp);
    temp = new QTableWidgetItem("ФИО постояльца");
    ui->tw_list->setHorizontalHeaderItem(3,temp);
    temp = new QTableWidgetItem("Статус");
    ui->tw_list->setHorizontalHeaderItem(4,temp);

    QSqlQuery query;
    QString query_part= "";
    if (!ui->lineEdit->text().isEmpty()) {
        query_part = " AND Customer_ID IN (SELECT ID FROM customers WHERE Name LIKE'%"+ ui->lineEdit->text() +"%')";
    }
    query.prepare("SELECT * FROM Reservations WHERE "
                  "((julianday(Start_Date) - julianday(:START)>=0 AND julianday(Start_Date) - julianday(:END) <= 0)"
                  "OR (julianday(End_Date) - julianday(:START)>=0 AND julianday(End_Date) - julianday(:END) <= 0)"
                  "OR (julianday(Start_Date) - julianday(:START)<=0 AND julianday(End_Date) - julianday(:END) >= 0))" + query_part);
    query.bindValue(":START",date_start);
    query.bindValue(":END",date_end);
    query.exec();


    while (query.next()) {


        r_id.append(query.value(0).toInt());
        ui->tw_list->insertRow( ui->tw_list->rowCount() );
        temp = new QTableWidgetItem(query.value(3).toString());
        ui->tw_list->setItem( ui->tw_list->rowCount()-1, 0, temp);
        temp = new QTableWidgetItem(query.value(4).toString());
        ui->tw_list->setItem( ui->tw_list->rowCount()-1, 1, temp);
        temp = new QTableWidgetItem(query.value(2).toString());
        ui->tw_list->setItem( ui->tw_list->rowCount()-1, 2, temp);


        switch (query.value(5).toInt()) {
        case 0:
            temp = new QTableWidgetItem("Забронированно");
            break;
        case 1:
            temp = new QTableWidgetItem("Заселен");
            break;
        case 2:
            temp = new QTableWidgetItem("Выехал");
            break;
        default:
            break;
        }

        ui->tw_list->setItem( ui->tw_list->rowCount()-1, 4, temp);



        QSqlQuery query2;
        query2.prepare("SELECT Name FROM customers WHERE ID=:ID");
        query2.bindValue(":ID",query.value(1).toInt());
        query2.exec();
        query2.next();
        temp = new QTableWidgetItem(query2.value(0).toString());
        ui->tw_list->setItem( ui->tw_list->rowCount()-1, 3, temp);

    }



    ui->tableWidget->fill(date_start, date_end.addDays(1), get_all_rooms());
}

void Reservations_edit::del() {
    if (PERM[BOOKING_EDIT_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    QModelIndexList selectedList = ui->tw_list->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана бронь!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        QSqlQuery query;
        query.prepare("DELETE FROM reservations WHERE ID=:ID");
        query.bindValue(":ID",r_id[row]);
        query.exec();
        filter();
    }
}

void Reservations_edit::edit() {

    QModelIndexList selectedList = ui->tw_list->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана бронь!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();

        Reservation_redactor *redactor = new Reservation_redactor(r_id[row]);
        redactor->show();
        redactor->exec();
        filter();
    }
}
