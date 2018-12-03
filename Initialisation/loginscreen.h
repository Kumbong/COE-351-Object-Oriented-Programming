#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QMainWindow>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = 0);
    ~LoginScreen();
signals:
    void login(QString,QString);
    void forgotPassword(QString);
    void createAccount();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_usernameEdit_textChanged(const QString &arg1);

    void on_passwordEdit_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::LoginScreen *ui;
};

#endif // LOGINSCREEN_H
