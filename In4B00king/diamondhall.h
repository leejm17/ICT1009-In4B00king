#ifndef DIAMONDHALL_H
#define DIAMONDHALL_H

#include <QDialog>
#include "mydb.h"

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
    void showSeatSelection();

private slots:
    void on_book_clicked();
    void updateSeats();

private:
    Ui::DiamondHall *ui;
};

#endif // DIAMONDHALL_H
