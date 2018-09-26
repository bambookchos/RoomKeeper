#include "room_add.h"
#include "ui_room_add.h"

Room_add::Room_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Room_add)
{
    id =0;
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));

    flowLayout = new QVBoxLayout;
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );
    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );



    QSqlQuery query;
    query.exec("SELECT * FROM characters");



    while (query.next()) {

        QWidget *window = new QWidget;
        QLabel *l = new QLabel(query.value(1).toString());
        QComboBox *c = new QComboBox();
        QFormLayout *f = new QFormLayout;
        f->addRow(l,c);

        character* cha = new character;
        cha->cb = c;
        cha->id = query.value(0).toInt();
        characters.append(cha);

        QSqlQuery query2;
        query2.prepare("SELECT * FROM character_vars WHERE C_ID=:ID");
        query2.bindValue(":ID",query.value(0).toInt());
        query2.exec();
        while (query2.next()) {
            c->addItem(query2.value(2).toString(),query2.value(0).toInt());
        }

        f->setSizeConstraint(QLayout::SetMinAndMaxSize);
        f->setContentsMargins(0, 0, 0, 0);
        window->setLayout(f);

        flowLayout->addWidget(window);

    }
}

Room_add::Room_add(int id_r,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Room_add)
{
    id =id_r;
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));

    flowLayout = new QVBoxLayout;
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );

    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );


    QSqlQuery query;
    query.prepare("SELECT Number FROM rooms WHERE ID=:ID");
    query.bindValue(":ID",id);
    query.exec();
    query.next();
    ui->le_number->setText(query.value(0).toString());

    query.exec("SELECT * FROM characters");



    while (query.next()) {

        QWidget *window = new QWidget;
        QLabel *l = new QLabel(query.value(1).toString());
        QComboBox *c = new QComboBox();
        QFormLayout *f = new QFormLayout;
        f->addRow(l,c);



        character* cha = new character;
        cha->cb = c;
        cha->id = query.value(0).toInt();
        characters.append(cha);

        QSqlQuery query2;
        query2.prepare("SELECT * FROM character_vars WHERE C_ID=:ID");
        query2.bindValue(":ID",query.value(0).toInt());
        query2.exec();
        while (query2.next()) {
            c->addItem(query2.value(2).toString(),query2.value(0).toInt());
        }


        query2.prepare("SELECT C_V_ID FROM room_characters WHERE R_ID=:RID AND C_ID=:CID");
        query2.bindValue(":RID",id);
        query2.bindValue(":CID",cha->id);
        query2.exec();
        query2.next();

        c->setCurrentIndex(c->findData(query2.value(0).toInt()));


        f->setSizeConstraint(QLayout::SetMinAndMaxSize);
        f->setContentsMargins(0, 0, 0, 0);
        window->setLayout(f);

        flowLayout->addWidget(window);

    }
}

Room_add::~Room_add()
{
    delete ui;
}


void Room_add::save()
{
    QSqlQuery query;
    QString number = ui->le_number->text();
    int last_id = 0;

    //UPDATE NAME
    if (id != 0) {
        query.prepare("UPDATE rooms SET Name=:NAME WHERE ID=:ID");
        query.bindValue(":NAME",number);
        query.bindValue(":ID",id);
        query.exec();
        last_id = id;
    }
    //NEW NAME
    else {
        query.prepare("INSERT INTO rooms VALUES(NULL,:NAME)");
        query.bindValue(":NAME",number);
        query.exec();
        last_id = query.lastInsertId().toInt();
        query.prepare("DELETE FROM rooms WHERE C_ID=:ID");
        query.bindValue(":ID",id);
        query.exec();
    }

    for (int i = 0; i < characters.size(); i++) {
        query.prepare("INSERT INTO room_characters VALUES(NULL,:RID,:CID,:CVID)");
        query.bindValue(":RID",last_id);
        query.bindValue(":CID",characters[i]->id);
        query.bindValue(":CVID",characters[i]->cb->currentData().toInt());
        query.exec();
    }



}
