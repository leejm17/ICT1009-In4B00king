#include "economyhall.h"
#include "ui_economyhall.h"

EconomyHall::EconomyHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EconomyHall)
{
    ui->setupUi(this);

    updateSeats();
}

EconomyHall::~EconomyHall()
{
    delete ui;
}

void EconomyHall::updateSeats()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select HallSeats.seat_num,MovieSeats.available,HallSeats.condition,HallSeats.type from HallSeats inner join MovieSeats on HallSeats.seat_ID=MovieSeats.seat_ID where MovieSeats.show_ID=1");

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
            if(query.value(1).toString().compare("TRUE") == 0 && query.value(2).toString().compare("good") == 0 && query.value(3).toString().compare("disabled") == 0)
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

void EconomyHall::on_book_clicked()
{   
    emit showSeatSelection();
}

void EconomyHall::closeEvent(QCloseEvent *event){
    emit closeAll();
}
