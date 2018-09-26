#include "customer_editor.h"
#include "ui_customer_editor.h"

extern int PERM[9];


Customer_editor::Customer_editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customer_editor)
{
    ui->setupUi(this);


    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM customers");
    ui->tv_customers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_customers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_customers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tv_customers->verticalHeader()->setVisible(false);
    ui->tv_customers->setModel(model);
    connect(ui->le_search, SIGNAL(textChanged(QString)), this, SLOT(search()));
    connect(ui->pb_add, SIGNAL(released()), this, SLOT(add_customer()));
    connect(ui->pb_delete, SIGNAL(released()), this, SLOT(del()));
    connect(ui->pb_edit, SIGNAL(released()), this, SLOT(edit()));
    //    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(end()));
}

Customer_editor::~Customer_editor()
{
    delete ui;
}




void Customer_editor::search() {
    QString text = "'%"+ui->le_search->text()+"%'";
    model->setQuery("SELECT * FROM customers WHERE NAME LIKE "+text);
}
void Customer_editor::add_customer() {
    Customer_add *add = new Customer_add();
    add->show();
    add->exec();
    search();

}

void Customer_editor::edit() {
    QModelIndexList selectedList = ui->tv_customers->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран постоялец!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        id = model->data(model->index(row,0)).toInt();
        Customer_add *add = new Customer_add(id);
        add->show();
        add->exec();
        search();
    }
}

void Customer_editor::del() {




    if (PERM[CUSTOMER_EDIT_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    QModelIndexList selectedList = ui->tv_customers->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран постоялец!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        id = model->data(model->index(row,0)).toInt();
        QSqlQuery query;
        query.prepare("DELETE FROM customers WHERE ID=:ID");
        query.bindValue(":ID",id);
        query.exec();
        search();
    }
}
