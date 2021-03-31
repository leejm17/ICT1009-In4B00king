#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QPixmap>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/Logo.png");
    ui->label_pic->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString username = ui->username->text();
    QString password = ui->password->text();

    if (username == "test" && password == "test"){
        QMessageBox::information(this, "Login", "You have logined successfully");
        hide();
        mainpage = new Mainpage2(this);
        mainpage->show();
    } else {
        QMessageBox::warning(this, "Login", "You have failed to login");
    }

}
