#include "editmovies.h"
#include "ui_editmovies.h"

editmovies::editmovies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editmovies)
{
    ui->setupUi(this);
}

editmovies::~editmovies()
{
    delete ui;
}
