#include "diamondhall.h"
#include "ui_diamondhall.h"

DiamondHall::DiamondHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiamondHall)
{
    ui->setupUi(this);
    seatSelection = new SeatSelection(this);

    updateSeats();
}

DiamondHall::~DiamondHall()
{
    delete ui;
}

void DiamondHall::updateSeats()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select HallSeats.seat_num,MovieSeats.available,HallSeats.condition from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=1");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }

    while(query.next())
    {
        QString sLabel = "s" + query.value(0).toString().toLower();
        QLabel *sptr = this->findChild<QLabel*>(sLabel);
        if(sptr!=nullptr)
        {
            if(query.value(1).toString().compare("TRUE") == 0 && query.value(2).toString().compare("good") == 0)
            {
                sptr->setStyleSheet("QLabel { background-color : green; }");
            } else {
                sptr->setStyleSheet("QLabel { background-color : red; }");
            }
        }
    }
}
void DiamondHall::on_book_clicked()
{
    seatSelection->updateSelection();
    seatSelection->show();
}
