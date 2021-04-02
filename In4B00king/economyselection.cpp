#include "economyselection.h"
#include "ui_economyselection.h"

EconomySelection::EconomySelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EconomySelection)
{
    ui->setupUi(this);
}

EconomySelection::~EconomySelection()
{
    delete ui;
}

void EconomySelection::updateSelection()
{
    ui->sselection->clear();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select seat_num from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=1 and MovieSeats.available='TRUE' and HallSeats.condition='good'");

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
