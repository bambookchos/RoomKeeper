#include "booking_new.h"
#include "ui_booking_new.h"


extern int PERM[9];


Booking_new::Booking_new(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Booking_new)
{
    ui->setupUi(this);

    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->dateEdit_2, SIGNAL(dateChanged(QDate)), this, SLOT(filter()));
    connect(ui->pb_booking, SIGNAL(released()), this, SLOT(booking()));
    connect(ui->pb_addRow, SIGNAL(released()), this, SLOT(add_row()));



    flowLayout = new QVBoxLayout;
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );

    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit_2->setCalendarPopup(true);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());



    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    QSqlQuery query;
    query.exec("SELECT * FROM characters");
    while (query.next()) {
        int id = query.value(0).toInt();
        characters.insert(id, query.value(1).toString());

        QSqlQuery query2;
        query2.prepare("SELECT * FROM character_vars WHERE C_ID=:ID");
        query2.bindValue(":ID",id);
        query2.exec();
        while (query2.next()) {
            c_box_data c;
            c.id = query2.value(0).toInt();
            c.name = query2.value(2).toString();
            character_vars.insert(id,c);
        }
    }
}

Booking_new::~Booking_new()
{
    delete ui;
}

void Booking_new::show() {
    if (PERM[BOOKING_ADD_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Booking_new::exec() {
    if (PERM[BOOKING_ADD_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}

void Booking_new::filter(){
    ui->comboBox->clear();

    QDate date_start = ui->dateEdit->date();
    QDate date_end = ui->dateEdit_2->date();
    QString querty_part = "";
    if (filters.size() > 0) {
        querty_part= "AND ID NOT IN (SELECT R_ID FROM room_characters WHERE ";
        for (int i = 0; i < filters.size(); i++) {
            if (i!=0) {
                querty_part+= " OR ";
            }
            querty_part+="(C_ID="+filters[i]->c1->currentData().toString() +" AND C_V_ID!="+filters[i]->c2->currentData().toString() +") ";
        }
        querty_part+= "GROUP BY R_ID)";
    }
    QSqlQuery query;
    query.prepare("SELECT ID,Number FROM rooms\
                  WHERE ID NOT IN (SELECT Room_ID FROM reservations WHERE  (julianday(Start_Date) - julianday(:START)>=0 AND julianday(Start_Date) - julianday(:END) <= 0)\
                                   OR (julianday(End_Date) - julianday(:START)>=0 AND julianday(End_Date) - julianday(:END) <= 0)\
                                   OR (julianday(Start_Date) - julianday(:START)<=0 AND julianday(End_Date) - julianday(:END) >= 0)  )" + querty_part+
                                                                                                                                      "GROUP BY ID\
                  ORDER BY Number"
                  );

    query.bindValue(":START",date_start);
    query.bindValue(":END",date_end);
    query.exec();


    QVector<room> rooms;
    while (query.next()) {

        room temp;
        temp.id = query.value(0).toInt();
        temp.number = query.value(1).toInt();
        rooms.append(temp);
        ui->comboBox->addItem(QString::number(temp.number), temp.id);
    }

    ui->tableWidget->fill(date_start.addDays(-7), date_end.addDays(7), rooms, date_start, date_end);
}

void Booking_new::booking() {
    if (ui->comboBox->currentIndex()==-1) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран номер!"), QMessageBox::Ok);
        return;
    }


    QDate date_start = ui->dateEdit->date();
    QDate date_end = ui->dateEdit_2->date();
    QString number = ui->comboBox->currentData().toString();
    hide();


    Customer_choose* choose = new Customer_choose();
    choose->show();

    if (choose->exec() == 0) {\
        accept();
        return;
    }

    QVector<QString> a;
    a.append(date_start.toString());
    a.append(date_end.toString());
    a.append(number);
    a.append(QString::number(choose->id));

    Booking_finish* finish = new Booking_finish();
    finish->get_data(a);
    finish->show();
    if (finish->exec() == 0) {
        accept();
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO reservations VALUES(NULL,:ID,:NUMBER,:START,:END,0)");
    query.bindValue(":ID",QString::number(choose->id));
    query.bindValue(":NUMBER",number);
    query.bindValue(":START",date_start);
    query.bindValue(":END",date_end);
    query.exec();
    accept();

}


void Booking_new::add_row()
{
    filter_s *temp = new filter_s;
    QWidget *window = new QWidget;
    Filter_row *c1 = new Filter_row;
    Filter_row *c2 = new Filter_row;
    QPushButton *b = new QPushButton("X");
    QHBoxLayout *h = new QHBoxLayout;


    connect(c1,SIGNAL(currentDataChanged(int)),c2,SLOT(sendMe(int)));
    connect(c2,SIGNAL(me(QComboBox*,int)),this,SLOT(set_vals(QComboBox*,int)));
    connect(c2, SIGNAL(currentDataChanged(int)),this,SLOT(filter()));
    connect(c1, SIGNAL(currentDataChanged(int)),this,SLOT(filter()));

    QMapIterator<int, QString> i(characters);
    while (i.hasNext()) {
        i.next();
        c1->addItem(i.value(), i.key());

    }



    temp->c1 =c1;
    temp->c2 =c2;
    filters.append(temp);

    connect(b, SIGNAL(released()), b, SLOT(deleteLater()));
    connect(b, SIGNAL(released()), c1, SLOT(deleteLater()));
    connect(b, SIGNAL(released()), c2, SLOT(deleteLater()));
    connect(c1, SIGNAL(destroyed(QObject*)), this, SLOT(delete_row(QObject*)));
    connect(b, SIGNAL(released()), h, SLOT(deleteLater()));
    connect(b, SIGNAL(released()), window, SLOT(deleteLater()));

    h->addWidget(c1);
    h->addWidget(c2);
    h->addWidget(b);
    h->setSizeConstraint(QLayout::SetMinAndMaxSize);
    h->setContentsMargins(0, 0, 0, 0);
    window->setLayout(h);

    flowLayout->addWidget(window);
    filter();
}

void Booking_new::delete_row(QObject *a) {

    for (int i = 0; i < filters.size(); i++) {
        if (filters[i]->c1 == (QComboBox*)a) {
            filters.remove(i);
        }
    }
    filter();
}

void Booking_new::set_vals(QComboBox* c, int id) {
    c->clear();
    QList<c_box_data> values = character_vars.values(id);
    for (int i = 0; i < values.size(); ++i) {
        c->addItem(values.at(i).name, values.at(i).id);
    }
}

