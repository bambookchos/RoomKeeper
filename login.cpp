#include "login.h"
#include "ui_login.h"
int PERM[9];

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("SELECT * FROM personal ORDER BY Name");
    while (query.next()) {
        ui->comboBox->addItem(query.value(1).toString(),query.value(0).toString());
    }


}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_released()
{
    QSqlQuery query;
    query.prepare("SELECT Password FROM personal WHERE ID=:ID");
    query.bindValue(":ID",ui->comboBox->currentData().toString());
    query.exec();
    query.next();
    if (ui->lineEdit->text() == query.value(0).toString()){
        query.prepare("SELECT * FROM personal WHERE ID=:ID");
        query.bindValue(":ID",ui->comboBox->currentData().toString());
        query.exec();
        query.next();
        PERM[0] = query.value(3).toInt();
        PERM[1] = query.value(4).toInt();
        PERM[2] = query.value(5).toInt();
        PERM[3] = query.value(6).toInt();
        PERM[4] = query.value(7).toInt();
        PERM[5] = query.value(8).toInt();
        PERM[6] = query.value(9).toInt();
        PERM[7] = query.value(10).toInt();
        PERM[8] = query.value(11).toInt();


        this->accept();
    }
    else {
        QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Incorrect password!"), QMessageBox::Ok);
    }
}
