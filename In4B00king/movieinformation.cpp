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

//    QPixmap pix(":/resources/img/Tom_and_Jerry.jpg");
//    ui->Movie->setPixmap(pix.scaled(361,525,Qt::KeepAspectRatio));

    QImage img1(":/resources/img/Tom_and_Jerry.jpg");
    QImage img2(":/Chaos_Walking.png");
    QImage img3(":/resources/img/Godzilla_Vs_Kong.jpg");

    QVector<QImage> img_array;
    img_array.push_back(img1);
    img_array.push_back(img2);
    img_array.push_back(img3);

    QPixmap pix(":/resources/img/" + movieInfo.getMovieName().replace(" ", "_") + ".jpg");
    ui->Movie->setPixmap(pix.scaled(351,525,Qt::KeepAspectRatio));
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
    if (selection.split(" ").size() == 3)
    {
        QString selectedHall = selection.split(" ").at(0);
        QString selectedTime = selection.split(" ").at(1);
        QString selectedDate = selection.split(" ").at(2);
        qDebug() << "Hall is " << selectedHall;
        qDebug() << "Time is " << selectedTime;
        qDebug() << "Date is " << selectedDate;
    }

}
