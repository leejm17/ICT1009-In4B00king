#include "movielist.h"
#include "ui_movielist.h"
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

    connect(economyHall,SIGNAL(showSeatSelection()),seatSelection,SLOT(showSeatSelection()));
    connect(diamondHall,SIGNAL(showSeatSelection()),seatSelection,SLOT(showSeatSelection()));
    connect(seatSelection,SIGNAL(showConfirmation(QString)),confirmationScreen,SLOT(showConfirmation(QString)));

    connect(confirmationScreen,SIGNAL(updateSeats()),economyHall,SLOT(updateSeats()));
    connect(confirmationScreen,SIGNAL(updateSeats()),diamondHall,SLOT(updateSeats()));

    connect(this,SIGNAL(updateSeats()),economyHall,SLOT(updateSeats()));
    connect(this,SIGNAL(updateSeats()),diamondHall,SLOT(updateSeats()));

    //Close all windows
    connect(economyHall,SIGNAL(closeAll()),seatSelection,SLOT(close()));
    connect(economyHall,SIGNAL(closeAll()),confirmationScreen,SLOT(close()));
    connect(diamondHall,SIGNAL(closeAll()),seatSelection,SLOT(close()));
    connect(diamondHall,SIGNAL(closeAll()),confirmationScreen,SLOT(close()));

    connect(confirmationScreen,SIGNAL(closeAll()),seatSelection,SLOT(close()));
}

MovieList::~MovieList()
{
    delete ui;
}

void MovieList::on_SelectButton_clicked()
{
    //QMessageBox::information(this,"Hi","is_clicked");
    emit updateSeats();
    economyHall->show();
    //movieinformation = new MovieInformation(this);
    //movieinformation->show();
}

void MovieList::on_SelectButton_2_clicked()
{
    emit updateSeats();
    diamondHall->show();
}
