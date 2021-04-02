#include "economyhall.h"
#include "ui_economyhall.h"

EconomyHall::EconomyHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EconomyHall)
{
    ui->setupUi(this);
    economySelection = new EconomySelection(this);
}

EconomyHall::~EconomyHall()
{
    delete ui;
}

void EconomyHall::on_book_clicked()
{
    economySelection->updateSelection();
    economySelection->show();
}
