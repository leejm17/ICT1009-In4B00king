#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainpage2.h"
#include "mydb.h"

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

private:
    Ui::Login *ui;
    Mainpage2 *mainpage;
};
#endif // LOGIN_H
