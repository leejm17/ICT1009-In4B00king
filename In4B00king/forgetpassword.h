#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QDialog>
#include "mydb.h"
#include "email.h"

namespace Ui {
class forgetpassword;
}

class forgetpassword : public QDialog
{
    Q_OBJECT

public:
    explicit forgetpassword(QWidget *parent = nullptr);
    ~forgetpassword();

private slots:
    void on_HomePage_clicked();

    void on_resetpassword_clicked();

    void on_resetpassword_3_clicked();

    void on_verifyButton_clicked();

private:
    Ui::forgetpassword *ui;
    email email;
};

#endif // FORGETPASSWORD_H
