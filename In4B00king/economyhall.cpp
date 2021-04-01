#include "economyhall.h"
#include "ui_economyhall.h"

EconomyHall::EconomyHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EconomyHall)
{
    ui->setupUi(this);
}

EconomyHall::~EconomyHall()
{
    delete ui;
}
