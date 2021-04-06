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
    QString selectedTime = selection.split(" ").at(0);
    QString selectedDate = selection.split(" ").at(1);
    qDebug() << "Time is " << selectedTime;
    qDebug() << "Date is " << selectedDate;
}
