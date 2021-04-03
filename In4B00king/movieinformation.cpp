#include "movieinformation.h"
#include "ui_movieinformation.h"

MovieInformation::MovieInformation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MovieInformation)
{
    ui->setupUi(this);
}

MovieInformation::~MovieInformation()
{
    delete ui;
}
