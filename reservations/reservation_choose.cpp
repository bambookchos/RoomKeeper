#include "reservation_choose.h"
#include "ui_reservation_choose.h"

extern int PERM[9];


Reservation_choose::Reservation_choose(int state, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservation_choose)
{
    ui->setupUi(this);
    s = state;


    ui->tw_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

    filter();

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(filter()));
    connect(this, SIGNAL(accepted()), this, SLOT(ready()));
}

Reservation_choose::~Reservation_choose()
{
    delete ui;
}



void Reservation_choose::show() {
    if (PERM[BOOKING_IN_OUT_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Reservation_choose::exec() {
    if (PERM[BOOKING_IN_OUT_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}

void Reservation_choose::filter(){


    QDate date_start = QDate::currentDate();
    QDate date_end = date_start.addDays(5);
    ui->tw_list->clear();
    r_id.clear();
    ui->tw_list->setRowCount(0);
    ui->tw_list->setColumnCount(5);
    QSqlQuery query;
    QString query_part= "";
    if (!ui->lineEdit->text().isEmpty()) {
        query_part = " AND Customer_ID IN (SELECT ID FROM customers WHERE Name LIKE'%"+ ui->lineEdit->text() +"%')";
    }


    if (s == 0) {
        ui->label->setText("Выберите броинрование для заезда");

        query.prepare("SELECT * FROM Reservations WHERE "
                      "(julianday(Start_Date) - julianday(:END)<=0) AND Status==0" + query_part);
        query.bindValue(":END",date_end);

    }
    if (s == 1) {
        ui->label->setText("Выберите броинрование для выезда");
        query.prepare("SELECT * FROM Reservations WHERE "
                      "(julianday(End_Date) - julianday(:END)<=0) AND Status==1" + query_part);

        query.bindValue(":END",date_end);

    }



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


}


void Reservation_choose::ready(){

    QModelIndexList selectedList = ui->tw_list->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана бронь!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        QSqlQuery query;

        if (s==0) {
            query.prepare("UPDATE reservations SET Status=1 WHERE ID=:ID");
        }
        if (s==1) {
            query.prepare("UPDATE reservations SET Status =2 WHERE ID=:ID");

        }
        query.bindValue(":ID",r_id[row]);
        query.exec();
        filter();
    }

}
