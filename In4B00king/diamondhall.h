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
    void showSeatSelection(int);
    void closeAll();

private slots:
    void on_book_clicked();
    void updateSeats(QString, QString, int);

private:
    Ui::DiamondHall *ui;
    void closeEvent(QCloseEvent *event);
    int show_ID;
};

#endif // DIAMONDHALL_H
