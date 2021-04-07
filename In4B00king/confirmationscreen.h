#ifndef CONFIRMATIONSCREEN_H
#define CONFIRMATIONSCREEN_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class ConfirmationScreen;
}

class ConfirmationScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationScreen(QWidget *parent = nullptr);
    ~ConfirmationScreen();

signals:
    void updateSeats();
    void closeAll();

private slots:
    void showConfirmation(QString seat, int show_ID);
    void on_confirm_clicked();

private:
    Ui::ConfirmationScreen *ui;
    int show_ID;
};

#endif // CONFIRMATIONSCREEN_H
