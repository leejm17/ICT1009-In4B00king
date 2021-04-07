#ifndef CONFIRMATIONSCREEN_H
#define CONFIRMATIONSCREEN_H

#include <QDialog>
#include "mydb.h"
#include "bookinginfo.h"

namespace Ui {
class ConfirmationScreen;
}

class ConfirmationScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationScreen(QWidget *parent = nullptr);
    ~ConfirmationScreen();

signals:
    void updateESeats(BookingInfo);
    void updateDSeats(BookingInfo);

private slots:
    void showConfirmation(QString, BookingInfo);
    void on_confirm_clicked();

private:
    Ui::ConfirmationScreen *ui;
    BookingInfo bookingInfo;
};

#endif // CONFIRMATIONSCREEN_H
