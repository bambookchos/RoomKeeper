#include "personal_model.h"



QVariant Personal_model::data(const QModelIndex &index, int role) const
{
    int col = index.column();

    if (col >= 3) //add a checkbox to cell(1,0)
    {
        switch(role){
        case Qt::CheckStateRole:
            if (QSqlTableModel::data(index).toInt() == 1) {
                return Qt::Checked;
            }
            else {
                return Qt::Unchecked;
            }
            break;
        case Qt::DisplayRole:
            return QString();
        default:
            return QSqlTableModel::data(index,role);
        }
    }

    return QSqlTableModel::data(index,role);
}
