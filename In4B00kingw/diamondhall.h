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
    void closeAll();

private slots:
    void on_book_clicked();
    void updateSeats();

private:
    Ui::DiamondHall *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // DIAMONDHALL_H
