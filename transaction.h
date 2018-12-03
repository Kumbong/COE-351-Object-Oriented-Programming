#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction
{
public:
    Transaction();
    unsigned long long int id;
    QString date;
    QString time;
    QString items;
    double totalCost;
    double totalDiscount;
    double amountToPay;
    double amountPaid;
    double balance;
};

#endif // TRANSACTION_H
