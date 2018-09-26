#ifndef FILTER_ROW_H
#define FILTER_ROW_H
#include <QDebug>
#include <QComboBox>
class Filter_row : public QComboBox
{
    Q_OBJECT
public:
    Filter_row(QWidget *parent = 0) : QComboBox(parent) {connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(sendDataChanged(int)));};

private slots:
  void sendMe(int value);
  void sendDataChanged(int value);
signals:
  void me(QComboBox*,int);
  void currentDataChanged(int);

};

#endif // FILTER_ROW_H
