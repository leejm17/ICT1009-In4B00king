#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QPixmap>
#include <QCryptographicHash>
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

// Onclick Event function for Login Button.
void Login::on_pushButton_clicked()
{

    QString username = ui->username->text();
    QString password = ui->password->text();
    // Salts the password using the username
    QString salted_password = username + password;
    // Hashes the salt using MD5
    QByteArray hashed_password = QCryptographicHash::hash(salted_password.toUtf8(),QCryptographicHash::Md5);
    QString inputHash = QLatin1String(hashed_password.toHex());

    // Initializes Sql
    QSqlQuery query(MyDB::getInstance()->getDBInstance());

    // Sql Query.
    query.prepare("Select * FROM User WHERE email_ID='" + username + "' AND password='" + inputHash + "';");
    if(!query.exec()){
        qDebug() << query.lastError().text() << query.lastQuery();
    }else{
        if(query.next()){
            QMessageBox::information(this, "Login", "You have logged in successfully as: " + username);
            close();

            //Create new movielist page
            mainpage = new MovieList(this);
            mainpage->show();

            connect(this, SIGNAL(sendData(user)), mainpage, SLOT(receiveData(user)));
            user newuser;
            newuser.GetUserVariables(username);          
            emit sendData(newuser);


        }else{
            QMessageBox::warning(this, "Login", "Wrong email or password");
        }
    }
}
// Onclick event for Register button. Pops up a new window.
void Login::on_Register_clicked()
{
    Register registerpage;
    registerpage.setModal(true);
    registerpage.exec();
}
// Onclick event for Forget Password button. Pops up a new window.
void Login::on_forgetpwd_clicked()
{
    forgetpassword forgetpwd;
    forgetpwd.setModal(true);
    forgetpwd.exec();
}
