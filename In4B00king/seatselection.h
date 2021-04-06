#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class SeatSelection;
}

class SeatSelection : public QDialog
{
    Q_OBJECT

public:
    explicit SeatSelection(QWidget *parent = nullptr);
    ~SeatSelection();
    void updateSelection(int);

signals:
    void showConfirmation(QString, int);

private slots:
    void on_book_clicked();
    void showSeatSelection(int);


private:
    Ui::SeatSelection *ui;
    int show_ID;
};

#endif // SEATSELECTION_H
