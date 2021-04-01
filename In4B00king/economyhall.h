#ifndef ECONOMYHALL_H
#define ECONOMYHALL_H

#include <QDialog>

namespace Ui {
class EconomyHall;
}

class EconomyHall : public QDialog
{
    Q_OBJECT

public:
    explicit EconomyHall(QWidget *parent = nullptr);
    ~EconomyHall();

private:
    Ui::EconomyHall *ui;
};

#endif // ECONOMYHALL_H
