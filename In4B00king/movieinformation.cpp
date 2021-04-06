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
    if (movieInfo.getMovieDuration() > 0)
    {
        isMins = QString::number(movieInfo.getMovieDuration()) + QString(" mins");
    }
    else
    {
        isMins = QString("TBA");
    }

    ui->Title->setText(movieInfo.getMovieName());
    ui->Date->setText(movieInfo.getMovieDebut());
    ui->Time->setText(isMins);
    ui->Description->setText(movieInfo.getMovieDesc());
    this->MovieID = movieInfo.getMovieID();
    // fetch from db dates and time
    ShowtimesInfo().displayMovieDetails(movieInfo.getMovieName(), ui->DropdownDate);
}

void MovieInformation::on_Back_clicked()
{
    hide();
    parentWidget()->show();

}

void MovieInformation::on_SelectSeats_clicked()
{
    QString selection = ui->DropdownDate->currentText();
    QString selectedTime = selection.split(" ").at(1);
    QString selectedDate = selection.split(" ").at(0);

    qDebug() << this->MovieID;

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select MovieShowing.show_ID from Halls inner join MovieShowing on Halls.hall_ID=MovieShowing.hall_ID where MovieShowing.movie_ID=" + QString::number(this->MovieID) +" and MovieShowing.date='" + selectedDate + "' and MovieShowing.timeslot='" + selectedTime + "' and Halls.type='economy'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        QMessageBox::warning(this,"Error",query.lastError().text());
    }
    query.next();
            /*if( == 0){
            emit updateESeats(selectedTime, selectedDate, query.value(0).toInt());
            } else {
                emit updateDSeats(selectedTime, selectedDate, query.value(0).toInt());
            }*/
}
