#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QDebug>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include <fooditem.h>
#include <QTableView>
#include "user.h"
#include "transaction.h"

class LoginScreen;
class CreateAccountScreen;
class  SalesTableModel;
class InventoryTableModel;
class QSqlTableModel;

namespace Ui {
class MainWindow;
}
enum Pages{PointOfSale,Inventory,Statistics,Transactions,Settings};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    bool createAccount();
    bool login(QString username,QString password);
    void loginFromCreateAccountPage();
    void createNewAccount(QList<QString> list,int accountType);//0 manager account, 1 vendor account
private slots:
    void changePage();
    void forgotPassword(QString username);
    void on_pushButton_13_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();
    void orderMade();

    void on_pushButton_15_clicked();
    void newTransaction();

    void on_paidLineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();
    void printSimpleReceipt(double amountPaid);
    void on_addInventoryItem_clicked();
    void initializeInventoryPage();
    void validateInventoryAddItem();
    void on_updateInventoryItem_clicked();

    void on_searchButton_clicked();
    void changePassword(QString answer,QString password);
    void initializeSettingsPage();


    void on_updateButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginScreen *loginScreen;
    CreateAccountScreen *accountScreen;
    void initializeUi();

    QList<QPushButton*> foodButtons;
    QList<QLabel*> priceLabels;
    QList<QLabel*> nameLabels;
    QList<FoodItem> foodItemList;

    void InitializeLists();

    SalesTableModel *model;
    InventoryTableModel *inventoryModel;
    QSqlDatabase mydb;
    QSqlTableModel *transactionsTableModel;

    //bad bad OOP
    QString answer;
    QString userName;
    User currentUser;
    Transaction currentTransaction;


};

#endif // MAINWINDOW_H
