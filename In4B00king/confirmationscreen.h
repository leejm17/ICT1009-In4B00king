#ifndef CONFIRMATIONSCREEN_H
#define CONFIRMATIONSCREEN_H

#include <QDialog>

namespace Ui {
class ConfirmationScreen;
}

class ConfirmationScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationScreen(QWidget *parent = nullptr);
    ~ConfirmationScreen();

private slots:
    void receiveData(QString data);

private:
    Ui::ConfirmationScreen *ui;
};

#endif // CONFIRMATIONSCREEN_H
