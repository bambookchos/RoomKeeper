#include "personal_edit.h"
#include "ui_personal_edit.h"

extern int PERM[9];

Personal_edit::Personal_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Personal_edit)
{
    ui->setupUi(this);

    //PERSONAL TABLE
    personal_model = new Personal_model(this,QSqlDatabase::database());
    personal_model->setTable("personal");
    personal_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    personal_model->select();

    personal_model->setHeaderData(0, Qt::Horizontal, QObject::tr("N"));
    personal_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Имя"));
    personal_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Пароль"));
    personal_model->setHeaderData(3, Qt::Horizontal, QObject::tr("ДБ"));
    personal_model->setHeaderData(4, Qt::Horizontal, QObject::tr("РБ"));
    personal_model->setHeaderData(5, Qt::Horizontal, QObject::tr("З/В"));
    personal_model->setHeaderData(6, Qt::Horizontal, QObject::tr("Х"));
    personal_model->setHeaderData(7, Qt::Horizontal, QObject::tr("Н"));
    personal_model->setHeaderData(8, Qt::Horizontal, QObject::tr("ДП"));
    personal_model->setHeaderData(9, Qt::Horizontal, QObject::tr("РП"));
    personal_model->setHeaderData(10, Qt::Horizontal, QObject::tr("П"));

    ui->tv_personal->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_personal->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tv_personal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_personal->verticalHeader()->setVisible(false);
    ui->tv_personal->setModel(personal_model);

    connect(ui->pb_newUser, SIGNAL(released()), this, SLOT(add_user()));
    connect(ui->pb_deleteUser, SIGNAL(released()), this, SLOT(delete_user()));
    connect(ui->pb_editUser, SIGNAL(released()), this, SLOT(edit_user()));
}

Personal_edit::~Personal_edit()
{
    delete ui;
}

void Personal_edit::show() {
    if (PERM[PERSONAL_PERM] == 0) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Нет прав доступа!"), QMessageBox::Ok);
        return;
    }
    else {
        return QDialog::show();
    }
}

int Personal_edit::exec() {
    if (PERM[PERSONAL_PERM] == 0) {
        qDebug() << "PERMITIION";
        return 0;
    }
    else {
        return QDialog::exec();
    }
}


void Personal_edit::add_user() {
    Personal *user = new Personal();
    user->show();
    user->exec();
    personal_model->select();
}


void Personal_edit::edit_user() {
    QModelIndexList selectedList = ui->tv_personal->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран пользователь!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        Personal *user = new Personal(personal_model->data(personal_model->index(row,0)).toInt());
        user->show();
        user->exec();
        personal_model->select();
    }
}

void Personal_edit::delete_user() {
    QModelIndexList selectedList = ui->tv_personal->selectionModel()->selectedRows();
    if (selectedList.isEmpty()) {
        QMessageBox::critical(0, QObject::tr("Ошибка"), QObject::tr("Не выбран пользователь!"), QMessageBox::Ok);
        return;
    }
    else {
        int row = selectedList.at(0).row();
        QSqlQuery query;
        query.prepare("DELETE FROM personal WHERE ID=:ID");
        query.bindValue(":ID",personal_model->data(personal_model->index(row,0)).toInt());
        query.exec();

        personal_model->select();
    }
}
