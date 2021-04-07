#include "movieinformation.h"
#include "ui_movieinformation.h"

MovieInformation::MovieInformation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MovieInformation)
{
    ui->setupUi(this);
}

MovieInformation::~MovieInformation()
{
    delete ui;
}

void MovieInformation::receiveData(MovieInfo movieInfo)
{
    QString isMins;
    if (movieInfo.getDuration() > 0)
    {
        isMins = QString::number(movieInfo.getDuration()) + QString(" mins");
    }
    else
    {
        isMins = QString("TBA");
    }

    QPixmap pix(":/resources/img/" + movieInfo.getName().replace(" ", "_") + ".jpg");
    ui->Movie->setPixmap(pix.scaled(351,525,Qt::KeepAspectRatio));

    ui->Title->setText(movieInfo.getName());
    ui->Date->setText(movieInfo.getDebut());
    ui->Time->setText(isMins);
    ui->Description->setText(movieInfo.getDesc());
    this->MovieID = movieInfo.getMovieID();
    // fetch from db dates and time
    ShowtimesInfo().displayMovieDetails(movieInfo.getName(), ui->DropdownDate);
}

void MovieInformation::on_Back_clicked()
{
    hide();
    parentWidget()->show();

}

void MovieInformation::on_SelectSeats_clicked()
{
    QString selection = ui->DropdownDate->currentText();
    QString selectedTime = selection.split(" ").at(2);
    QString selectedDate = selection.split(" ").at(1);
    QString selectedHall = selection.split(" ").at(0);

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select MovieShowing.show_ID,Halls.type from Halls inner join MovieShowing on Halls.hall_ID=MovieShowing.hall_ID where MovieShowing.movie_ID=" + QString::number(this->MovieID) +" and MovieShowing.date='" + selectedDate + "' and MovieShowing.timeslot='" + selectedTime + "' and MovieShowing.hall_ID='"+ selectedHall+"'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        QMessageBox::warning(this,"Error",query.lastError().text());
    }
    while(query.next())
    {
        BookingInfo bookingInfo(query.value(0).toInt(), selectedDate, selectedTime, query.value(1).toString());
            if(query.value(1).toString().compare("economy") == 0){
            emit updateESeats(bookingInfo);
            } else {
                emit updateDSeats(bookingInfo);
            }
    }
}
