#ifndef EDITMENUDIALOG_H
#define EDITMENUDIALOG_H

#include <QDialog>

namespace Ui {
class EditMenuDialog;
}

class EditMenuDialog : public QDialog
{
    Q_OBJECT

public:

    explicit EditMenuDialog(QWidget *parent = 0);
    void disableSections();
    QString name();
    double price();
    double discount();
    QString picture();


    ~EditMenuDialog();

private slots:
    void on_okButton_clicked();
        void validateData();

    void on_cancelButton_clicked();

    void on_selecFileButton_clicked();

private:
    Ui::EditMenuDialog *ui;
};

#endif // EDITMENUDIALOG_H
