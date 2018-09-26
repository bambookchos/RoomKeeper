#include "character_edit.h"
#include "ui_character_edit.h"

extern int PERM[9];

Character_edit::Character_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Character_edit)
{
    ui->setupUi(this);
    connect(ui->pb_add, SIGNAL(released()), this, SLOT(add()));
    connect(ui->pb_edit, SIGNAL(released()), this, SLOT(edit()));
    connect(ui->pb_delete, SIGNAL(released()), this, SLOT(del()));
    ui->tv_characters->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_characters->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tv_characters->verticalHeader()->setVisible(false);
//    ui->tv_characters->setModel(reservations_model);



}



Character_edit::~Character_edit()
{
    delete ui;
}

void Character_edit::show() {
    if (PERM[CHAR_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Character_edit::exec() {
    if (PERM[CHAR_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}

void Character_edit::add() {
    Character_add *add = new Character_add();
    add->show();
    add->exec();
    ui->tv_characters->fill();
}
void Character_edit::edit() {
    QModelIndexList selectedList = ui->tv_characters->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана характеристика!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        int id = ui->tv_characters->item(row,0)->text().toInt();
        Character_add *add = new Character_add(id);
        add->show();
        add->exec();
        ui->tv_characters->fill();
    }
}
void Character_edit::del() {

    QModelIndexList selectedList = ui->tv_characters->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбрана характеристика!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        int id = ui->tv_characters->item(row,0)->text().toInt();
        QSqlQuery query;





        query.prepare("DELETE FROM characters WHERE ID=:ID");
        query.bindValue(":ID",id);
        query.exec();
        //        search();
    }
}
