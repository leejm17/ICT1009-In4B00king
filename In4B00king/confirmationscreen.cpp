#include "confirmationscreen.h"
#include "ui_confirmationscreen.h"
#include <QMessageBox>

ConfirmationScreen::ConfirmationScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationScreen)
{
    ui->setupUi(this);
}

ConfirmationScreen::~ConfirmationScreen()
{
    delete ui;
}

void ConfirmationScreen::showConfirmation(QString seat)
{
    ui->seat->setText(seat);
    this->show();
}

void ConfirmationScreen::on_confirm_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update MovieSeats set MovieSeats.available='FALSE' where exists (select null from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where seat_num='"+ui->seat->text()+"' and MovieSeats.show_ID=1 and MovieSeats.available='TRUE' and HallSeats.condition='good')");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        QMessageBox::warning(this,"Error",query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            qDebug() << "update was successful "<< query.lastQuery();
        }
        else
        {
            QMessageBox::warning(this,"Error","Unable to update seating");
        }
       }

    emit updateSeats();
}
