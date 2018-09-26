#include "reservation_redactor.h"
#include "ui_reservation_redactor.h"

extern int PERM[9];

Reservation_redactor::Reservation_redactor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservation_redactor)
{
    ui->setupUi(this);
}

Reservation_redactor::Reservation_redactor(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservation_redactor)
{
    id_r =id;

    ui->setupUi(this);

    ui->l_titile->setText("Бронь №"+ QString::number(id));
    ui->comboBox_2->addItem("Забронированно",0);
    ui->comboBox_2->addItem("Заселен",1);
    ui->comboBox_2->addItem("Выехал",2);

    QSqlQuery query;
    query.prepare("SELECT * FROM reservations WHERE ID=:ID");
    query.bindValue(":ID",id);
    query.exec();
    if (query.next()) {

        customer_id = query.value(1).toInt();
        room_id = query.value(2).toInt();

        ui->dateEdit->setDate(query.value(3).toDate());
        ui->dateEdit_2->setDate(query.value(4).toDate());
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findData(query.value(5).toInt()));

        date_start = ui->dateEdit->date();
        date_end = ui->dateEdit_2->date();

    }

    query.prepare("SELECT ID,Number FROM rooms\
                  WHERE  ID NOT IN (SELECT Room_ID FROM reservations WHERE   (ID !=:ID) AND ((julianday(Start_Date) - julianday(:START)>=0 AND julianday(Start_Date) - julianday(:END) <= 0)\
                                                                                             OR (julianday(End_Date) - julianday(:START)>=0 AND julianday(End_Date) - julianday(:END) <= 0)\
                                                                                             OR (julianday(Start_Date) - julianday(:START)<=0 AND julianday(End_Date) - julianday(:END) >= 0) ) )"
                                                                                                                                                                                                 "GROUP BY ID\
                  ORDER BY Number"
                  );

    query.bindValue(":START",date_start);
    query.bindValue(":END",date_end);
    query.bindValue(":ID",id);

    query.exec();

    while (query.next()) {
        ui->comboBox->addItem(query.value(1).toString(),query.value(0).toInt());
    }
    ui->comboBox->setCurrentIndex(ui->comboBox->findData(room_id));


    query.prepare("SELECT Name From customers WHERE ID=:ID");
    query.bindValue(":ID",customer_id);
    query.exec();
    if (query.next()) {
        ui->l_customer->setText(query.value(0).toString());
    }

    connect(ui->pb_choose, SIGNAL(released()), this, SLOT(choose()));
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->dateEdit_2, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(ready()));

}

Reservation_redactor::~Reservation_redactor()
{
    delete ui;
}



void Reservation_redactor::show() {
    if (PERM[BOOKING_EDIT_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Reservation_redactor::exec() {
    if (PERM[BOOKING_EDIT_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}


void Reservation_redactor::choose()
{
    Customer_choose *cus = new Customer_choose();
    cus->show();
    cus->exec();
    customer_id = cus->id;
    QSqlQuery query;
    query.prepare("SELECT Name From customers WHERE ID=:ID");
    query.bindValue(":ID",customer_id);
    query.exec();
    query.next();
    ui->l_customer->setText(query.value(0).toString());
}
void Reservation_redactor::filter()
{
    ui->comboBox->clear();

    date_start = ui->dateEdit->date();
    date_end = ui->dateEdit_2->date();
    QSqlQuery query;
    query.prepare("SELECT ID,Number FROM rooms\
                  WHERE  ID NOT IN (SELECT Room_ID FROM reservations WHERE   (ID !=:ID) AND ((julianday(Start_Date) - julianday(:START)>=0 AND julianday(Start_Date) - julianday(:END) <= 0)\
                                                                                             OR (julianday(End_Date) - julianday(:START)>=0 AND julianday(End_Date) - julianday(:END) <= 0)\
                                                                                             OR (julianday(Start_Date) - julianday(:START)<=0 AND julianday(End_Date) - julianday(:END) >= 0) ) )"
                                                                                                                                                                                                 "GROUP BY ID\
                  ORDER BY Number"
                  );

    query.bindValue(":START",date_start);
    query.bindValue(":END",date_end);
    query.bindValue(":ID",id_r);

    query.exec();

    while (query.next()) {
        ui->comboBox->addItem(query.value(1).toString(),query.value(0).toInt());
    }
    ui->comboBox->setCurrentIndex(ui->comboBox->findData(room_id));
}
void Reservation_redactor::ready()
{
    if (ui->comboBox->currentIndex() == -1) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран номер, или свободных номеров на выбранные даты нет!"), QMessageBox::Ok);
    }
    else {
        QSqlQuery query;
        query.prepare("UPDATE reservations SET Customer_ID=:CID, Room_ID =:RID, Start_Date=:START, End_Date=:END, Status=:STAT WHERE ID=:ID");
        query.bindValue(":START",date_start);
        query.bindValue(":END",date_end);
        query.bindValue(":ID",id_r);
        query.bindValue(":RID",ui->comboBox->currentData().toInt());
        query.bindValue(":CID",customer_id);
        query.bindValue(":STAT",ui->comboBox_2->currentData().toInt());
        query.exec();
        accept();
    }
}
