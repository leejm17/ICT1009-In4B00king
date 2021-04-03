#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QDialog>
#include "mydb.h"
#include "confirmationscreen.h"

namespace Ui {
class SeatSelection;
}

class SeatSelection : public QDialog
{
    Q_OBJECT

public:
    explicit SeatSelection(QWidget *parent = nullptr);
    ~SeatSelection();
    void updateSelection();

signals:
    void sendData(QString);

private slots:
    void on_book_clicked();

private:
    Ui::SeatSelection *ui;
    ConfirmationScreen *confirmationScreen;
};

#endif // SEATSELECTION_H
