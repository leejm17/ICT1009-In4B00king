#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_Register_2_clicked();
    void on_testBtn_clicked();

    void on_verifyBtn_clicked();

    void on_verifyBtn_2_clicked();

    void on_Close_clicked();

    void on_sendemail_clicked();

    void on_verify_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
