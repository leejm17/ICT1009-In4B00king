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

void SeatSelection::updateSelection(int show_ID)
{
    this->show_ID=show_ID;
    ui->sselection->clear();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select seat_num from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=" + QString::number(show_ID) + " and MovieSeats.available='TRUE' and HallSeats.condition='good'");

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

void SeatSelection::showSeatSelection(int show_ID)
{
    this->updateSelection(show_ID);
    this->show();
}

void SeatSelection::on_book_clicked()
{
    emit showConfirmation(ui->sselection->currentText(), show_ID);
}
