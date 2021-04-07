#include "seatselection.h"
#include "ui_seatselection.h"

SeatSelection::SeatSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeatSelection)
{
    ui->setupUi(this);
}

SeatSelection::~SeatSelection()
{
    delete ui;
}

void SeatSelection::updateSelection(BookingInfo bookingInfo)
{
    ui->sselection->clear();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select seat_num from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=" + QString::number(bookingInfo.get_show_ID()) + " and MovieSeats.available='TRUE' and HallSeats.condition='good'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }

    while(query.next())
    {
        ui->sselection->addItem(query.value(0).toString());
    }

    if(ui->sselection->count()<=0){
        ui->book->setEnabled(false);
    }

}

void SeatSelection::showSeatSelection(BookingInfo bookingInfo)
{
    this->updateSelection(bookingInfo);
    this->bookingInfo = bookingInfo;
    this->show();
}

void SeatSelection::on_book_clicked()
{
    emit showConfirmation(ui->sselection->currentText(), bookingInfo);
}
