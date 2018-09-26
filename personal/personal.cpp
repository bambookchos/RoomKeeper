#include "personal.h"
#include "ui_personal.h"

Personal::Personal(QWidget *parent) : QDialog(parent), ui(new Ui::Personal)
{
    user_id = -1;
    ui->setupUi(this);
}

Personal::Personal(int id, QWidget *parent) : QDialog(parent), ui(new Ui::Personal)
{
    user_id = id;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM personal WHERE ID=:ID"));
    query.bindValue(":ID",id);
    query.exec();
    query.next();
    QSqlRecord rec = query.record();
    name = query.value(rec.indexOf("Name")).toString();
    password = query.value(rec.indexOf("Password")).toString();
    rights[0] = query.value(rec.indexOf("Permission 1")).toBool();
    rights[1] = query.value(rec.indexOf("Permission 2")).toBool();
    rights[2] = query.value(rec.indexOf("Permission 3")).toBool();
    rights[3] = query.value(rec.indexOf("Permission 4")).toBool();
    rights[4] = query.value(rec.indexOf("Permission 5")).toBool();
    rights[5] = query.value(rec.indexOf("Permission 6")).toBool();
    rights[6] = query.value(rec.indexOf("Permission 7")).toBool();
    rights[7] = query.value(rec.indexOf("Permission 8")).toBool();
    ui->setupUi(this);
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(password);
    ui->checkBox->setChecked(rights[0]);
    ui->checkBox_2->setChecked(rights[1]);
    ui->checkBox_3->setChecked(rights[2]);
    ui->checkBox_4->setChecked(rights[3]);
    ui->checkBox_5->setChecked(rights[4]);
    ui->checkBox_6->setChecked(rights[5]);
    ui->checkBox_7->setChecked(rights[6]);
    ui->checkBox_8->setChecked(rights[7]);
}

Personal::~Personal()
{
    delete ui;
}

void Personal::on_buttonBox_accepted()
{
    name  = ui->lineEdit->text();
    password = ui->lineEdit_2->text();

    rights[0] = ui->checkBox->isChecked();
    rights[1] = ui->checkBox_2->isChecked();
    rights[2] = ui->checkBox_3->isChecked();
    rights[3] = ui->checkBox_4->isChecked();
    rights[4] = ui->checkBox_5->isChecked();
    rights[5] = ui->checkBox_6->isChecked();
    rights[6] = ui->checkBox_7->isChecked();
    rights[7] = ui->checkBox_8->isChecked();


    QSqlQuery query;
    if (user_id == -1) {
        query.prepare(QString("INSERT INTO personal VALUES(NULL,:NAME,:PASSWORD,:RIGHT1,:RIGHT2,:RIGHT3,:RIGHT4,:RIGHT5,:RIGHT6,:RIGHT7,:RIGHT8)"));
    }
    else{
        query.prepare(QString("UPDATE personal SET Name=:NAME, Password=:PASSWORD, `Permission 1`=:RIGHT1, `Permission 2`=:RIGHT2, `Permission 3`=:RIGHT3, `Permission 4`=:RIGHT4, `Permission 5`=:RIGHT5, `Permission 6`=:RIGHT6, `Permission 7`=:RIGHT7, `Permission 8`=:RIGHT8 WHERE ID=:ID"));
        query.bindValue(":ID",user_id);
    }
    query.bindValue(":NAME",name);
    query.bindValue(":PASSWORD",password);
    query.bindValue(":RIGHT1",rights[0]);
    query.bindValue(":RIGHT2",rights[1]);
    query.bindValue(":RIGHT3",rights[2]);
    query.bindValue(":RIGHT4",rights[3]);
    query.bindValue(":RIGHT5",rights[4]);
    query.bindValue(":RIGHT6",rights[5]);
    query.bindValue(":RIGHT7",rights[6]);
    query.bindValue(":RIGHT8",rights[7]);
    query.exec();

}
