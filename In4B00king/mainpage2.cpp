#include "mainpage2.h"
#include "ui_mainpage2.h"
#include <QPixmap>
#include <QMessageBox>

Mainpage2::Mainpage2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainpage2)
{
    ui->setupUi(this);
    economyHall = new EconomyHall(this);
    diamondHall = new DiamondHall(this);
}

Mainpage2::~Mainpage2()
{
    delete ui;
}

void Mainpage2::on_SelectButton_clicked()
{
    QMessageBox::information(this,"Hi","is_clicked");
    economyHall->show();
    //movieinformation = new MovieInformation(this);
    //movieinformation->show();
}

void Mainpage2::on_SelectButton_2_clicked()
{
    diamondHall->show();
}
