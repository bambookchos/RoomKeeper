#ifndef ROOM_ADD_H
#define ROOM_ADD_H

#include <QDialog>
#include <QtSql>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QDebug>

namespace Ui {
class Room_add;
}
struct character {
    QComboBox *cb;
    int id;
};

class Room_add : public QDialog
{
    Q_OBJECT

public:
    explicit Room_add(QWidget *parent = 0);
    explicit Room_add(int id, QWidget *parent = 0);
    ~Room_add();

private:
    Ui::Room_add *ui;
    QVBoxLayout *flowLayout;
    QVector<character*> characters;
    int id;

private slots:
    void save();
};



#endif // ROOM_ADD_H
