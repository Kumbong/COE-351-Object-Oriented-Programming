#include "salestablemodel.h"
#include <QBrush>
#include <QFont>
#include <QtDebug>
bool SalesTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    toBeInserted.unitsPurchased = 1;
    for(int i = 0 ; i<itemsPurchased.length(); i++){

        if(itemsPurchased.at(i).name == toBeInserted.name){
            toBeInserted.unitsPurchased = itemsPurchased.at(i).unitsPurchased+1;
            removeRows(i,1);
            break;
          }


    }


    for (int row=0; row < rows; row++) {
        itemsPurchased.append(toBeInserted);
    }

    endInsertRows();
    return true;
}
bool SalesTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows && position<itemsPurchased.length(); ++row) {
         itemsPurchased.removeAt(position+row);
    }

    endRemoveRows();
    return true;
}

void SalesTableModel::append(FoodItem item)
{
    toBeInserted = item;

    insertRows(itemsPurchased.length(),1);
}

void SalesTableModel::removeAll()
{
    beginRemoveRows(QModelIndex(), 0, itemsPurchased.length()-1);
       itemsPurchased.clear();
    endRemoveRows();

}

Qt::ItemFlags SalesTableModel::flags(const QModelIndex &index) const
{
   if(index.column() == 1)
       return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
   return QAbstractTableModel::flags(index);
}

double SalesTableModel::total()
{
    double total=0;
    for(int i = 0; i<itemsPurchased.length();i++){
        total += itemsPurchased.at(i).unitsPurchased * itemsPurchased.at(i).price;
    }
    return total;
}

double SalesTableModel::discount()
{
    double total=0;
    for(int i = 0; i<itemsPurchased.length();i++){
        total += itemsPurchased.at(i).unitsPurchased * itemsPurchased.at(i).discount;
    }
    return total;
}

SalesTableModel::SalesTableModel()
{

}
SalesTableModel::SalesTableModel(QList<FoodItem> &items)
{
    itemsPurchased.append(items);
}

SalesTableModel::SalesTableModel(FoodItem item)
{
    itemsPurchased.append(item);
}

int SalesTableModel::rowCount(const QModelIndex &parent) const
{
        if(itemsPurchased.length()==0)
            return 10;

        return itemsPurchased.length();
}

int SalesTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant SalesTableModel::data(const QModelIndex &index, int role) const
{
    double actualPrice;
    if(role == Qt::DisplayRole && index.row() < itemsPurchased.length()){
        if(index.column() == 0)
            return itemsPurchased.at(index.row()).name;
        else if(index.column() == 1){
            return itemsPurchased.at(index.row()).unitsPurchased;
        }
        else if(index.column() == 2){
            actualPrice = itemsPurchased.at(index.row()).price;
            return actualPrice;
        }
        else if(index.column() == 3){
            return itemsPurchased.at(index.row()).discount * itemsPurchased.at(index.row()).unitsPurchased;
        }
        else if(index.column() == 4){
             actualPrice = itemsPurchased.at(index.row()).price - itemsPurchased.at(index.row()).discount;
            return actualPrice * itemsPurchased.at(index.row()).unitsPurchased;
        }
    }
    return QVariant();
}

bool SalesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column()==1/*quantity column*/){
        if(value.toInt()>0){
           if(index.row()<itemsPurchased.length())
              itemsPurchased[index.row()].unitsPurchased = value.toInt();
        }
    }
}

QVariant SalesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section == 0)
                return(QVariant(QString("Item")));
            else if(section == 1)
                return QVariant(QString("Quantity"));
            else if(section == 2)
                return QVariant(QString("Unit price"));
            else if(section == 3)
                return QVariant(QString("Discount"));
            else if(section == 4)
                 return QVariant(QString("Sub Total"));
        }
    }
    else if(role == Qt::FontRole && orientation ==Qt::Horizontal){
        return QVariant(QFont("MS Shell Dlg",12));
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QList<FoodItem> SalesTableModel::modelList()
{
    return itemsPurchased;
}
