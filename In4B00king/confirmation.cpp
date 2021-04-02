#include "confirmation.h"
#include "ui_confirmation.h"
#include "seatselection.h"

confirmation::confirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmation)
{
    ui->setupUi(this);
}

confirmation::~confirmation()
{
    delete ui;
}

void confirmation::showReceiveForm()
{
    qDebug() << "TEST2";
}
