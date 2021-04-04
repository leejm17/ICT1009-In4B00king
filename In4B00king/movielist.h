#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <QMainWindow>
#include "movieinformation.h"
#include "economyhall.h"
#include "diamondhall.h"
#include "seatselection.h"
#include "confirmationscreen.h"

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

    void receiveData(QStringList);

private:
    Ui::MovieList *ui;
    EconomyHall *economyHall;
    DiamondHall *diamondHall;
    SeatSelection *seatSelection;
    ConfirmationScreen *confirmationScreen;
	int currentOffset;
    QSqlDatabase db;
};

#endif // MAINPAGE_H
