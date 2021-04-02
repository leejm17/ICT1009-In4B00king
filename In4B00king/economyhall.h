#ifndef ECONOMYHALL_H
#define ECONOMYHALL_H

#include <QDialog>
#include "economyselection.h"

namespace Ui {
class EconomyHall;
}

class EconomyHall : public QDialog
{
    Q_OBJECT

public:
    explicit EconomyHall(QWidget *parent = nullptr);
    ~EconomyHall();

private slots:
    void on_book_clicked();

private:
    Ui::EconomyHall *ui;
    EconomySelection *economySelection;
};

#endif // ECONOMYHALL_H
