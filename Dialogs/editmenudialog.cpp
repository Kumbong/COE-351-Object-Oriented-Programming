#include "editmenudialog.h"
#include "ui_editmenudialog.h"

#include <QFileDialog>

EditMenuDialog::EditMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMenuDialog)
{
    ui->setupUi(this);
    ui->okButton->setEnabled(false);
    connect(ui->nameEdit,&QLineEdit::textChanged,this,&EditMenuDialog::validateData);

    //setWindowTitle("Kenkey Boutique");
    setWindowIcon(QIcon(":/windowIcon.png"));
}

void EditMenuDialog::disableSections()
{
    ui->discountSpinBox->setEnabled(false);
    ui->priceSpinBox->setEnabled(false);
    ui->pictureEdit->setEnabled(false);
    ui->selecFileButton->setEnabled(false);
}

QString EditMenuDialog::name()
{
    return ui->nameEdit->text();
}

double EditMenuDialog::price()
{
    return ui->priceSpinBox->value();
}

double EditMenuDialog::discount()
{
    return ui->discountSpinBox->value();
}

QString EditMenuDialog::picture()
{
    return ui->pictureEdit->text();
}

void EditMenuDialog::validateData()
{
    QString str = ui->nameEdit->text();

    if(str.isEmpty() || str.isNull())
         ui->okButton->setEnabled(false);
    else
        ui->okButton->setEnabled(true);

    bool onlySpaces = true;
    for(int i = 0; i<str.length();i++){
        if(str.at(i) != ' ')
            onlySpaces = false;
    }

    if(onlySpaces)
        ui->okButton->setEnabled(false);
    else
        ui->okButton->setEnabled(true);

}

EditMenuDialog::~EditMenuDialog()
{
    delete ui;
}

void EditMenuDialog::on_okButton_clicked()
{
    this->accept();
}

void EditMenuDialog::on_cancelButton_clicked()
{
    this->reject();
}

void EditMenuDialog::on_selecFileButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Select Image"), "C:\\Users\\HP\\Desktop\\Projects\\Kenkey_Boutique\\Resources", tr("Image Files (*.png *.jpg *.jpeg)"));
    ui->pictureEdit->setText(fileName);
}
