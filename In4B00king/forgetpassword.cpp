#include "forgetpassword.h"
#include "ui_forgetpassword.h"

forgetpassword::forgetpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
}

forgetpassword::~forgetpassword()
{
    delete ui;
}
