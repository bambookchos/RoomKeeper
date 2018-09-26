#include "secondui.h"
#include "ui_second.h"



SecondUI::SecondUI(QWidget *parent) : QMainWindow(parent), ui(new Ui::SecondUI)
{
    ui->setupUi(this);

    QMenu *admin = ui->menubar->addMenu("Administration");

    QAction *userAct = new QAction(tr("&Edit user..."), this);
    userAct->setShortcuts(QKeySequence::Underline);
    userAct->setStatusTip(tr("Show/edit programm users"));
    admin->addAction(userAct);
    connect(userAct, SIGNAL(triggered(bool)), this, SLOT(add_user()));   //BUTTONS

    QAction *customerAct = new QAction(tr("&Edit customers..."), this);
    customerAct->setShortcuts(QKeySequence::Copy);
    customerAct->setStatusTip(tr("Show/edit customers"));
    admin->addAction(customerAct);
    connect(customerAct, SIGNAL(triggered(bool)), this, SLOT(customers_editor()));   //BUTTONS

    QAction *characterAct = new QAction(tr("&Edit characters..."), this);
    characterAct->setShortcuts(QKeySequence::Cut);
    characterAct->setStatusTip(tr("Show/edit characters"));
    admin->addAction(characterAct);
    connect(characterAct, SIGNAL(triggered(bool)), this, SLOT(characters_editor()));   //BUTTONS

    QAction *roomAct = new QAction(tr("&Edit rooms..."), this);
    roomAct->setShortcuts(QKeySequence::Refresh);
    roomAct->setStatusTip(tr("Show/edit rooms"));
    admin->addAction(roomAct);
    connect(roomAct, SIGNAL(triggered(bool)), this, SLOT(rooms_editor()));   //BUTTONS

    QAction *bookingAct = new QAction(tr("&Edit bookings..."), this);
    bookingAct->setShortcuts(QKeySequence::Bold);
    bookingAct->setStatusTip(tr("Show/edit bookings"));
    admin->addAction(bookingAct);
    connect(bookingAct, SIGNAL(triggered(bool)), this, SLOT(books_editor()));   //BUTTONS


    refresh_table();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh_table()));
    timer->start(15000);

    connect(ui->pb_booking,   SIGNAL(released()), this, SLOT(booking()));
    connect(ui->pb_in,   SIGNAL(released()), this, SLOT(in()));
    connect(ui->pb_out,   SIGNAL(released()), this, SLOT(out()));

}

SecondUI::~SecondUI()
{
    delete ui;
}



void SecondUI::refresh_table() {
    QDate now = QDate::currentDate();
    ui->tableWidget->fill(now.addDays(-2),now.addDays(30),get_all_rooms());

    for (int i = 0; i < labels.size(); i++) {
        labels[i]->deleteLater();
    }
    labels.clear();
    QSqlQuery query;

    query.prepare("SELECT * FROM reservations WHERE "
                  "((julianday(Start_Date) - julianday(:END)<=0) AND Status==0)"
                  "OR ((julianday(End_date) - julianday(:END)<=0) AND Status==1)ORDER BY Start_Date LIMIT 10 ");
    query.bindValue(":END",QDate::currentDate().addDays(2));

    query.exec();
    while (query.next()) {
        QString temp = "";
        if (query.value(5).toInt() == 0) {
            temp += "Заезд ";
            temp+= query.value(3).toDate().toString("dd.MM");
        }
        if (query.value(5).toInt() == 1) {
            temp += "Выезд ";
            temp+= query.value(4).toDate().toString("dd.MM");
        }

        QSqlQuery query2;
        query2.prepare("SELECT Name FROM customers WHERE ID=:ID");
        query2.bindValue(":ID",query.value(1).toInt());
        query2.exec();
        query2.next();
        temp += " "+query2.value(0).toString();


        query2.prepare("SELECT Number FROM rooms WHERE ID=:ID");
        query2.bindValue(":ID",query.value(2).toInt());
        query2.exec();
        query2.next();
        temp += " №"+query2.value(0).toString();

        QLabel *l = new QLabel(temp);
        labels.append(l);
        ui->verticalLayout->addWidget(l);
        ui->verticalLayout->setContentsMargins(0,0,0,0);
        ui->verticalLayout->setAlignment(Qt::AlignTop);
    }



}
void SecondUI::add_user() {
    Personal_edit *user = new Personal_edit();
    user->show();
}

void SecondUI::customers_editor() {
    Customer_editor *customer = new Customer_editor();
    customer->show();
}

void SecondUI::characters_editor() {
    Character_edit *character_edit = new Character_edit();
    character_edit->show();
}

void SecondUI::rooms_editor() {
    Room_edit *room = new Room_edit();
    room->show();
    room->exec();
    refresh_table();
}



void SecondUI::books_editor() {
    Reservations_edit *room = new Reservations_edit();
    room->show();
    room->exec();
    refresh_table();
}

void SecondUI::in() {
    Reservation_choose *room = new Reservation_choose(0);
    room->show();
    room->exec();
    refresh_table();
}


void SecondUI::out() {
    Reservation_choose *room = new Reservation_choose(1);
    room->show();
    room->exec();
    refresh_table();
}




void SecondUI::booking() {
    Booking_new *book = new Booking_new();
    book->show();
    book->exec();
    refresh_table();
}
