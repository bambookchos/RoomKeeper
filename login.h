#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPixmap>

#define BOOKING_ADD_PERM 0
#define BOOKING_EDIT_PERM 1
#define BOOKING_IN_OUT_PERM 2
#define CHAR_PERM 3
#define ROOM_PERM 4
#define CUSTOMER_ADD_PERM 5
#define CUSTOMER_EDIT_PERM 6
#define PERSONAL_PERM 7



namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_released();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
