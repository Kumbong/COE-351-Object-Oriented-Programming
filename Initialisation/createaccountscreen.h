#ifndef CREATEACCOUNTSCREEN_H
#define CREATEACCOUNTSCREEN_H

#include <QMainWindow>
class QCloseEvent;
namespace Ui {
class CreateAccountScreen;
}

class CreateAccountScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateAccountScreen(QWidget *parent = 0);
    ~CreateAccountScreen();
private slots:
    void on_createAccountButton_clicked();
    void fillQuestionComboBox();
    void on_loginButton_clicked();
signals:
    void login();
    void createAccount(QList<QString>,int); //int is for the account type 0 for manager 1 for vendor
private:
    void closeEvent(QCloseEvent *event) override;
    bool proceedToCancel();
private:
    Ui::CreateAccountScreen *ui;
};

#endif // CREATEACCOUNTSCREEN_H
