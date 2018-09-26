#ifndef PERSONAL_MODEL_H
#define PERSONAL_MODEL_H

#include <QSqlTableModel>
#include <QCheckBox>
#include <QDebug>

class Personal_model : public QSqlTableModel
{
    Q_OBJECT
public:
 Personal_model(QObject * parent = 0, QSqlDatabase db = QSqlDatabase() ):QSqlTableModel(parent, db){}
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
#endif // PERSONAL_MODEL_H
