#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include <QMessageBox>

changePasswordDialog::changePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePasswordDialog)
{
    ui->setupUi(this);

    //
    setWindowTitle("Kenkey Boutique");
    setWindowIcon(QIcon(":/windowIcon.png"));
}

void changePasswordDialog::setQuestion(QString question)
{
    ui->questionEdit->setText(question);
}

changePasswordDialog::~changePasswordDialog()
{
    delete ui;
}

void changePasswordDialog::on_submitButton_clicked()
{
    QString message;
    if(ui->passwordEdit->text().length()>=6){
        if(ui->confirmPasswordEdit->text() == ui->passwordEdit->text()){
            emit submitted(ui->answerEdit->text(),ui->passwordEdit->text());
            return;
        }
        else{
            message.append("Password and confirmed password must be the same\n");
        }
    }
    else{
        message.prepend("Password must be atleast six characters\n");
    }

    QMessageBox::warning(nullptr, tr("Operation Failed"),
                                             message);
}
