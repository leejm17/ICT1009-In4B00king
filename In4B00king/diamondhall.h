#ifndef DIAMONDHALL_H
#define DIAMONDHALL_H

#include <QDialog>
#include "mydb.h"
#include "bookinginfo.h"


namespace Ui {
class DiamondHall;
}

class DiamondHall : public QDialog
{
    Q_OBJECT

public:
    explicit DiamondHall(QWidget *parent = nullptr);
    ~DiamondHall();

signals:
    void showSeatSelection(BookingInfo);

private slots:
    void on_book_clicked();
    void updateSeats(BookingInfo);
    void updateDSeats(BookingInfo);


private:
    Ui::DiamondHall *ui;
    void closeEvent(QCloseEvent *event);
    BookingInfo bookingInfo;
};

#endif // DIAMONDHALL_H
