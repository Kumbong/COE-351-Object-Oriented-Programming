#include "inventorytablemodel.h"
#include <QFont>



InventoryTableModel::InventoryTableModel()
{

}
bool InventoryTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    itemsInStock.append(toBeInserted);

    endInsertRows();
    return true;
}

bool InventoryTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows && position<itemsInStock.length(); ++row) {
         itemsInStock.removeAt(position+row);
    }

    endRemoveRows();
    return true;
}
void InventoryTableModel::append(InventoryItem item)
{
   toBeInserted = item;
   insertRows(itemsInStock.length(),1);
}

InventoryTableModel::InventoryTableModel(QList<InventoryItem> &items)
{
    itemsInStock = items;
}

InventoryTableModel::InventoryTableModel(InventoryItem item)
{
   itemsInStock.append(item);
}

int InventoryTableModel::rowCount(const QModelIndex &parent) const
{
    return 22;
}

int InventoryTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant InventoryTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole && index.row() <itemsInStock.length()){
       if(index.column() == 0)
           return itemsInStock.at(index.row()).name;
       else if(index.column() == 1)
           return itemsInStock.at(index.row()).price;
       else if(index.column() == 2)
           return itemsInStock.at(index.row()).stockin;
       else if(index.column() == 3)
           return itemsInStock.at(index.row()).stockout;
       else if(index.column() == 4)
           return itemsInStock.at(index.row()).stockLeft;
    }
    return QVariant();
}

QVariant InventoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section == 0)
                return(QVariant(QString("Item")));
            else if(section == 1)
                return QVariant(QString("Unit price"));
            else if(section == 2)
                return QVariant(QString("Stock in"));
            else if(section == 3)
                return QVariant(QString("Stock out"));
            else if(section == 4)
                 return QVariant(QString("Balance remaining"));
        }
    }
    else if(role == Qt::FontRole && orientation ==Qt::Horizontal){
        return QVariant(QFont("MS Shell Dlg",12));
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QList<InventoryItem> InventoryTableModel::modelList()
{
    return itemsInStock;
}

