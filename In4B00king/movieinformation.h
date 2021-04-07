#ifndef MOVIEINFORMATION_H
#define MOVIEINFORMATION_H

#include <QMainWindow>
#include <QDebug>
#include <movies.h>
#include "mydb.h"
#include "bookinginfo.h"

namespace Ui {
class MovieInformation;
}

class MovieInformation : public QMainWindow
{
    Q_OBJECT

public:
    explicit MovieInformation(QWidget *parent = nullptr);
    ~MovieInformation();

signals:
    void updateESeats(BookingInfo);
    void updateDSeats(BookingInfo);

private slots:
    void receiveData(MovieInfo);

    void on_Back_clicked();

    void on_SelectSeats_clicked();

private:
    Ui::MovieInformation *ui;
    int MovieID;
};

#endif // MOVIEINFORMATION_H
