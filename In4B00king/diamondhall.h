#ifndef DIAMONDHALL_H
#define DIAMONDHALL_H

#include <QDialog>
#include "seatselection.h"

namespace Ui {
class DiamondHall;
}

class DiamondHall : public QDialog
{
    Q_OBJECT

public:
    explicit DiamondHall(QWidget *parent = nullptr);
    ~DiamondHall();
    void updateSeats();

private slots:
    void on_book_clicked();

private:
    Ui::DiamondHall *ui;
    SeatSelection *seatSelection;
};

#endif // DIAMONDHALL_H
