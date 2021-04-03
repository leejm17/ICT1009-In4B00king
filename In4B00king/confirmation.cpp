#include "confirmation.h"
#include "ui_confirmation.h"
#include "seatselection.h"

Confirmation::Confirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirmation)
{
    ui->setupUi(this);
    SeatSelection *sselection = new SeatSelection;

    connect(sselection,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    sselection->show();
}

Confirmation::~Confirmation()
{
    delete ui;
}

void Confirmation::receiveData(QString data)
{
    ui->userInput->setText(data);
}

