#include "changemenuitemdialog.h"
#include "ui_changemenuitemdialog.h"
#include <QFileDialog>

changeMenuItemDialog::changeMenuItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeMenuItemDialog)
{
    ui->setupUi(this);
    ui->discountSpinBox->setEnabled(false);
    ui->priceSpinBox->setEnabled(false);
    ui->pictureEdit->setEnabled(false);
    ui->selecFileButton->setEnabled(false);

    ui->nameEdit_2->setText(ui->nameEdit->text());
    ui->priceSpinBox_2->setValue(ui->priceSpinBox->value());
    ui->discountSpinBox_2->setValue(ui->discountSpinBox->value());
    ui->pictureEdit_2->setText(ui->pictureEdit->text());

    ui->okButton->setEnabled(false);
    connect(ui->nameEdit_2,&QLineEdit::textChanged,this,&changeMenuItemDialog::validateData);
    connect(ui->nameEdit,&QLineEdit::textChanged,this,&changeMenuItemDialog::nameChanged);

    //setWindowTitle("Kenkey Boutique");
    setWindowIcon(QIcon(":/windowIcon.png"));
}
void changeMenuItemDialog::validateData()
{
    QString str = ui->nameEdit_2->text();

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



QString changeMenuItemDialog::name()
{
    return ui->nameEdit->text();
}
QString changeMenuItemDialog::newName()
{
    return ui->nameEdit_2->text();
}

double changeMenuItemDialog::newPrice()
{
    return ui->priceSpinBox_2->value();
}

double changeMenuItemDialog::newDiscount()
{
    return ui->discountSpinBox_2->value();
}

QString changeMenuItemDialog::newPicture()
{
    return ui->pictureEdit_2->text();
}

changeMenuItemDialog::~changeMenuItemDialog()
{
    delete ui;
}

void changeMenuItemDialog::on_selecFileButton_2_clicked()
{
    //select the new file name for the picture
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Select Image"), "C:\\Users\\HP\\Desktop\\Projects\\Kenkey_Boutique\\Resources", tr("Image Files (*.png *.jpg *.jpeg)"));
    ui->pictureEdit_2->setText(fileName);
}

void changeMenuItemDialog::on_okButton_clicked()
{
    //ok button clicked

    this->accept();
}

void changeMenuItemDialog::on_cancelButton_clicked()
{
    //cancel button clicked

    this->reject();

}
