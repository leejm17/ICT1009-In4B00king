#include "mainpage.h"
#include "ui_mainpage.h"

Mainpage::Mainpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainpage)
{
    ui->setupUi(this);
}

Mainpage::~Mainpage()
{
    delete ui;
}
