#include "character_add.h"
#include "ui_character_add.h"


Character_add::Character_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Character_add)
{
    ui->setupUi(this);

    i=-1;
    id = 0;


    flowLayout = new QVBoxLayout;
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );

    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );


    connect(ui->pb_addRow, SIGNAL(released()), this, SLOT(add_row()));
    connect(this, SIGNAL(accepted()), this, SLOT(save()));

}

Character_add::Character_add(int id_c, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Character_add)
{
    ui->setupUi(this);

    i=-1;
    id = id_c;


    flowLayout = new QVBoxLayout;
    flowLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );

    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );


    connect(ui->pb_addRow, SIGNAL(released()), this, SLOT(add_row()));
    connect(this, SIGNAL(accepted()), this, SLOT(save()));


    QSqlQuery query;
    query.prepare("SELECT Name FROM characters WHERE ID=:ID");
    query.bindValue(":ID",id);
    query.exec();
    query.next();
    ui->le_name->setText(query.value(0).toString());


    query.prepare("SELECT ID,Name FROM character_vars WHERE C_ID=:ID");
    query.bindValue(":ID",id);
    query.exec();
    while (query.next()) {
        add_row();
        variant[variant.size()-1]->id=query.value(0).toInt();
        variant[variant.size()-1]->le->setText(query.value(1).toString());
    }
}

Character_add::~Character_add()
{
    delete ui;
}




void Character_add::add_row()
{
    character_var *temp = new character_var;
    temp->id = i;
    QWidget *window = new QWidget;
    QLineEdit *a = new QLineEdit;
    temp->le = a;
    QPushButton *b = new QPushButton("X");
    QHBoxLayout *h = new QHBoxLayout;

    connect(b, SIGNAL(released()), b, SLOT(deleteLater()));
    connect(b, SIGNAL(released()), a, SLOT(deleteLater()));
    connect(a, SIGNAL(destroyed(QObject*)), this, SLOT(delete_row(QObject*)));
    connect(b, SIGNAL(released()), h, SLOT(deleteLater()));
    connect(b, SIGNAL(released()), window, SLOT(deleteLater()));
    variant.append(temp);
    h->addWidget(a);
    h->addWidget(b);
    h->setSizeConstraint(QLayout::SetMinAndMaxSize);
    h->setContentsMargins(0, 0, 0, 0);
    window->setLayout(h);

    flowLayout->addWidget(window);
    a->setText(QString::number(i));
    i--;
}
void Character_add::save()
{
    QSqlQuery query;
    QString name = ui->le_name->text();
    int last_id = 0;

    //UPDATE NAME
    if (id != 0) {
        query.prepare("UPDATE characters SET Name=:NAME WHERE ID=:ID");
        query.bindValue(":NAME",name);
        query.bindValue(":ID",id);
        query.exec();
    }
    //NEW NAME
    else {
        query.prepare("INSERT INTO characters VALUES(NULL,:NAME)");
        query.bindValue(":NAME",name);
        query.exec();
        last_id = query.lastInsertId().toInt();
    }

    for (int j = 0; j < variant.size(); j++) {
        //DELETED ROW
        if (variant[j]->le == Q_NULLPTR){
            if (id!= 0) {
                QSqlQuery query;
                query.prepare("DELETE FROM character_vars WHERE ID=:ID");
                query.bindValue(":ID",variant[j]->id);
                query.exec();
            }
        }

        else {
            //UPDATE ROW
            if (id!= 0) {

                if  (variant[j]->id > 0) {
                    query.prepare("UPDATE character_vars SET Name=:NAME WHERE ID=:ID");
                    query.bindValue(":ID",variant[j]->id);
                    query.bindValue(":NAME",variant[j]->le->text());
                    query.exec();
                }

                if  (variant[j]->id < 0) {
                    query.prepare("INSERT INTO character_vars VALUES(NULL,:LASTID,:NAME)");
                    query.bindValue(":LASTID",id);
                    query.bindValue(":NAME",variant[j]->le->text());
                    query.exec();
                }


            }
            //NEW ROW
            else {
                query.prepare("INSERT INTO character_vars VALUES(NULL,:LASTID,:NAME)");
                query.bindValue(":LASTID",last_id);
                query.bindValue(":NAME",variant[j]->le->text());
                query.exec();
            }
        }
    }
}
void Character_add::delete_row(QObject *a) {

    for (int i = 0; i < variant.size(); i++) {
        if (variant[i]->le == (QLineEdit*)a) {
            variant[i]->le = Q_NULLPTR;
        }
    }
}
