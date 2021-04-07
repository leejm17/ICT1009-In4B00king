#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QDialog>
#include "mydb.h"
#include "bookinginfo.h"

namespace Ui {
class SeatSelection;
}

class SeatSelection : public QDialog
{
    Q_OBJECT

public:
    explicit SeatSelection(QWidget *parent = nullptr);
    ~SeatSelection();
    void updateSelection(BookingInfo);

signals:
    void showConfirmation(QString, BookingInfo);

private slots:
    void on_book_clicked();
    void showSeatSelection(BookingInfo);


private:
    Ui::SeatSelection *ui;
    BookingInfo bookingInfo;
};

#endif // SEATSELECTION_H
