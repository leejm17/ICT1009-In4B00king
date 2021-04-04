#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "login.h"
#include <QMessageBox>

forgetpassword::forgetpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

void forgetpassword::on_HomePage_clicked()
{
    close();
}

void forgetpassword::on_resetpassword_clicked()
{

}

void forgetpassword::on_resetpassword_3_clicked()
{
    bool emailcheck = false;
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString email = ui->Email->text();
    query.prepare("SELECT * FROM User WHERE email_ID='" + email + "';");
    if(!query.exec()){
            qDebug() << query.lastError().text() << query.lastQuery();
    }else if (query.exec()){
        if(query.next()){
            emailcheck = true;
        }
    }
    if (!emailcheck){
            QMessageBox::warning(this, "Invalid Email", "Email not found!");
    } else{
        //Disable send email button
    }

    //Add your sending email to verify here
}
