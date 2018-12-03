#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Initialisation/loginscreen.h"
#include "Initialisation/createaccountscreen.h"
#include "salestablemodel.h"
#include "inventorytablemodel.h"
#include "Dialogs/editmenudialog.h"
#include "Dialogs/changemenuitemdialog.h"
#include "Dialogs/changepassworddialog.h"
#include "fooditem.h"
#include "themewidget.h"



#include <QTableView>
#include <QMessageBox>
#include <QMainWindow>
#include <QSettings>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileInfo>
#include <fstream>
#include <iostream>
#include <string>
#include <QDate>
#include <QTime>
#include <iomanip>
#include <QSqlTableModel>

using namespace std;

bool MainWindow::createAccount()
{
    //handles manipulation of create account screen
     accountScreen = new CreateAccountScreen;
     connect(accountScreen,&CreateAccountScreen::login,this,&MainWindow::loginFromCreateAccountPage);
     connect(accountScreen,&CreateAccountScreen::createAccount,this,&MainWindow::createNewAccount);
     if(loginScreen)
        loginScreen->hide();
     accountScreen->show();
}

bool MainWindow::login(QString username, QString password)
{
     QSqlQuery query;
      query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
      query.addBindValue(username);
      query.addBindValue(password);
      query.exec();

      int counter = 0;
      while(query.next()){
        counter++;
        currentUser.username = query.value(0).toString();
        currentUser.firstName = query.value(1).toString();
        currentUser.lastName = query.value(2).toString();
        currentUser.address = query.value(3).toString();
        currentUser.email = query.value(4).toString();
        currentUser.password = query.value(5).toString();
        currentUser.question = query.value(6).toString();
        currentUser.answer = query.value(7).toString();
        currentUser.accountType = query.value(8).toInt();
      }


     if(counter==1){
         initializeSettingsPage();
         this->show();
         loginScreen->hide();
         ui->userNameEdit->setText(username);
         delete loginScreen;
         loginScreen = nullptr;
         return true;
     }
     else{
         QMessageBox::critical(nullptr, tr("unsuccessfull Login"),
                                        tr("Login unsuccessful.\n"
                                           "Please make sure your user details are correct"));
        return false;
     }
}

void MainWindow::loginFromCreateAccountPage()
{
     if(loginScreen){
         accountScreen->hide();
         delete accountScreen;
         accountScreen = nullptr;
         loginScreen->show();
       }
         else
         qDebug()<<"Login screen points to null";
}

void MainWindow::createNewAccount(QList<QString> list, int accountType)
{
    //bug bug bug
    //instead of userName2 when name already exists we are getting userName1 repeatedly

     QSqlQuery query;
     int counter =0;
     QString userName;
     query.prepare("SELECT * from users WHERE username = ?");
     query.addBindValue(list.first());//first name

      if(query.exec()){
          qDebug()<<"Querrying inside create new account";
          while(query.next())
              counter++;

          if(counter>=1){//a user with the username already exists
               userName = list.first()+QString::number(counter);
          }
          else{
               userName = list.first();
          }
      }else{
          qDebug()<<"Query failed";
      }

      qDebug()<<userName;

      query.prepare("INSERT INTO users(username,firstname,lastname,address,email,password,question,answer,accountType)"
                    "values(?,?,?,?,?,?,?,?,?)");
      query.addBindValue(userName);
      for(int i = 0; i<list.length();i++){
          query.addBindValue(list.at(i));
      }
      query.addBindValue(accountType);

      if(query.exec()){
          qDebug()<<"Values inserted";
          int ret = QMessageBox::information(nullptr, tr("Account created"),
                                         tr("Account successfully create.\n"
                                            "Your username is ")+userName);
          if(ret==QMessageBox::Ok)
              loginFromCreateAccountPage();

      }
}

