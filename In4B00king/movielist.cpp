#include "movielist.h"
#include "ui_movielist.h"
#include "editprofile.h"
#include "user.h"
#include "movies.h"
#include <QPixmap>
#include <QMessageBox>

MovieList::MovieList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MovieList)
{
    ui->setupUi(this);
    economyHall = new EconomyHall(this);
    diamondHall = new DiamondHall(this);
    seatSelection = new SeatSelection(this);
    confirmationScreen = new ConfirmationScreen(this);

    connect(economyHall,SIGNAL(showSeatSelection(BookingInfo)),seatSelection,SLOT(showSeatSelection(BookingInfo)));
    connect(diamondHall,SIGNAL(showSeatSelection(BookingInfo)),seatSelection,SLOT(showSeatSelection(BookingInfo)));
    connect(seatSelection,SIGNAL(showConfirmation(QString,BookingInfo)),confirmationScreen,SLOT(showConfirmation(QString,BookingInfo)));
    connect(confirmationScreen,SIGNAL(updateESeats(BookingInfo)),economyHall,SLOT(updateESeats(BookingInfo)));
    connect(confirmationScreen,SIGNAL(updateDSeats(BookingInfo)),diamondHall,SLOT(updateDSeats(BookingInfo)));

    currentOffset = 0;
    updateUI();



}

MovieList::~MovieList()
{
    delete ui;
}

void MovieList::receiveData(user newuser){
    this->newuser = newuser;
    QString labelText = "<P><b><i><font color='#ffffff' font_size=12>";
    labelText.append("Hello " + newuser.getEmail());
    labelText.append("</font></i></b></P></br>");
    ui->profile->setText(labelText);
    if (newuser.getType() == "customer"){
        ui->editmovie->setVisible(false);
    }else{
        ui->Edit_Profile->setVisible(false);
    }

    if (newuser.getType() == "customer"){
        customer newcustomer(newuser.getEmail());
        this->newcustomer = newcustomer;

    }else{
        administrator newadmin(newuser.getEmail());
        this->newadmin = newadmin;
    }

}

void MovieList::updateUI()
{
    // bindings to movie labels
    Movie movie0;       // Movie is a struct defined in movielist.h
    movie0.title = ui->Movie_Title_1;
    movie0.duration = ui->Duration_1;

    Movie movie1;
    movie1.title = ui->Movie_Title_2;
    movie1.duration = ui->Duration_2;

    Movie movie2;
    movie2.title = ui->Movie_Title_3;
    movie2.duration = ui->Duration_3;

    movies[0] = movie0;
    movies[1] = movie1;
    movies[2] = movie2;

    // styling and displaying of movie title and duration
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);

    movies[0].title->setPalette(sample_palette);
    movies[0].duration->setPalette(sample_palette);

    movies[1].title->setPalette(sample_palette);
    movies[1].duration->setPalette(sample_palette);

    movies[2].title->setPalette(sample_palette);
    movies[2].duration->setPalette(sample_palette);

    MovieListInfo().displayMovieList(movies);   // movies is a struct array

    QPixmap pix(":/resources/img/" + movies[0].title->text().replace(" ", "_") + ".jpg");
    ui->Movie1->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    QPixmap pix2(":/resources/img/" + movies[1].title->text().replace(" ", "_") + ".jpg");
    ui->Movie2->setPixmap(pix2.scaled(221,300,Qt::KeepAspectRatio));
    QPixmap pix3(":/resources/img/" + movies[2].title->text().replace(" ", "_") + ".jpg");
    ui->Movie3->setPixmap(pix3.scaled(221,300,Qt::KeepAspectRatio));

}



void MovieList::on_Next_Button_clicked()
{
    currentOffset++;
    updateUI();
}

void MovieList::on_Select_Button1_clicked()
{
    movieInfoWindow = new MovieInformation(this);
    hide();
    movieInfoWindow->show();

    MovieInfo movieInfo(movies[0].title->text(), movies[0].duration->text().split(" ").at(0).toInt());
    movieInfo.getMovieDetails_Db(); // get details of the selected movie

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(BookingInfo)),economyHall,SLOT(updateESeats(BookingInfo)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(BookingInfo)),diamondHall,SLOT(updateDSeats(BookingInfo)));
    emit sendMovieData(movieInfo);
}

void MovieList::on_Edit_Profile_clicked()
{
    profilepage = new editprofile();
    profilepage->show();
    connect(this, SIGNAL(sendData(customer)), profilepage, SLOT(receiveData(customer)));
    emit sendData(newcustomer);

}

void MovieList::on_logout_clicked()
{
    close();
}

void MovieList::on_editmovie_clicked()
{  
    editmoviespage = new editmovies();
    editmoviespage->show();
    QString privilegelvl = (QString::number(newadmin.getpriv()));
    connect(this, SIGNAL(sendData2(QString)), editmoviespage, SLOT(receiveData(QString)));
    emit sendData2(privilegelvl);
}

void MovieList::on_Select_Button2_clicked()
{
    movieInfoWindow = new MovieInformation(this);
    hide();
    movieInfoWindow->show();

    MovieInfo movieInfo(movies[1].title->text(), movies[1].duration->text().split(" ").at(0).toInt());
    movieInfo.getMovieDetails_Db(); // get details of the selected movie

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(BookingInfo)),economyHall,SLOT(updateESeats(BookingInfo)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(BookingInfo)),diamondHall,SLOT(updateDSeats(BookingInfo)));
    emit sendMovieData(movieInfo);
}

void MovieList::on_Select_Button3_clicked()
{
    movieInfoWindow = new MovieInformation(this);
    hide();
    movieInfoWindow->show();

    MovieInfo movieInfo(movies[2].title->text(), movies[2].duration->text().split(" ").at(0).toInt());
    movieInfo.getMovieDetails_Db(); // get details of the selected movie

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(BookingInfo)),economyHall,SLOT(updateESeats(BookingInfo)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(BookingInfo)),diamondHall,SLOT(updateDSeats(BookingInfo)));
    emit sendMovieData(movieInfo);
}
