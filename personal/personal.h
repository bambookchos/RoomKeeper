#ifndef PERSONAL_H
#define PERSONAL_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
namespace Ui {
class Personal;
}

class Personal : public QDialog
{
    Q_OBJECT

public:
    explicit Personal(QWidget *parent = 0);
    Personal(int id,QWidget *parent = 0);
    ~Personal();


private:
    Ui::Personal *ui;
    QString name;
    QString password;
    bool rights[8];
    int user_id;

private slots:
    void on_buttonBox_accepted();
};

#endif // PERSONAL_H
