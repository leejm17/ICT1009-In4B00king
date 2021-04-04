#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <QMainWindow>
#include "movieinformation.h"
#include "economyhall.h"
#include "diamondhall.h"
#include "seatselection.h"
#include "confirmationscreen.h"
#include "user.h"
#include "editprofile.h"
#include "editmovies.h"

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
    void sendData(user);

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

private:
    Ui::MovieList *ui;
    EconomyHall *economyHall;
    DiamondHall *diamondHall;
    SeatSelection *seatSelection;
    ConfirmationScreen *confirmationScreen;
	int currentOffset;
    QSqlDatabase db;
    user newuser;
    editprofile *profilepage;
    editmovies *moviespage;

};

#endif // MAINPAGE_H
