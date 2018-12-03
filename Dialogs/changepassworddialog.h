#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class changePasswordDialog;
}

class changePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changePasswordDialog(QWidget *parent = 0);
    void setQuestion(QString question);
    ~changePasswordDialog();

private slots:
    void on_submitButton_clicked();
signals:
    void submitted(QString answer,QString password);
private:
    Ui::changePasswordDialog *ui;
};

#endif // CHANGEPASSWORDDIALOG_H
