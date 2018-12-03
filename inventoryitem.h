#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QString>

class InventoryItem
{
public:
    InventoryItem();
    QString name;
    double price;
    int stockin;
    int stockout;
    int stockLeft;

};

#endif // INVENTORYITEM_H
