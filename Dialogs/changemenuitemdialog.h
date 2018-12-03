#ifndef CHANGEMENUITEMDIALOG_H
#define CHANGEMENUITEMDIALOG_H

#include <QDialog>

namespace Ui {
class changeMenuItemDialog;
}

class changeMenuItemDialog : public QDialog
{
    Q_OBJECT

public slots:
    void validateData();
public:
    QString name();
    QString newName();
    QString newPicture();
    double newDiscount();
    double newPrice();
    explicit changeMenuItemDialog(QWidget *parent = 0);
    ~changeMenuItemDialog();
signals:
    nameChanged();
private slots:
    void on_selecFileButton_2_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::changeMenuItemDialog *ui;
};

#endif // CHANGEMENUITEMDIALOG_H
