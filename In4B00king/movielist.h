#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <QMainWindow>
#include <QLabel>
#include "movieinformation.h"
#include "economyhall.h"
#include "diamondhall.h"
#include "seatselection.h"
#include "confirmationscreen.h"
#include "user.h"
#include "editprofile.h"
#include "editmovies.h"
#include "movies.h"

/* Forward declaration for friend-function. */
class MovieListInfo;    // found in movies.h


namespace Ui {
class MovieList;
}

class MovieList : public QMainWindow
{
    Q_OBJECT

public:
    explicit MovieList(QWidget *parent = nullptr);
    ~MovieList();
	void updateUI();

signals:
    void updateSeats();
    void sendData(customer);
    void sendMovieData(MovieInfo);
    void sendData2(QString);

private slots:

    void on_SelectButton_clicked();

    void on_SelectButton_2_clicked();
	
	void on_Next_Button_clicked();


    /**
    void on_Select_Button_clicked();

    void on_SelectButton_2_clicked();

    void on_Next_Button_clicked();
    **/


    void on_Select_Button1_clicked();

    void on_Edit_Profile_clicked();

    void receiveData(user);



    void on_logout_clicked();

    void on_editmovie_clicked();

    void on_Select_Button2_clicked();

    void on_Select_Button3_clicked();

private:
    Ui::MovieList *ui;
    EconomyHall *economyHall;
    DiamondHall *diamondHall;
    SeatSelection *seatSelection;
    ConfirmationScreen *confirmationScreen;
	int currentOffset;
    QSqlDatabase db;
    editprofile *profilepage;
    editmovies *moviespage;
    editmovies *editmoviespage;
    MovieInformation *movieInfoWindow;
    user newuser;
    administrator newadmin;
    customer newcustomer;

    Movie movies[3];
};

#endif // MAINPAGE_H

