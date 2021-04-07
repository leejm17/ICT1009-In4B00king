#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "movielist.h"
#include "register.h"
#include "forgetpassword.h"
#include "mydb.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();
    void on_Register_clicked();
    void on_forgetpwd_clicked();

signals:
    void sendData(user);

private:
    Ui::Login *ui;
    MovieList *mainpage;
};
#endif // LOGIN_H
