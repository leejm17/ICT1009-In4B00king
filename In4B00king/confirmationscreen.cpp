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

void ConfirmationScreen::showConfirmation(QString seat, BookingInfo bookingInfo)
{
    this->bookingInfo = bookingInfo;
    ui->seat->setText(seat);
    ui->hall->setText(bookingInfo.get_hall_Type());
    this->show();
}

void ConfirmationScreen::on_confirm_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update MovieSeats set available='FALSE' where seat_ID=(select MovieSeats.seat_ID from MovieSeats inner join HallSeats on MovieSeats.seat_ID=HallSeats.seat_ID where HallSeats.seat_num='"+ui->seat->text()+"' and MovieSeats.show_ID='"+QString::number(bookingInfo.get_show_ID())+"')");

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

    if(bookingInfo.get_hall_Type().compare("economy") == 0){
        emit updateESeats(bookingInfo);
    } else {
    emit updateDSeats(bookingInfo);
       }
}
