#include "economyselection.h"
#include "ui_economyselection.h"

EconomySelection::EconomySelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EconomySelection)
{
    ui->setupUi(this);
}

EconomySelection::~EconomySelection()
{
    delete ui;
}
