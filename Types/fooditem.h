#ifndef FOODITEM_H
#define FOODITEM_H
#include <QString>

class FoodItem
{
public:
    FoodItem();
    QString name;
    double price;
    int unitsPurchased;
    double discount;
    QString pictureFile;
};

#endif // FOODITEM_H
