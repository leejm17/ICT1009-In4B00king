#ifndef ECONOMYHALL_H
#define ECONOMYHALL_H

#include <QDialog>
#include "mydb.h"

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
    void showSeatSelection();

private slots:
    void on_book_clicked();
    void updateSeats();

private:
    Ui::EconomyHall *ui;
};

#endif // ECONOMYHALL_H
