#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include <QDialog>
#include "mydb.h"
#include "confirmation.h"

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
    QPushButton *book;

private slots:
    void on_book_clicked();

private:
    Ui::SeatSelection *ui;
    confirmation *confirmation;
};

#endif // SEATSELECTION_H
