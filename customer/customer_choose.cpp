#include "customer_choose.h"
#include "ui_customer_choose.h"

Customer_choose::Customer_choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customer_choose)
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
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(end()));

}

Customer_choose::~Customer_choose()
{
    delete ui;
}


void Customer_choose::search() {
    QString text = "'%"+ui->le_search->text()+"%'";
    model->setQuery("SELECT * FROM customers WHERE NAME LIKE "+text);
}
void Customer_choose::add_customer() {
    Customer_add *add = new Customer_add();
    add->show();
    add->exec();
    search();
}
void Customer_choose::end() {
    QModelIndexList selectedList = ui->tv_customers->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран постоялец!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        id = model->data(model->index(row,0)).toInt();
        accept();
    }
}

