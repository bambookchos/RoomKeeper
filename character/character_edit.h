#ifndef CHARACTER_EDIT_H
#define CHARACTER_EDIT_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

#include "login.h"
#include "character/character_add.h"

namespace Ui {
class Character_edit;
}

class Character_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Character_edit(QWidget *parent = 0);
    ~Character_edit();
    void show();
    int exec();

private:
    Ui::Character_edit *ui;

private slots:
    void add();
    void edit();
    void del();
};

#endif // CHARACTER_EDIT_H
