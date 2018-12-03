#include "loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    /*setStyleSheet(QString("QPushButton {"
                          "border: 2px solid #8f8f91;"
                          "border-radius: 6px;"
                          "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                           "stop: 0 #f6f7fa, stop: 1 #dadbde);"
                      "} QLineEdit {border-radius: 6px;}"));*/
    //connect(ui->loginButton,&QPushButton::clicked,this,&LoginScreen::login);
    //connect(ui->createAccountButton,&QPushButton::clicked,this,&LoginScreen::createAccount);
    setWindowTitle("Kenkey Boutique");
    setWindowIcon(QIcon(":/windowIcon.png"));
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_pushButton_clicked()
{
    //on login button clicked
    QString username = ui->usernameEdit->text().toLower();
    QString password = ui->passwordEdit->text();

    emit login(username,password);
}

void LoginScreen::on_pushButton_2_clicked()
{
    //on create account button clicked
    emit createAccount();

}

void LoginScreen::on_usernameEdit_textChanged(const QString &arg1)
{
    if(ui->usernameEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty())
        ui->pushButton->setEnabled(false);
    else
        ui->pushButton->setEnabled(true);
}

void LoginScreen::on_passwordEdit_textChanged(const QString &arg1)
{
    if(ui->usernameEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty())
        ui->pushButton->setEnabled(false);
    else
        ui->pushButton->setEnabled(true);
}

void LoginScreen::on_pushButton_3_clicked()
{
    //on forgot password button clicked
    emit forgotPassword(ui->usernameEdit->text());
}
