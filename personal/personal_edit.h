#ifndef PERSONAL_EDIT_H
#define PERSONAL_EDIT_H


#include <QDialog>
#include <QDebug>
#include <QStandardItem>
#include <QMessageBox>
#include "personal.h"
#include "personal_model.h"
#include "login.h"

namespace Ui {
class Personal_edit;
}

class Personal_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Personal_edit(QWidget *parent = 0);
    ~Personal_edit();

    void show();
    int exec();

private slots:
    void add_user();
    void edit_user();
    void delete_user();

private:
    Personal_model *personal_model;
    Ui::Personal_edit *ui;
};

#endif // PERSONAL_EDIT_H
