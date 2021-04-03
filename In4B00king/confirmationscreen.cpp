#include "confirmationscreen.h"
#include "ui_confirmationscreen.h"

ConfirmationScreen::ConfirmationScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationScreen)
{
    ui->setupUi(this);
}

ConfirmationScreen::~ConfirmationScreen()
{
    delete ui;
}

void ConfirmationScreen::receiveData(QString data)
{
   ui->seat->setText(data);
}
