#include "diamondhall.h"
#include "ui_diamondhall.h"

DiamondHall::DiamondHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiamondHall)
{
    ui->setupUi(this);
}

DiamondHall::~DiamondHall()
{
    delete ui;
}

void DiamondHall::updateSeats(BookingInfo bookingInfo)
{
    this->bookingInfo = bookingInfo;
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select HallSeats.seat_num,MovieSeats.available,HallSeats.condition,HallSeats.type from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=" + QString::number(bookingInfo.get_show_ID()));

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
            if(query.value(1).toString().compare("TRUE") == 0 && query.value(2).toString().compare("good") == 0 && query.value(3).toString().compare("handicap") == 0)
            {
                sptr->setStyleSheet("QLabel { background-color : blue; }");
            }else if(query.value(1).toString().compare("TRUE") == 0 && query.value(2).toString().compare("good") == 0){
                sptr->setStyleSheet("QLabel { background-color : green; }");
            }else {
                sptr->setStyleSheet("QLabel { background-color : red; }");
            }
        }
    }
}

void DiamondHall::updateDSeats(BookingInfo bookingInfo)
{
    this->updateSeats(bookingInfo);
    this->show();
}

void DiamondHall::on_book_clicked()
{
    emit showSeatSelection(bookingInfo);
}
