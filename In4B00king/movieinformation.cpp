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
}

void MovieInformation::on_Back_clicked()
{
    hide();
    parentWidget()->show();

}
