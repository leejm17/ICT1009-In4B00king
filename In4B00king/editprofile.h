#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include "mydb.h"
#include "user.h"
#include <QDialog>

namespace Ui {
class editprofile;
}

class editprofile : public QDialog
{
    Q_OBJECT

public:
    explicit editprofile(QWidget *parent = nullptr);
    ~editprofile();

private slots:

    void on_Close_clicked();
    void receiveData(customer);

    void on_profilechange_clicked();

    void on_pwdchange_clicked();

private:
    Ui::editprofile *ui;
    customer edituser;
};

#endif // EDITPROFILE_H
