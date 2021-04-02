#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <QMainWindow>
#include "movieinformation.h"
#include "economyhall.h"
#include "diamondhall.h"

namespace Ui {
class MovieList;
}

class MovieList : public QMainWindow
{
    Q_OBJECT

public:
    explicit MovieList(QWidget *parent = nullptr);
    ~MovieList();

private slots:

    void on_SelectButton_clicked();

    void on_SelectButton_2_clicked();

private:
    Ui::MovieList *ui;
    EconomyHall *economyHall;
    DiamondHall *diamondHall;
};

#endif // MAINPAGE_H
