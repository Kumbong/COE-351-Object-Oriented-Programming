#ifndef INVENTORYTABLEMODEL_H
#define INVENTORYTABLEMODEL_H

#include "inventoryitem.h"
#include <QAbstractTableModel>

class InventoryTableModel : public QAbstractTableModel
{
public:
    InventoryTableModel();
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    void append(InventoryItem item);
    /*void removeAll();
    Qt::ItemFlags flags(const QModelIndex &index) const;*/
    InventoryTableModel(QList<InventoryItem> &items);
    InventoryTableModel(InventoryItem item);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<InventoryItem> modelList();

private:
    QList<InventoryItem> itemsInStock;
    InventoryItem toBeInserted;
};

#endif // INVENTORYTABLEMODEL_H
