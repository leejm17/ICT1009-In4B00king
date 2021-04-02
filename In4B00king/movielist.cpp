#include "movielist.h"
#include "ui_mainpage2.h"
#include <QPixmap>
#include <QMessageBox>

MovieList::MovieList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainpage2)
{
    ui->setupUi(this);
    economyHall = new EconomyHall(this);
    diamondHall = new DiamondHall(this);
}

MovieList::~MovieList()
{
    delete ui;
}

void MovieList::on_SelectButton_clicked()
{
    QMessageBox::information(this,"Hi","is_clicked");
    economyHall->show();
    //movieinformation = new MovieInformation(this);
    //movieinformation->show();
}

void MovieList::on_SelectButton_2_clicked()
{
    diamondHall->show();
}
