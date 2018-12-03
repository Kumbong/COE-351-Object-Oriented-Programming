#include "createaccountscreen.h"
#include "ui_createaccountscreen.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QtDebug>
#include <QRegExp>

CreateAccountScreen::CreateAccountScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateAccountScreen)
{
    ui->setupUi(this);
    fillQuestionComboBox();
    setWindowTitle("Kenkey Boutique");
    setWindowIcon(QIcon(":/windowIcon.png"));

}

CreateAccountScreen::~CreateAccountScreen()
{
    delete ui;
}
bool CreateAccountScreen::proceedToCancel(){

}
void CreateAccountScreen::closeEvent(QCloseEvent* event){


    event->accept();
}

void CreateAccountScreen::on_createAccountButton_clicked()
{
    QList<QString> list;
    QString message;
    list.append(ui->firstnameEdit->text().toLower());
    list.append(ui->lastnameEdit->text().toLower());
    list.append(ui->addressEdit->text().toLower());
    list.append(ui->emailEdit->text().toLower());
    list.append(ui->passwordEdit->text());
    list.append(ui->questionCombo->currentText().toLower());
    list.append(ui->answerEdit->text().toLower());

    int accountType = ui->vendorRadioButton->isChecked();
    if(!ui->firstnameEdit->text().isEmpty() && !ui->lastnameEdit->text().isEmpty() && !ui->addressEdit->text().isEmpty() && !ui->emailEdit->text().isEmpty() && !ui->passwordEdit->text().isEmpty() && !ui->confirmPasswordEdit->text().isEmpty() && !ui->answerEdit->text().isEmpty()){
        if(ui->passwordEdit->text().length()>=6){
            if(ui->passwordEdit->text() == ui->confirmPasswordEdit->text()){
                qDebug()<<"Performing last check";
                QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
                mailREX.setCaseSensitivity(Qt::CaseInsensitive);
                mailREX.setPatternSyntax(QRegExp::RegExp);
                 if(mailREX.exactMatch(ui->emailEdit->text())){
                     createAccount(list,accountType);
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

void CreateAccountScreen::fillQuestionComboBox()
{
    ui->questionCombo->addItem("Which phone number do you remember most from your childhood?");
    ui->questionCombo->addItem("What was your favorite place to visit as a child?");
    ui->questionCombo->addItem("Who is your favorite actor, musician, or artist?");
    ui->questionCombo->addItem("What is the name of your favorite pet?");
    ui->questionCombo->addItem("what is your favorite social media website");
    ui->questionCombo->addItem("what is your favorite online platform");
    ui->questionCombo->addItem("what is your favorite forum");
    ui->questionCombo->addItem("what is your favorite website");
    ui->questionCombo->addItem("Which is your favorite web browser?");
    ui->questionCombo->addItem("What was your high school mascot?");
    ui->questionCombo->addItem("What is the name of your first grade teacher?");
    ui->questionCombo->addItem("What is your father's middle name?");
    ui->questionCombo->addItem("What is your favorite color?");
    ui->questionCombo->addItem("When is your anniversary?");
    ui->questionCombo->addItem("In what city were you born?");
    ui->questionCombo->addItem("What high school did you attend?");
    ui->questionCombo->addItem("What is the name of your first school?");
    ui->questionCombo->addItem("What is your favorite movie?");
    ui->questionCombo->addItem("What is your mother's maiden name?");
    ui->questionCombo->addItem("What street did you grow up on?");
    ui->questionCombo->addItem("What was the make of your first car?");

}

void CreateAccountScreen::on_loginButton_clicked()
{
    emit login();
}
