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
    void updateSelection();

private:
    Ui::SeatSelection *ui;
};

#endif // SEATSELECTION_H
