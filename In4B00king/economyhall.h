#ifndef ECONOMYHALL_H
#define ECONOMYHALL_H

#include <QDialog>
#include "mydb.h"
#include "bookinginfo.h"

namespace Ui {
class EconomyHall;
}

class EconomyHall : public QDialog
{
    Q_OBJECT

public:
    explicit EconomyHall(QWidget *parent = nullptr);
    ~EconomyHall();

signals:
    void showSeatSelection(BookingInfo);
    void closeAll();

private slots:
    void on_book_clicked();
    void updateSeats(BookingInfo);

private:
    Ui::EconomyHall *ui;
    void closeEvent(QCloseEvent *event);
    BookingInfo bookingInfo;
};

#endif // ECONOMYHALL_H
