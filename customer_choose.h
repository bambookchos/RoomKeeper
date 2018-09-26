#ifndef CUSTOMER_CHOOSE_H
#define CUSTOMER_CHOOSE_H

#include <QDialog>

namespace Ui {
class Customer_choose;
}

class Customer_choose : public QDialog
{
    Q_OBJECT

public:
    explicit Customer_choose(QWidget *parent = 0);
    ~Customer_choose();

private:
    Ui::Customer_choose *ui;
};

#endif // CUSTOMER_CHOOSE_H
