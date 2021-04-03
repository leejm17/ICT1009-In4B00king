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

signals:
    void updateSeats();

private slots:

    void on_SelectButton_clicked();

    void on_SelectButton_2_clicked();

private:
    Ui::MovieList *ui;
    EconomyHall *economyHall;
    DiamondHall *diamondHall;
    SeatSelection *seatSelection;
    ConfirmationScreen *confirmationScreen;
};

#endif // MAINPAGE_H
