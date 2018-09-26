#ifndef CHARACTER_ADD_H
#define CHARACTER_ADD_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVector>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class Character_add;
}

struct character_var {
    int id;
    QLineEdit *le;
};

class Character_add : public QDialog
{
    Q_OBJECT

public:
    explicit Character_add(QWidget *parent = 0);
    explicit Character_add(int id, QWidget *parent = 0);
    ~Character_add();

private slots:
    void add_row();
    void delete_row(QObject* a);
        void save();


private:
    Ui::Character_add *ui;
    QVBoxLayout* flowLayout;
    int i;
    int id;
    QVector<character_var*> variant;
};



#endif // CHARACTER_ADD_H
