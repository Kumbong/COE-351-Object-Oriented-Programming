#ifndef SALESTABLEMODEL_H
#define SALESTABLEMODEL_H

#include "Types/fooditem.h"
#include <QAbstractTableModel>
#include <QString>
#include <QList>



class SalesTableModel : public QAbstractTableModel
{
public:
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    void append(FoodItem item);
    void removeAll();
    Qt::ItemFlags flags(const QModelIndex &index) const;
    double total();
    double discount();
    SalesTableModel();
    SalesTableModel(QList<FoodItem> &items);
    SalesTableModel(FoodItem item);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<FoodItem> modelList();
private:
    QList<FoodItem> itemsPurchased;
    FoodItem toBeInserted;
};

#endif // SALESTABLEMODEL_H
