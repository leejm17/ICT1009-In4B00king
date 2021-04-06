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

    connect(economyHall,SIGNAL(showSeatSelection(int)),seatSelection,SLOT(showSeatSelection(int)));
    connect(diamondHall,SIGNAL(showSeatSelection(int)),seatSelection,SLOT(showSeatSelection(int)));
    connect(seatSelection,SIGNAL(showConfirmation(QString,int)),confirmationScreen,SLOT(showConfirmation(QString,int)));
    connect(confirmationScreen,SIGNAL(updateSeats()),economyHall,SLOT(updateSeats()));
    connect(confirmationScreen,SIGNAL(updateSeats()),diamondHall,SLOT(updateSeats()));

    //Close all windows
    /*connect(economyHall,SIGNAL(closeAll()),seatSelection,SLOT(close()));
    connect(economyHall,SIGNAL(closeAll()),confirmationScreen,SLOT(close()));
    connect(diamondHall,SIGNAL(closeAll()),seatSelection,SLOT(close()));
    connect(diamondHall,SIGNAL(closeAll()),confirmationScreen,SLOT(close()));

    connect(confirmationScreen,SIGNAL(closeAll()),seatSelection,SLOT(close()));*/

    //db = MyDB::getInstance()->getDBInstance();

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
    labelText.append("Hello " + newuser.getName());
    labelText.append("</font></i></b></P></br>");
    ui->profile->setText(labelText);
    if (newuser.getType() == "customer"){
        ui->editmovie->setVisible(false);
    }else{
        ui->Edit_Profile->setVisible(false);
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

    // styling
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::white);

    movies[0].title->setPalette(sample_palette);
    movies[0].duration->setPalette(sample_palette);

    movies[1].title->setPalette(sample_palette);
    movies[1].duration->setPalette(sample_palette);

    movies[2].title->setPalette(sample_palette);
    movies[2].duration->setPalette(sample_palette);

    qDebug() << "currentOffset: " << currentOffset;

/**    QSqlQuery query(db);
    query.prepare("SELECT name, duration FROM MovieList LIMIT 3 OFFSET " + QString(std::to_string(3*currentOffset).c_str()));
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
    }
    else
    {
        int currentIndex = 0;
        while (query.next())
        {
            movies[currentIndex].title->setText(query.value(0).toString());
            auto duration = query.value(1).toString();
            if (duration !=  QString("TBA"))
            {
                duration += QString(" mins");
            }

            movies[currentIndex].duration->setText(duration);

            currentIndex++;

            qDebug() << "title: " << query.value(0).toString().toUtf8().constData();
            qDebug() << " duration : " << query.value(1).toString().toUtf8().constData();
        }
    }
    query.finish();**/

    MovieListInfo().displayMovieList(movies);   // movies is a struct array
    qDebug() << "hi2";

 QPixmap pix(":/resources/img/" + movies[0].title->text().replace(" ", "_") + ".jpg");
 ui->Movie1->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
 QPixmap pix2(":/resources/img/" + movies[1].title->text().replace(" ", "_") + ".jpg");
    ui->Movie2->setPixmap(pix2.scaled(221,300,Qt::KeepAspectRatio));
    QPixmap pix3(":/resources/img/" + movies[2].title->text().replace(" ", "_") + ".jpg");
    ui->Movie3->setPixmap(pix3.scaled(221,300,Qt::KeepAspectRatio));
    /**


    setText("FF9");
    ui->Duration_1->setText("120min");

    ui->Movie2->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    ui->Movie_Title_2->setText("FF9");
    ui->Duration_2->setText("120min");

    ui->Movie3->setPixmap(pix.scaled(221,300,Qt::KeepAspectRatio));
    ui->Movie_Title_3->setText("FF9");
    ui->Duration_3->setText("120min");
    **/
    qDebug() << "hi";
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

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(QString,QString,int)),economyHall,SLOT(updateSeats(QString,QString,int)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(QString,QString,int)),diamondHall,SLOT(updateSeats(QString,QString,int)));
    emit sendMovieData(movieInfo);
}

void MovieList::on_Edit_Profile_clicked()
{
    profilepage = new editprofile();
    profilepage->show();
    connect(this, SIGNAL(sendData(user)), profilepage, SLOT(receiveData(user)));
    QString email = newuser.getEmail();
    newuser.GetUserVariables(email);
    emit sendData(newuser);
}

void MovieList::on_logout_clicked()
{
    close();
}

void MovieList::on_editmovie_clicked()
{  
    editmovies editmoviepage;
    editmoviepage.setModal(true);
    editmoviepage.exec();
}

void MovieList::on_Select_Button2_clicked()
{
    movieInfoWindow = new MovieInformation(this);
    hide();
    movieInfoWindow->show();

    MovieInfo movieInfo(movies[1].title->text(), movies[1].duration->text().split(" ").at(0).toInt());

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(QString,QString,int)),economyHall,SLOT(updateSeats(QString,QString,int)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(QString,QString,int)),diamondHall,SLOT(updateSeats(QString,QString,int)));
    emit sendMovieData(movieInfo);
}

void MovieList::on_Select_Button3_clicked()
{
    movieInfoWindow = new MovieInformation(this);
    hide();
    movieInfoWindow->show();

    MovieInfo movieInfo(movies[2].title->text(), movies[2].duration->text().split(" ").at(0).toInt());

    connect(this, SIGNAL(sendMovieData(MovieInfo)), movieInfoWindow, SLOT(receiveData(MovieInfo)));
    connect(movieInfoWindow,SIGNAL(updateESeats(QString,QString,int)),economyHall,SLOT(updateSeats(QString,QString,int)));
    connect(movieInfoWindow,SIGNAL(updateDSeats(QString,QString,int)),diamondHall,SLOT(updateSeats(QString,QString,int)));
    emit sendMovieData(movieInfo);
}