void MainWindow::changePage()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button == ui->pointOfSaleButton || button == ui->pointOfSaleAltButton){
        if(ui->stackedWidget->currentIndex() != PointOfSale)
            ui->stackedWidget->setCurrentIndex(PointOfSale);
    }
    else if(button == ui->inventoryButton || button == ui->inventoryAltButton){
        if(ui->stackedWidget->currentIndex() != Inventory)
            ui->stackedWidget->setCurrentIndex(Inventory);
    }
    else if(button == ui->statisticsButton || button ==  ui->statisticsAltButton){
        if(ui->stackedWidget->currentIndex() != Statistics)
            ui->stackedWidget->setCurrentIndex(Statistics);
    }
    else if(button == ui->transactionsButton || button == ui->transactionsAltButton){
        if(ui->stackedWidget->currentIndex() != Transactions)
            ui->stackedWidget->setCurrentIndex(Transactions);
    }
    else if(button == ui->settingsButton || button == ui->settingsAltButton){
        if(ui->stackedWidget->currentIndex() != Settings)
            ui->stackedWidget->setCurrentIndex(Settings);
            initializeSettingsPage();
    }
}

void MainWindow::forgotPassword(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ?");
    this->userName = username;
    query.addBindValue(username);
    int counter=0;

    query.exec();
    while(query.next()){
        changePasswordDialog *dialog = new changePasswordDialog;
        dialog->setQuestion(query.value(6).toString());
        dialog->exec();
        answer = query.value(7).toString();
        connect(dialog,&changePasswordDialog::submitted,this,&MainWindow::changePassword);
        counter++;
        qDebug()<<answer;

    }

    if(counter<1){
        QMessageBox::warning(nullptr, tr("User not found"),                                                 tr("No such user exists.\n"));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/SQlite/kenkeyBoutique.db");

    model = new SalesTableModel;
    inventoryModel = new InventoryTableModel;
    ui->inventoryTable->setModel(inventoryModel);


    ui->tableView->setModel(model);
    initializeUi();

    if(mydb.open())
        qDebug()<<"Connected";
    else{
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                   QObject::tr("Unable to establish a database connection.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }

    ThemeWidget *widget = new ThemeWidget;
    ui->statisticsPageLayout->addWidget(widget);

   initializeInventoryPage();
   InitializeLists();

   loginScreen = new LoginScreen;
   loginScreen->show();
      connect(loginScreen,&LoginScreen::login,this,&MainWindow::login);
      connect(loginScreen,&LoginScreen::createAccount,this,&MainWindow::createAccount);
      connect(loginScreen,&LoginScreen::forgotPassword,this,&MainWindow::forgotPassword);


      transactionsTableModel = new QSqlTableModel(Q_NULLPTR, mydb);
      transactionsTableModel->setTable("transactions");
      //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
      transactionsTableModel->select();
      transactionsTableModel->setHeaderData(0, Qt::Horizontal, tr("Transaction ID"));
      transactionsTableModel->setHeaderData(1, Qt::Horizontal, tr("Date"));
      transactionsTableModel->setHeaderData(2, Qt::Horizontal, tr("Time"));
      transactionsTableModel->setHeaderData(3, Qt::Horizontal, tr("Items"));
      transactionsTableModel->setHeaderData(4, Qt::Horizontal, tr("Total cost"));
      transactionsTableModel->setHeaderData(5, Qt::Horizontal, tr("Total Discount"));
      transactionsTableModel->setHeaderData(6, Qt::Horizontal, tr("Amount to Pay"));
      transactionsTableModel->setHeaderData(7, Qt::Horizontal, tr("Amount paid"));
      transactionsTableModel->setHeaderData(8, Qt::Horizontal, tr("Balance"));

      ui->transactionsTableView->setModel(transactionsTableModel);
      ui->transactionsTableView->resizeRowsToContents();
      ui->transactionsTableView->setColumnWidth(1,200);
      ui->transactionsTableView->setColumnWidth(2,150);
      ui->transactionsTableView->setColumnWidth(3,500);
      //view->hideColumn(0); // don't show the ID
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeUi()
{


    ui->inventoryTable->setColumnWidth(0,350);
    ui->inventoryTable->setColumnWidth(1,350);
    ui->inventoryTable->setColumnWidth(3,220);
    ui->inventoryTable->setColumnWidth(4,200);
    ui->inventoryTable->setColumnWidth(5,200);
    ui->tableView->setColumnWidth(0,300);
    ui->tableView->setColumnWidth(2,147);
    ui->tableView->setColumnWidth(3,147);
    ui->tableView->setColumnWidth(4,147);

     ui->stackedWidget->setCurrentIndex(PointOfSale);
    connect(ui->pointOfSaleButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->inventoryButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->statisticsButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->pointOfSaleAltButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->inventoryAltButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->statisticsAltButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->settingsButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->settingsAltButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->transactionsButton,&QPushButton::clicked,this,&MainWindow::changePage);
    connect(ui->transactionsAltButton,&QPushButton::clicked,this,&MainWindow::changePage);

    foodButtons.append(ui->button_1);
    foodButtons.append(ui->button_2);
    foodButtons.append(ui->button_3);
    foodButtons.append(ui->button_4);
    foodButtons.append(ui->button_5);
    foodButtons.append(ui->button_6);
    foodButtons.append(ui->button_7);
    foodButtons.append(ui->button_8);
    foodButtons.append(ui->button_9);
    foodButtons.append(ui->button_10);
    foodButtons.append(ui->button_11);
    foodButtons.append(ui->button_12);
    foodButtons.append(ui->button_13);
    foodButtons.append(ui->button_14);
    foodButtons.append(ui->button_15);
    foodButtons.append(ui->button_16);
    foodButtons.append(ui->button_17);
    foodButtons.append(ui->button_18);
    foodButtons.append(ui->button_19);
    foodButtons.append(ui->button_20);
    foodButtons.append(ui->button_21);

    priceLabels.append(ui->priceLabel_1);
    priceLabels.append(ui->priceLabel_2);
    priceLabels.append(ui->priceLabel_3);
    priceLabels.append(ui->priceLabel_4);
    priceLabels.append(ui->priceLabel_5);
    priceLabels.append(ui->priceLabel_6);
    priceLabels.append(ui->priceLabel_7);
    priceLabels.append(ui->priceLabel_8);
    priceLabels.append(ui->priceLabel_9);
    priceLabels.append(ui->priceLabel_10);
    priceLabels.append(ui->priceLabel_11);
    priceLabels.append(ui->priceLabel_12);
    priceLabels.append(ui->priceLabel_13);
    priceLabels.append(ui->priceLabel_14);
    priceLabels.append(ui->priceLabel_15);
    priceLabels.append(ui->priceLabel_16);
    priceLabels.append(ui->priceLabel_17);
    priceLabels.append(ui->priceLabel_18);
    priceLabels.append(ui->priceLabel_19);
    priceLabels.append(ui->priceLabel_20);
    priceLabels.append(ui->priceLabel_21);

    nameLabels.append(ui->nameLabel_1);
    nameLabels.append(ui->nameLabel_2);
    nameLabels.append(ui->nameLabel_3);
    nameLabels.append(ui->nameLabel_4);
    nameLabels.append(ui->nameLabel_5);
    nameLabels.append(ui->nameLabel_6);
    nameLabels.append(ui->nameLabel_7);
    nameLabels.append(ui->nameLabel_8);
    nameLabels.append(ui->nameLabel_9);
    nameLabels.append(ui->nameLabel_10);
    nameLabels.append(ui->nameLabel_11);
    nameLabels.append(ui->nameLabel_12);
    nameLabels.append(ui->nameLabel_13);
    nameLabels.append(ui->nameLabel_14);
    nameLabels.append(ui->nameLabel_15);
    nameLabels.append(ui->nameLabel_16);
    nameLabels.append(ui->nameLabel_17);
    nameLabels.append(ui->nameLabel_18);
    nameLabels.append(ui->nameLabel_19);
    nameLabels.append(ui->nameLabel_20);
    nameLabels.append(ui->nameLabel_21);

    ui->questionCombo_2->addItem("Which phone number do you remember most from your childhood?");
    ui->questionCombo_2->addItem("What was your favorite place to visit as a child?");
    ui->questionCombo_2->addItem("Who is your favorite actor, musician, or artist?");
    ui->questionCombo_2->addItem("What is the name of your favorite pet?");
    ui->questionCombo_2->addItem("what is your favorite social media website");
    ui->questionCombo_2->addItem("what is your favorite online platform");
    ui->questionCombo_2->addItem("what is your favorite forum");
    ui->questionCombo_2->addItem("what is your favorite website");
    ui->questionCombo_2->addItem("Which is your favorite web browser?");
    ui->questionCombo_2->addItem("What was your high school mascot?");
    ui->questionCombo_2->addItem("What is the name of your first grade teacher?");
    ui->questionCombo_2->addItem("What is your father's middle name?");
    ui->questionCombo_2->addItem("What is your favorite color?");
    ui->questionCombo_2->addItem("When is your anniversary?");
    ui->questionCombo_2->addItem("In what city were you born?");
    ui->questionCombo_2->addItem("What high school did you attend?");
    ui->questionCombo_2->addItem("What is the name of your first school?");
    ui->questionCombo_2->addItem("What is your favorite movie?");
    ui->questionCombo_2->addItem("What is your mother's maiden name?");
    ui->questionCombo_2->addItem("What street did you grow up on?");
    ui->questionCombo_2->addItem("What was the make of your first car?");
}

void MainWindow::InitializeLists()
{
    QSqlQuery query;
    query.exec("SELECT * FROM foodItems");

    FoodItem item;
    int i = 0;
    while (query.next() && i< nameLabels.length()) {
          item.name = query.value(0).toString();
          item.price = query.value(1).toDouble();
          item.discount = query.value(2).toDouble();
          item.pictureFile = query.value(3).toString();

          nameLabels.at(i)->setText(item.name);
          priceLabels.at(i)->setText(QString::number(item.price));
          foodButtons.at(i)->setIcon(QIcon(item.pictureFile));
          foodButtons.at(i)->setIconSize(QSize(70,70));
          foodItemList.insert(i,item);
          connect(foodButtons.at(i),&QPushButton::clicked,this,&MainWindow::orderMade);
          i++;
      }
    for(int j = i; j<nameLabels.length();j++){
        nameLabels.at(j)->setText("");
        priceLabels.at(j)->setText("");
        foodButtons.at(j)->setIcon(QIcon("C:/Users/HP/Desktop/Projects/Kenkey_Boutique/Resources/foodItem.png"));
        foodButtons.at(j)->setIconSize(QSize(70,70));
    }
}


void MainWindow::on_pushButton_13_clicked()
{
   //add item button clicked

    EditMenuDialog *dialog= new EditMenuDialog;
    QSqlQuery query;
    QFileInfo file;

     dialog->setWindowTitle("Add item");
     dialog->setWindowIcon(QIcon(":/add.png"));
    FoodItem foodItem;
    switch (dialog->exec()) {
    case QDialog::Accepted:
        qDebug()<<"Accepted";
        foodItem.name = dialog->name();
        foodItem.price = dialog->price();
        foodItem.discount = dialog->discount();
        foodItem.pictureFile = dialog->picture();

        for(int i=0; i<nameLabels.length();i++){
        if(nameLabels.at(i)->text() == foodItem.name){
            QMessageBox::critical(nullptr
                                  , tr("Insertion Failed"),
                                            tr("Failed to add item requested.\n"
                                               "Item already exists."), QMessageBox::Cancel);
          return;
        }
        }
        query.prepare("INSERT INTO foodItems(name, price, discount,pictureFileName) "
                      "VALUES (?, ?, ?,?)");
        query.addBindValue(foodItem.name.toLower());
        query.addBindValue(foodItem.price);
        query.addBindValue(foodItem.discount);

        file.setFile(foodItem.pictureFile);

        if(file.exists())
            query.addBindValue(foodItem.pictureFile);
        else
            query.addBindValue("C:/Users/HP/Desktop/Projects/Kenkey_Boutique/Resources/foodItem.png");
        query.exec();
        break;
    case QDialog::Rejected:
        break;
    default:
        break;
    }
    delete dialog;

    InitializeLists();
}

void MainWindow::on_pushButton_24_clicked()
{
    //edit item button clicked

    changeMenuItemDialog *dialog= new changeMenuItemDialog;
    QSqlQuery query;

     dialog->setWindowTitle("Edit item");
     dialog->setWindowIcon(QIcon(":/edit.png"));
    FoodItem foodItem;
    QFileInfo file;

    switch (dialog->exec()) {
    case QDialog::Accepted:
        qDebug()<<"Accepted";
        foodItem.name = dialog->newName();
        foodItem.price = dialog->newPrice();
        foodItem.discount = dialog->newDiscount();
        foodItem.pictureFile = dialog->newPicture();

        query.prepare("UPDATE foodItems set name=?, price=?, discount=?,pictureFileName=? WHERE name = ?");
        query.addBindValue(foodItem.name.toLower());
        query.addBindValue(foodItem.price);
        query.addBindValue(foodItem.discount);

        file.setFile(foodItem.pictureFile);
        if(file.exists())
            query.addBindValue(foodItem.pictureFile);
        else
            query.addBindValue("C:/Users/HP/Desktop/Projects/Kenkey_Boutique/Resources/foodItem.png");

        query.addBindValue(dialog->name());
        query.exec();

        /*for(int i=0; i<nameLabels.length();i++){
        if(nameLabels.at(i)->text() == foodItem.name){
            QMessageBox::critical(nullptr
                                  , tr("Update Failed"),
                                            tr("Failed to edit item requested.\n"
                                               "Item with same name already exists."), QMessageBox::Cancel);
          return;
        }
        }*/
        if(query.numRowsAffected()<1){
            QMessageBox::critical(nullptr
                                  , tr("Update Failed"),
                                            tr("Failed to make changes requested.\n"
                                               "Please make sure the item exists"), QMessageBox::Cancel);
          return;
        }
        break;
    case QDialog::Rejected:
        break;
    default:
        break;
    }
    delete dialog;

    //initializeInventoryPage();
    InitializeLists();
}
void MainWindow::on_pushButton_25_clicked(){
    //remove item button clicked

    EditMenuDialog *dialog= new EditMenuDialog;
    QSqlQuery query;

     dialog->setWindowTitle("Remove item");
     dialog->setWindowIcon(QIcon(":/remove.png"));
     dialog->disableSections();

    FoodItem foodItem;


    switch (dialog->exec()) {
    case QDialog::Accepted:
        qDebug()<<"Accepted";
        foodItem.name = dialog->name();
        foodItem.price = dialog->price();
        foodItem.discount = dialog->discount();
        foodItem.pictureFile = dialog->picture();

        query.prepare("DELETE from foodItems WHERE name=?");
        query.addBindValue(foodItem.name.toLower());
        query.exec();

        if(query.numRowsAffected()<1){
            QMessageBox::critical(nullptr
                                  , tr("Delete Failed"),
                                            tr("Failed to remove item requested.\n"
                                               "Please make sure the item exists"), QMessageBox::Cancel);
          return;
        }
        break;
    case QDialog::Rejected:
        break;
    default:
        break;
    }
    delete dialog;
    InitializeLists();
}

void MainWindow::orderMade()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int index = foodButtons.indexOf(button);

    FoodItem item = foodItemList.at(index);

    model->append(item);

   ui->balanceLineEdit->setText("");
   ui->totalLabel->setText("Gh " +QString::number(model->total()));
   ui->discountLabel->setText("Gh " +QString::number(model->discount()));
   ui->amountToPayLabel->setText("Gh "+QString::number(model->total()-model->discount()));
}

void MainWindow::on_pushButton_15_clicked()
{
    //make transaction button clicked

    QSqlQuery query;
   //return if no transaction was made
   if(model->rowCount()==0)
       return;

   double amountPaid =  ui->paidLineEdit->text().toDouble();
   double amountToPay = model->total() - model->discount();
   double balance = amountPaid - amountToPay;

   //only go ahead to perform transaction if the amount paid is more than or equal to what is to be paid
   if(balance>=0){
       ui->balanceLineEdit->setText(QString::number(balance));


       int ret = QMessageBox::information(nullptr, tr("Successfull transaction"),
                                      tr("Transaction successfull.\n"
                                         "Do you want to proceed to a new transaction?"),
                                      QMessageBox::Yes | QMessageBox::No);


       //add the items into the transactions table in the database
       QList<FoodItem> m_list = model->modelList();

       /*if(*/query.exec("select * from number_of_transactions");//)
         //      qDebug()<<"number of transactions selected from numTransactions database";
      // else
            // qDebug()<<"Failed to query number_of_transactions";

       //check if there is a value in the query object and position the query object to valid record

       if(query.next())
         currentTransaction.id = query.value(0).toULongLong()+1;


       if(ui->simpleReceipt->isChecked())
            printSimpleReceipt(amountPaid);

       for(int i=0; i<m_list.length();i++){
           //qDebug()<<"m_list.length > 0 ";

          //set current transaction id. number of transactions are stored in database table numTransactions

           query.prepare("UPDATE number_of_transactions SET count = ?");
           query.addBindValue(currentTransaction.id);
           query.exec();

           currentTransaction.date = QDate::currentDate().toString("ddd MMMM d yyyy");
           currentTransaction.time = QTime::currentTime().toString("hh:mm:ss");
           currentTransaction.items.append(m_list.at(i).name).append(" x ").append(QString::number(m_list.at(i).unitsPurchased));
               //dont add a comma at the end of the last item
              if(i!= m_list.length()-1)
                  currentTransaction.items.append(", ");
       }
       currentTransaction.totalCost = model->total();
       currentTransaction.totalDiscount = model->discount();
       currentTransaction.amountToPay = currentTransaction.totalCost - currentTransaction.totalDiscount;
       currentTransaction.amountPaid = amountPaid;
       currentTransaction.balance = balance;

       query.prepare("INSERT into transactions(id,date,time,items,totalCost,totalDiscount,amountToPay,amountPaid,balance) values(?,?,?,?,?,?,?,?,?)");
       query.addBindValue(currentTransaction.id);
       query.addBindValue(currentTransaction.date);
       query.addBindValue(currentTransaction.time);
       query.addBindValue(currentTransaction.items);
       query.addBindValue(currentTransaction.totalCost);
       query.addBindValue(currentTransaction.totalDiscount);
       query.addBindValue(currentTransaction.amountToPay);
       query.addBindValue(currentTransaction.amountPaid);
       query.addBindValue(currentTransaction.balance);

       if(query.exec())
           qDebug()<<"Items inserted";
       //end add items into the transactions table in the database

       //proceed to a new transaction if the user requests one from the message box
       switch (ret) {
       case QMessageBox::Yes:
           newTransaction();
           break;
       default:
           break;
       }
   }
   else{//alert the user the amount paid is insufficient
       QMessageBox::critical(nullptr
                             , tr("Transaction Failed"),
                                       tr("Failed to complete transaction.\n"
                                          "You do not have enough money"), QMessageBox::Cancel);
       ui->balanceLineEdit->setText(QString::number(balance));
   }

}

void MainWindow::newTransaction()
{
    model->removeAll();
    ui->balanceLineEdit->setText("");
    ui->totalLabel->setText("");
    ui->discountLabel->setText("");
    ui->amountToPayLabel->setText("");
    ui->paidLineEdit->setText("");

}

void MainWindow::on_paidLineEdit_textChanged(const QString &arg1)
{
   ui->balanceLineEdit->setText("");
}

void MainWindow::on_pushButton_clicked()
{
   //new transaction button clicked
    if(model->rowCount() != 0)
        newTransaction();
}

void MainWindow::printSimpleReceipt(double amountPaid)
{
  ofstream outfile;

  QString fileName;
  QList<FoodItem> items = model->modelList();


  fileName = "C:/Users/HP/Desktop/Projects/Kenkey_Boutique/Receipts/" + QDate::currentDate().toString("dd.MM.yyyy")+"__"+QTime::currentTime().toString("hh.mm.ss")+".txt";
  outfile.open(fileName.toLocal8Bit().constData());
  outfile<<"Transaction ID: "<<currentTransaction.id<<"\tKenkey Boutique\t\t"<<QDate::currentDate().toString("ddd MMMM d yyyy").toLocal8Bit().constData()<<" "<<QTime::currentTime().toString("hh:mm").toLocal8Bit().constData()<<std::endl;
  outfile<<"----------------------------------------------------------------------"<<std::endl;
  double grandTotal = 0,totalDiscount = 0,payable=0;
  outfile<<setw(20)<<left<<"Item\t"<<setw(10)<<"Unit price\t"<<setw(10)<< "Quantity\t"<<setw(10)<<"Subtotal"<<std::endl;
  for(int i=0; i<items.length();i++){
      double total = items.at(i).unitsPurchased *items.at(i).price;
      grandTotal+=total;
      totalDiscount += items.at(i).unitsPurchased*items.at(i).discount;
      outfile<<setw(20)<<left<<items.at(i).name.toLocal8Bit().constData()<<"\t"<<setw(10)<<items.at(i).price<<"\t"<<setw(10)<<items.at(i).unitsPurchased<<"\t"<<setw(10)<<total<<std::endl;
  }
  outfile<<"--------------------------------------------------------------------"<<std::endl;
  outfile<<setw(20)<<"Total"<<right<<setw(40)<<grandTotal<<std::endl;
  outfile<<left<<setw(20)<<"Total Discount"<<right<<setw(40)<<totalDiscount<<std::endl;
  payable = grandTotal-totalDiscount;
  outfile<<left<<setw(20)<<"Amount Payable"<<right<<setw(40)<<payable<<std::endl;
  outfile<<"--------------------------------------------------------------------"<<std::endl;
  outfile<<setw(20)<<left<<"Amount Paid"<<right<<setw(40)<<amountPaid<<std::endl;
  outfile<<setw(20)<<left<<"Balance"<<right<<setw(40)<<amountPaid-payable<<std::endl;

  outfile.close();
}

void MainWindow::on_addInventoryItem_clicked()
{
  InventoryItem item;
  item.name = ui->addInventoryItemEdit->text();
  item.price = ui->priceSpinBox->value();
  item.stockin = ui->stockinSpinBox->value();
  item.stockout = ui->stockoutSpinBox->value();
  item.stockLeft = item.stockin - item.stockout;

  QSqlQuery prequery;

  prequery.prepare("SELECT * from inventoryTable where name = ?");
  prequery.addBindValue(item.name.toLower());

   prequery.exec();

   int counter = 0;
   while(prequery.next())
       counter++;

      qDebug()<<counter;

  qDebug()<<prequery.size();
  QSqlQuery query;

  if(counter !=0){
      QMessageBox::critical(nullptr
                            , tr("Insertion Failed"),
                                      tr("Failed to add Item requested.\n"
                                         "An item already exists with the same name"), QMessageBox::Cancel);
 }
  else{
      query.prepare("INSERT INTO inventoryTable(name, price, stockin,stockout,stockleft) "
                     "VALUES (?, ?, ?,?,?)");
       query.addBindValue(item.name.toLower());
       query.addBindValue(item.price);
       query.addBindValue(item.stockin);
       query.addBindValue(item.stockout);
       query.addBindValue(item.stockLeft);
       query.exec();
       inventoryModel->append(item);
  }



   //while(query.next())
   //qDebug()<<query.value(0).toString();
}

void MainWindow::initializeInventoryPage()
{
    ui->addInventoryItem->setEnabled(false);
    connect(ui->addInventoryItemEdit,&QLineEdit::textChanged,this,&MainWindow::validateInventoryAddItem);

    QSqlQuery query;
    query.exec("SELECT * FROM inventoryTable");

    InventoryItem item;
    int i = 0;
    //QList<InventoryItem> itemsList = inventoryModel->modelList();
    while (query.next() && i< nameLabels.length()) {
          item.name = query.value(0).toString();
          item.price = query.value(1).toDouble();
          item.stockin = query.value(2).toInt();
          item.stockout = query.value(3).toInt();
          item.stockLeft = query.value(4).toInt();

          inventoryModel->append(item);
      }

}

void MainWindow::validateInventoryAddItem()
{
    QString text  = ui->addInventoryItemEdit->text();
    for(int i = 0; i<text.length();i++){
        if(text.at(i)!= ' ')
             ui->addInventoryItem->setEnabled(true);

        return;
    }
    ui->addInventoryItem->setEnabled(false);
}

void MainWindow::on_updateInventoryItem_clicked()
{
   InventoryItem item;
   item.name = ui->updateItemInventoryEdit->text();
   item.price = ui->updateInventoryPriceSpinBox->value();
   item.stockin = ui->updateInventoryStockinSpinBox->value();
   item.stockout = ui->updateInventoryStockoutSpinBox->value();
   item.stockLeft = item.stockin -  item.stockout;

   QSqlQuery query;
   query.prepare("UPDATE inventoryTable set name=?, price=?, stockin=?,stockout=?, stockleft = ? WHERE name = ?");
   query.addBindValue(item.name.toLower());
   query.addBindValue(item.price);
   query.addBindValue(item.stockin);
   query.addBindValue(item.stockout);
   query.addBindValue(item.stockLeft);
   query.addBindValue(item.name.toLower());
   query.exec();

   if(query.numRowsAffected()<1){
       QMessageBox::critical(nullptr
                             , tr("Update Failed"),
                                       tr("Failed to make changes requested.\n"
                                          "Please make sure the item exists"), QMessageBox::Cancel);
     return;
   }
   QList<InventoryItem> inventoryList = inventoryModel->modelList();

   for(int i= 0; i<inventoryList.length();i++){
       if(inventoryList.at(i).name == item.name){
           inventoryModel->removeRows(i,1);
           inventoryModel->append(item);
           break;
       }
   }

}

void MainWindow::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();

    QList<InventoryItem> inventoryList = inventoryModel->modelList();
    for(int i= 0; i<inventoryList.length();i++){
        if(inventoryList.at(i).name == searchTerm){
            ui->updateItemInventoryEdit->setText(inventoryList.at(i).name);
            ui->updateInventoryPriceSpinBox->setValue(inventoryList.at(i).price);
            ui->updateInventoryStockinSpinBox->setValue(inventoryList.at(i).stockin);
            ui->updateInventoryStockoutSpinBox->setValue(inventoryList.at(i).stockout);
            break;
        }
    }
}

void MainWindow::changePassword(QString ans, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ?");
    query.addBindValue(userName);

    int counter=0;

    query.exec();
    while(query.next())
        counter++;

    if(ans.toLower() == this->answer.toLower()){
        query.prepare("UPDATE users set password = ? WHERE username = ?");
        query.addBindValue(password);
        query.addBindValue(userName);
        query.exec();
    }
    else{
        QMessageBox::critical(nullptr
                              , tr("Operation Failed"),
                                        tr("The answer you provided to the question is incorrect.\n"));
    }
}

void MainWindow::initializeSettingsPage()
{
    ui->firstnameEdit_2->setText(currentUser.firstName);
    ui->lastnameEdit_2->setText(currentUser.lastName);
    ui->addressEdit_2->setText(currentUser.address);
    ui->emailEdit_2->setText(currentUser.email);
    ui->passwordEdit_2->setText(currentUser.password);
    ui->confirmPasswordEdit_2->setText(currentUser.password);
    ui->questionCombo_2->setCurrentText(currentUser.question);
    ui->answerEdit_2->setText(currentUser.answer);

    if(currentUser.accountType == 1/*vendor*/)
        ui->vendorRadioButton_2->setChecked(true);
    else
        ui->managerRadioButton_2->setChecked(true);

}

void MainWindow::on_updateButton_clicked()
{
    QList<QString> list;
    QString message;
    list.append(ui->firstnameEdit_2->text().toLower());
    list.append(ui->lastnameEdit_2->text().toLower());
    list.append(ui->addressEdit_2->text().toLower());
    list.append(ui->emailEdit_2->text().toLower());
    list.append(ui->passwordEdit_2->text());
    list.append(ui->questionCombo_2->currentText().toLower());
    list.append(ui->answerEdit_2->text().toLower());

    int accountType = ui->vendorRadioButton_2->isChecked();
    if(!ui->firstnameEdit_2->text().isEmpty() && !ui->lastnameEdit_2->text().isEmpty() && !ui->addressEdit_2->text().isEmpty() && !ui->emailEdit_2->text().isEmpty() && !ui->passwordEdit_2->text().isEmpty() && !ui->confirmPasswordEdit_2->text().isEmpty() && !ui->answerEdit_2->text().isEmpty()){
        if(ui->passwordEdit_2->text().length()>=6){
            if(ui->passwordEdit_2->text() == ui->confirmPasswordEdit_2->text()){
                qDebug()<<"Performing last check";
                QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
                mailREX.setCaseSensitivity(Qt::CaseInsensitive);
                mailREX.setPatternSyntax(QRegExp::RegExp);
                 if(mailREX.exactMatch(ui->emailEdit_2->text())){
                    QSqlQuery query;
                    query.prepare("DELETE FROM users WHERE username = ?");
                    query.addBindValue(currentUser.username);
                    query.exec();
                    createNewAccount(list,accountType);
                }
                 else{
                     message.prepend("Invalid password.\n");
                 }
            }
            else{
                message.prepend("Password must match confirmed password.\n");
            }
        }
        else{
            message.prepend("Password must be atleast 6 characters long");
        }
    }
    else{
        message.prepend("All Fields are mandatory. Please fill them.\n");
    }

    if(!message.isEmpty())
        QMessageBox::warning(nullptr, tr("Operation failed"),message);
    message.clear();
}
